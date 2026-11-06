package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.util.List;

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
                return new TextUserInterface(new UserSession(new ProductCatalog()));
        }

        private String output() {
                return outContent.toString(StandardCharsets.UTF_8);
        }

        @Test
        void interfaceIsNotRunningBeforeStart() {
                System.setIn(new ByteArrayInputStream(new byte[0]));

                TextUserInterface tui = new TextUserInterface(new UserSession(new ProductCatalog()));

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

                assertDoesNotThrow(() -> tui.handleCommand(new ParsedCommand(CommandType.HELP, List.of())));

                String output = output();
                for (CommandType command : CommandType.values()) {
                        assertAll(
                                        () -> assertTrue(output.contains(command.getKeyword()),
                                                        "Help output should contain keyword: " + command.getKeyword()),
                                        () -> assertTrue(output.contains(command.getDescription()),
                                                        "Help output should contain description: "
                                                                        + command.getDescription()),
                                        () -> assertTrue(output.contains("(Syntax: " + command.getSyntax() + ")"),
                                                        "Help output should contain syntax for: "
                                                                        + command.getKeyword()));
                }
        }

        @Test
        void handleHelpCommandKeepsInterfaceRunning() {
                TextUserInterface tui = newInterfaceWithInput("");

                tui.handleCommand(new ParsedCommand(CommandType.HELP, List.of()));

                assertFalse(tui.isRunning(),
                                "HELP should not terminate the interface, but it must not start it either");
        }

        @Test
        void handleExitCommandPrintsExitMessage() {
                TextUserInterface tui = newInterfaceWithInput("");

                assertDoesNotThrow(() -> tui.handleCommand(new ParsedCommand(CommandType.EXIT, List.of())));

                assertTrue(output().contains(EXIT_MESSAGE));
        }

        @Test
        void handleUnrecognizedCommandTypeThrowsIllegalState() {
                TextUserInterface tui = newInterfaceWithInput("");

                IllegalStateException exception = assertThrows(IllegalStateException.class,
                                () -> tui.handleCommand(new ParsedCommand(
                                                CommandType.ADD_PRODUCT, List.of("P001", "Monitor", "799.99"))));

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
        void startReportsUnknownCommandWithHelpHintAndContinuesLoop() {
                TextUserInterface tui = newInterfaceWithInput("bogus\nexit\n");

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("Unknown command: bogus"),
                                                "Unknown keyword should be reported"),
                                () -> assertTrue(output.contains(CommandType.HELP.getKeyword()),
                                                "Unknown command error should hint at help"),
                                () -> assertTrue(output.contains(EXIT_MESSAGE),
                                                "Loop must survive unknown commands and process EXIT"),
                                () -> assertFalse(tui.isRunning()));
        }

        @Test
        void startProcessesAddProductCommandAgainstSessionCart() {
                UserSession session = new UserSession(new ProductCatalog());
                System.setIn(new ByteArrayInputStream(
                                "add P001 Monitor 799.99\nexit\n".getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                String output = output();
                assertAll(
                                () -> assertEquals(1, session.getCart().getSize(),
                                                "ADD should add one item to the cart"),
                                () -> assertEquals("P001", session.getCart().getAllItems()[0].getProduct().getCode()),
                                () -> assertEquals(799.99, session.getCart().getAllItems()[0].getProduct().getPrice()),
                                () -> assertTrue(output.contains(EXIT_MESSAGE),
                                                "Loop should continue to EXIT after ADD"));
        }

        @Test
        void startProcessesRegisterProductCommandAgainstCatalog() {
                ProductCatalog catalog = new ProductCatalog();
                UserSession session = new UserSession(catalog);
                System.setIn(new ByteArrayInputStream(
                                "register PRG5 Speakers 199.99\nexit\n".getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                Product registered = catalog.findByCode("PRG5");
                assertAll(
                                () -> assertEquals("Speakers", registered.getName()),
                                () -> assertEquals(199.99, registered.getPrice()),
                                () -> assertTrue(output().contains(EXIT_MESSAGE),
                                                "Loop should continue to EXIT after REGISTER"));
        }

        @Test
        void startProcessesUnregisterProductCommandAgainstCatalog() {
                ProductCatalog catalog = new ProductCatalog();
                UserSession session = new UserSession(catalog);
                catalog.addProduct(new Product("PRU6", "Removable", 5.0));
                System.setIn(new ByteArrayInputStream("unregister PRU6\nexit\n".getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                assertAll(
                                () -> assertNull(catalog.findByCode("PRU6")),
                                () -> assertTrue(output().contains(EXIT_MESSAGE),
                                                "Loop should continue to EXIT after UNREGISTER"));
        }

        @Test
        void startReportsErrorWhenRegisteringDuplicateCodeAndContinuesLoop() {
                ProductCatalog catalog = new ProductCatalog();
                UserSession session = new UserSession(catalog);
                System.setIn(new ByteArrayInputStream(
                                "register PRG9 DupOnce 10.0\nregister PRG9 DupTwice 20.0\nexit\n"
                                                .getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("Error: Product with code PRG9 already exists."),
                                                "Duplicate registration should be reported as an error"),
                                () -> assertEquals("DupOnce", catalog.findByCode("PRG9").getName(),
                                                "Original product must be kept"),
                                () -> assertTrue(output.contains(EXIT_MESSAGE),
                                                "Loop must survive a rejected command and process EXIT"));
        }

        @Test
        void startListsSubmittedCommandsInHistoryInSubmissionOrder() {
                UserSession session = new UserSession(new ProductCatalog());
                System.setIn(new ByteArrayInputStream(
                                "register R001 Keyboard 149.99\nadd P001 Monitor 799.99\nhistory\nexit\n"
                                                .getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("1. register R001 Keyboard 149.99")),
                                () -> assertTrue(output.contains("2. add P001 Monitor 799.99")),
                                () -> assertTrue(
                                                output.indexOf("1. register R001 Keyboard 149.99") < output
                                                                .indexOf("2. add P001 Monitor 799.99"),
                                                "History entries must follow submission order"),
                                () -> assertTrue(output.contains(EXIT_MESSAGE)),
                                () -> assertFalse(tui.isRunning(), "Loop should end after EXIT"),
                                () -> assertEquals(4, countPrompts(output), "Each processed line should re-prompt"));
        }

        @Test
        void startReportsEmptyHistory() {
                TextUserInterface tui = newInterfaceWithInput("history\nexit\n");

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("History is empty.")),
                                () -> assertTrue(output.contains(EXIT_MESSAGE)),
                                () -> assertFalse(tui.isRunning()));
        }

        @Test
        void startHistoryListsOnlySuccessfullyExecutedCommands() {
                UserSession session = new UserSession(new ProductCatalog());
                System.setIn(new ByteArrayInputStream(
                                "register PRH3 DupOnce 10.0\nregister PRH3 DupTwice 20.0\nhistory\nexit\n"
                                                .getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("Error: Product with code PRH3 already exists."),
                                                "Duplicate registration should be reported as an error"),
                                () -> assertTrue(output.contains("1. register PRH3 DupOnce 10.0")),
                                () -> assertFalse(output.contains("2. "), "Failed command must not be recorded"),
                                () -> assertFalse(output.contains("DupTwice")),
                                () -> assertTrue(output.contains(EXIT_MESSAGE),
                                                "Loop must survive a rejected command"));
        }

        @Test
        void startRendersHistoryCanonicallyRegardlessOfInputSpacing() {
                UserSession session = new UserSession(new ProductCatalog());
                System.setIn(new ByteArrayInputStream(
                                "add  P001   Monitor  799.990\nhistory\nexit\n".getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("1. add P001 Monitor 799.99")),
                                () -> assertFalse(output.contains("799.990")),
                                () -> assertTrue(output.contains(EXIT_MESSAGE)));
        }

        @Test
        void startUndoesLastRegisterCommandAndReportsIt() {
                ProductCatalog catalog = new ProductCatalog();
                UserSession session = new UserSession(catalog);
                System.setIn(new ByteArrayInputStream(
                                "register R001 Keyboard 149.99\nundo\nexit\n".getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("Undone: register R001 Keyboard 149.99"),
                                                "UNDO should describe the reversed command canonically"),
                                () -> assertTrue(catalog.isEmpty(), "Catalog should be empty after undo"),
                                () -> assertTrue(output.contains(EXIT_MESSAGE)),
                                () -> assertFalse(tui.isRunning(), "Loop should end after EXIT"));
        }

        @Test
        void startUndoesLastUnregisterCommandAndRestoresProduct() {
                ProductCatalog catalog = new ProductCatalog();
                UserSession session = new UserSession(catalog);
                System.setIn(new ByteArrayInputStream(
                                "register R001 Keyboard 149.99\nadd P001 Monitor 799.99\nunregister R001\nundo\nexit\n"
                                                .getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                Product restored = catalog.findByCode("R001");
                assertAll(
                                () -> assertTrue(output().contains("Undone: unregister R001")),
                                () -> assertEquals("Keyboard", restored.getName()),
                                () -> assertEquals(149.99, restored.getPrice()),
                                () -> assertEquals(1, session.getCart().getSize(),
                                                "Cart must keep its item through catalog undo"),
                                () -> assertEquals("P001", session.getCart().getAllItems()[0].getProduct().getCode()),
                                () -> assertTrue(output().contains(EXIT_MESSAGE)),
                                () -> assertFalse(tui.isRunning()));
        }

        @Test
        void startReportsBlockedUndoWhenNonUndoableCommandIsLast() {
                ProductCatalog catalog = new ProductCatalog();
                UserSession session = new UserSession(catalog);
                System.setIn(new ByteArrayInputStream(
                                "register R001 Keyboard 149.99\nadd P001 Monitor 799.99\nundo\nexit\n"
                                                .getBytes(StandardCharsets.UTF_8)));
                TextUserInterface tui = new TextUserInterface(session);

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("Cannot undo the last operation."),
                                                "The add at the top of history must block deeper undo"),
                                () -> assertEquals("Keyboard", catalog.findByCode("R001").getName(),
                                                "Catalog must keep the registered product"),
                                () -> assertEquals(1, session.getCart().getSize(),
                                                "Cart must keep the added item"),
                                () -> assertTrue(output.contains(EXIT_MESSAGE),
                                                "Loop must survive a blocked undo and process EXIT"),
                                () -> assertFalse(tui.isRunning()));
        }

        @Test
        void startReportsNothingToUndoOnEmptyHistory() {
                TextUserInterface tui = newInterfaceWithInput("undo\nexit\n");

                tui.start();

                String output = output();
                assertAll(
                                () -> assertTrue(output.contains("Nothing to undo.")),
                                () -> assertTrue(output.contains(EXIT_MESSAGE)),
                                () -> assertFalse(tui.isRunning()));
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
