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
        ParsedInput command = parser.parse("help");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.commandType()),
                () -> assertEquals("", command.arguments()));
    }

    @Test
    void parseIsCaseInsensitive() {
        assertAll(
                () -> assertEquals(CommandType.HELP, parser.parse("HELP").commandType()),
                () -> assertEquals(CommandType.HELP, parser.parse("Help").commandType()),
                () -> assertEquals(CommandType.EXIT, parser.parse("EXIT").commandType()));
    }

    @Test
    void parseTrimsSurroundingWhitespace() {
        ParsedInput command = parser.parse("   exit   ");

        assertEquals(CommandType.EXIT, command.commandType());
    }

    @Test
    void parseExtractsArgumentsAfterFirstWhitespace() {
        ParsedInput command = parser.parse("help   extra arguments");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.commandType()),
                () -> assertEquals("extra arguments", command.arguments()));
    }

    @Test
    void parsePreservesInnerArgumentSpacing() {
        ParsedInput command = parser.parse("help a  b");

        assertEquals("a  b", command.arguments());
    }

    @Test
    void parseThrowsOnNullInput() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.parse(null));
        assertEquals("Input cannot be empty.", exception.getMessage());
    }

    @Test
    void parseThrowsOnEmptyInput() {
        assertThrows(IllegalArgumentException.class, () -> parser.parse(""));
    }

    @Test
    void parseThrowsOnBlankInput() {
        assertThrows(IllegalArgumentException.class, () -> parser.parse("   \t  "));
    }

    @Test
    void parseThrowsOnUnknownKeyword() {
        UnknownCommandException exception = assertThrows(
                UnknownCommandException.class,
                () -> parser.parse("invalid"));
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void parseThrowsOnUnknownKeywordWithArguments() {
        UnknownCommandException exception = assertThrows(
                UnknownCommandException.class,
                () -> parser.parse("invalid argument"));
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void sliceResolvesAddProductKeywordWithArguments() {
        ParsedInput command = parser.parse("add P001 Monitor 799.99");

        assertAll(
                () -> assertEquals(CommandType.ADD_PRODUCT, command.commandType()),
                () -> assertEquals("P001 Monitor 799.99", command.arguments()));
    }

    @Test
    void parseCoreCommandBuildsAddProductCommand() {
        UserSession session = new UserSession();

        Command command = parser.toCommand(parser.parse("add P001 Monitor 799.99"));
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
        ParsedInput command = new ParsedInput(CommandType.ADD_PRODUCT, "");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertEquals("Missing arguments. Usage: add <code> <name> <price>", exception.getMessage());
    }

    @Test
    void parseCoreCommandThrowsOnIncompleteArguments() {
        ParsedInput command = new ParsedInput(CommandType.ADD_PRODUCT, "P001 Monitor");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertEquals("Invalid format. Usage: add <code> <name> <price>", exception.getMessage());
    }

    @Test
    void parseCoreCommandThrowsOnNonNumericPrice() {
        ParsedInput command = new ParsedInput(CommandType.ADD_PRODUCT, "P001 Monitor abc");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertEquals("Invalid price. Usage: add <code> <name> <price>", exception.getMessage());
        assertInstanceOf(NumberFormatException.class, exception.getCause(),
                "Original NumberFormatException should be chained as the cause");
    }

    @Test
    void parseCoreCommandThrowsForTuiCommandTypes() {
        for (CommandType type : CommandType.values()) {
            if (type.getTarget() != CommandType.Target.TUI) {
                continue;
            }

            ParsedInput command = new ParsedInput(type, "");

            UnknownCommandException exception = assertThrows(
                    UnknownCommandException.class,
                    () -> parser.toCommand(command),
                    "parseCoreCommand should reject " + type.getKeyword());
            assertEquals("Unknown command: " + type.getKeyword(), exception.getMessage());
        }
    }
}
