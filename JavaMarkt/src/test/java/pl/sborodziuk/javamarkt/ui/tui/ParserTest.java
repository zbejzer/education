package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class ParserTest {

    private final Parser parser = new Parser();

    @Test
    void parseResolvesKeywordWithoutArguments() {
        GenericCommand command = parser.slice("help");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.getCommandType()),
                () -> assertEquals("", command.getRawArguments()));
    }

    @Test
    void parseIsCaseInsensitive() {
        assertAll(
                () -> assertEquals(CommandType.HELP, parser.slice("HELP").getCommandType()),
                () -> assertEquals(CommandType.HELP, parser.slice("Help").getCommandType()),
                () -> assertEquals(CommandType.EXIT, parser.slice("EXIT").getCommandType()));
    }

    @Test
    void parseTrimsSurroundingWhitespace() {
        GenericCommand command = parser.slice("   exit   ");

        assertEquals(CommandType.EXIT, command.getCommandType());
    }

    @Test
    void parseExtractsArgumentsAfterFirstWhitespace() {
        GenericCommand command = parser.slice("help   extra arguments");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.getCommandType()),
                () -> assertEquals("extra arguments", command.getRawArguments()));
    }

    @Test
    void parsePreservesInnerArgumentSpacing() {
        GenericCommand command = parser.slice("help a  b");

        assertEquals("a  b", command.getRawArguments());
    }

    @Test
    void parseThrowsOnNullInput() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.slice(null));
        assertEquals("Input cannot be empty.", exception.getMessage());
    }

    @Test
    void parseThrowsOnEmptyInput() {
        assertThrows(IllegalArgumentException.class, () -> parser.slice(""));
    }

    @Test
    void parseThrowsOnBlankInput() {
        assertThrows(IllegalArgumentException.class, () -> parser.slice("   \t  "));
    }

    @Test
    void parseThrowsOnUnknownKeyword() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.slice("invalid"));
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void parseThrowsOnUnknownKeywordWithArguments() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.slice("invalid argument"));
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void sliceResolvesAddProductKeywordWithArguments() {
        GenericCommand command = parser.slice("add P001 Monitor 799.99");

        assertAll(
                () -> assertEquals(CommandType.ADD_PRODUCT, command.getCommandType()),
                () -> assertEquals("P001 Monitor 799.99", command.getRawArguments()));
    }

    @Test
    void parseCoreCommandBuildsAddProductCommand() {
        UserSession session = new UserSession();

        Command command = parser.parseCoreCommand(parser.slice("add P001 Monitor 799.99"));
        command.execute(session);

        Product added = session.getCart().getAllItems()[0].getProduct();
        assertAll(
                () -> assertTrue(command instanceof AddProductCommand,
                        "parseCoreCommand should build an AddProductCommand"),
                () -> assertEquals("P001", added.getCode()),
                () -> assertEquals("Monitor", added.getName()),
                () -> assertEquals(799.99, added.getPrice()));
    }

    @Test
    void parseCoreCommandThrowsOnMissingArguments() {
        GenericCommand command = new GenericCommand(CommandType.ADD_PRODUCT, "");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.parseCoreCommand(command));
        assertEquals("Missing arguments. Usage: add <code> <name> <price>", exception.getMessage());
    }

    @Test
    void parseCoreCommandThrowsOnIncompleteArguments() {
        GenericCommand command = new GenericCommand(CommandType.ADD_PRODUCT, "P001 Monitor");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.parseCoreCommand(command));
        assertEquals("Invalid format. Usage: add <code> <name> <price>", exception.getMessage());
    }

    @Test
    void parseCoreCommandThrowsOnNonNumericPrice() {
        GenericCommand command = new GenericCommand(CommandType.ADD_PRODUCT, "P001 Monitor abc");

        assertThrows(NumberFormatException.class, () -> parser.parseCoreCommand(command));
    }

    @Test
    void parseCoreCommandThrowsForTuiCommandTypes() {
        for (CommandType type : CommandType.values()) {
            if (type.getTarget() != CommandTarget.TUI) {
                continue;
            }

            GenericCommand command = new GenericCommand(type, "");

            IllegalArgumentException exception = assertThrows(
                    IllegalArgumentException.class,
                    () -> parser.parseCoreCommand(command),
                    "parseCoreCommand should reject " + type.getKeyword());
            assertEquals("Unknown command: " + type.getKeyword(), exception.getMessage());
        }
    }
}
