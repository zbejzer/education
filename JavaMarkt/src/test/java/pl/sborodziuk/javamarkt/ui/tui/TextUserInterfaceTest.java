package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.session.UserSession;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;

import static org.junit.jupiter.api.Assertions.*;

class TextUserInterfaceTest {

    private static final String WELCOME = "Enter a command, or type 'help' to list all available commands.";
    private static final String EXIT_MESSAGE = "App terminated successfully.";

    private final PrintStream originalOut = System.out;
    private final InputStream originalIn = System.in;
    private ByteArrayOutputStream outContent;

    @BeforeEach
    void setUpOutputCapture() {
        outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent, true, StandardCharsets.UTF_8));
    }

    @AfterEach
    void restoreSystemStreams() {
        System.setOut(originalOut);
        System.setIn(originalIn);
    }

    private TextUserInterface newInterfaceWithInput(String simulatedInput) {
        System.setIn(new ByteArrayInputStream(simulatedInput.getBytes(StandardCharsets.UTF_8)));
        return new TextUserInterface(new UserSession());
    }

    private String output() {
        return outContent.toString(StandardCharsets.UTF_8);
    }

    @Test
    void interfaceIsNotRunningBeforeStart() {
        System.setIn(new ByteArrayInputStream(new byte[0]));

        TextUserInterface tui = new TextUserInterface(new UserSession());

        assertFalse(tui.isRunning());
    }

    @Test
    void terminateStopsTheLoop() {
        TextUserInterface tui = newInterfaceWithInput("");

        tui.terminate();

        assertFalse(tui.isRunning());
    }

    @Test
    void handleHelpCommandPrintsCommandListing() {
        TextUserInterface tui = newInterfaceWithInput("");

        assertDoesNotThrow(() -> tui.handleCommand(new ParsedInput(CommandType.HELP, "")));

        String output = output();
        for (CommandType command : CommandType.values()) {
            assertAll(
                    () -> assertTrue(output.contains(command.getKeyword()),
                            "Help output should contain keyword: " + command.getKeyword()),
                    () -> assertTrue(output.contains(command.getDescription()),
                            "Help output should contain description: " + command.getDescription()),
                    () -> assertTrue(output.contains("(Syntax: " + command.getSyntax() + ")"),
                            "Help output should contain syntax for: " + command.getKeyword()));
        }
    }

    @Test
    void handleHelpCommandKeepsInterfaceRunning() {
        TextUserInterface tui = newInterfaceWithInput("");

        tui.handleCommand(new ParsedInput(CommandType.HELP, ""));

        assertFalse(tui.isRunning(),
                "HELP should not terminate the interface, but it must not start it either");
    }

    @Test
    void handleExitCommandPrintsExitMessage() {
        TextUserInterface tui = newInterfaceWithInput("");

        assertDoesNotThrow(() -> tui.handleCommand(new ParsedInput(CommandType.EXIT, "")));

        assertTrue(output().contains(EXIT_MESSAGE));
    }

    @Test
    void handleUnrecognizedCommandTypeThrowsIllegalState() {
        TextUserInterface tui = newInterfaceWithInput("");

        IllegalStateException exception = assertThrows(IllegalStateException.class,
                () -> tui.handleCommand(new ParsedInput(CommandType.ADD_PRODUCT, "P001 Monitor 799.99")));

        assertTrue(exception.getMessage().contains(CommandType.ADD_PRODUCT.getKeyword()),
                "Exception should identify the unrecognized command type");
    }

    @Test
    void startPrintsWelcomeAndProcessesCommandsUntilExit() {
        TextUserInterface tui = newInterfaceWithInput("help\nexit\n");

        tui.start();

        String output = output();
        assertAll(
                () -> assertTrue(output.contains(WELCOME)),
                () -> assertTrue(output.contains("Show available commands"), "HELP listing expected"),
                () -> assertTrue(output.contains(EXIT_MESSAGE)),
                () -> assertFalse(tui.isRunning()),
                () -> assertEquals(2, countPrompts(output), "Expected exactly two prompts"));
    }

    @Test
    void startStopsProcessingAfterExitCommand() {
        TextUserInterface tui = newInterfaceWithInput("exit\nhelp\n");

        tui.start();

        String output = output();
        assertAll(
                () -> assertTrue(output.contains(EXIT_MESSAGE)),
                () -> assertFalse(output.contains("Show available commands"),
                        "Commands after EXIT must not be processed"),
                () -> assertEquals(1, countPrompts(output), "Loop should end after EXIT"));
    }

    @Test
    void startIgnoresBlankLinesWithoutPrintingWelcomeAgain() {
        TextUserInterface tui = newInterfaceWithInput("\n   \nexit\n");

        assertDoesNotThrow(tui::start);

        String output = output();
        assertAll(
                () -> assertTrue(output.contains(EXIT_MESSAGE)),
                () -> assertEquals(3, countPrompts(output), "Each blank line should re-prompt"),
                () -> assertEquals(1, countOccurrences(output, WELCOME)));
    }

    @Test
    void startTerminatesAfterEofWhenInputEndsWithoutExitCommand() {
        TextUserInterface tui = newInterfaceWithInput("help\n");

        tui.start();

        String output = output();
        assertAll(
                () -> assertTrue(output.contains("Show available commands")),
                () -> assertFalse(output.contains(EXIT_MESSAGE)),
                () -> assertFalse(tui.isRunning(),
                        "EOF must terminate the interface, never quit with running == true"),
                () -> assertEquals(2, countPrompts(output),
                        "Prompt is displayed before EOF is reached"));
    }

    @Test
    void startOnEmptyInputPrintsSinglePromptBeforeEof() {
        TextUserInterface tui = newInterfaceWithInput("");

        tui.start();

        String output = output();
        assertAll(
                () -> assertTrue(output.contains(WELCOME)),
                () -> assertFalse(output.contains(EXIT_MESSAGE)),
                () -> assertFalse(tui.isRunning()),
                () -> assertEquals(1, countPrompts(output),
                        "Prompt is displayed once before EOF is reached"));
    }

    @Test
    void startProcessesAddProductCommandAgainstSessionCart() {
        UserSession session = new UserSession();
        System.setIn(new ByteArrayInputStream("add P001 Monitor 799.99\nexit\n".getBytes(StandardCharsets.UTF_8)));
        TextUserInterface tui = new TextUserInterface(session);

        tui.start();

        String output = output();
        assertAll(
                () -> assertEquals(1, session.getCart().getSize(), "ADD should add one item to the cart"),
                () -> assertEquals("P001", session.getCart().getAllItems()[0].getProduct().getCode()),
                () -> assertEquals(799.99, session.getCart().getAllItems()[0].getProduct().getPrice()),
                () -> assertTrue(output.contains(EXIT_MESSAGE), "Loop should continue to EXIT after ADD"));
    }

    private static int countPrompts(String output) {
        return countOccurrences(output, "\n> ");
    }

    private static int countOccurrences(String text, String needle) {
        int count = 0;
        int index = 0;
        while ((index = text.indexOf(needle, index)) != -1) {
            count++;
            index += needle.length();
        }
        return count;
    }
}
