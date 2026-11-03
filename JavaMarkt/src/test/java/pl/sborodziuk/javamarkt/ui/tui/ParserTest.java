package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ParserTest {

    private final Parser parser = new Parser();

    @Test
    void parseResolvesKeywordWithoutArguments() {
        GenericCommand command = parser.parse("help");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.getCommandType()),
                () -> assertEquals("", command.getArguments())
        );
    }

    @Test
    void parseIsCaseInsensitive() {
        assertAll(
                () -> assertEquals(CommandType.HELP, parser.parse("HELP").getCommandType()),
                () -> assertEquals(CommandType.HELP, parser.parse("Help").getCommandType()),
                () -> assertEquals(CommandType.EXIT, parser.parse("EXIT").getCommandType())
        );
    }

    @Test
    void parseTrimsSurroundingWhitespace() {
        GenericCommand command = parser.parse("   exit   ");

        assertEquals(CommandType.EXIT, command.getCommandType());
    }

    @Test
    void parseExtractsArgumentsAfterFirstWhitespace() {
        GenericCommand command = parser.parse("help   extra arguments");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.getCommandType()),
                () -> assertEquals("extra arguments", command.getArguments())
        );
    }

    @Test
    void parsePreservesInnerArgumentSpacing() {
        GenericCommand command = parser.parse("help a  b");

        assertEquals("a  b", command.getArguments());
    }

    @Test
    void parseThrowsOnNullInput() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.parse(null)
        );
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
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.parse("invalid")
        );
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void parseThrowsOnUnknownKeywordWithArguments() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.parse("invalid argument")
        );
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void parseCoreCommandThrowsForEveryCommandType() {
        for (CommandType type : CommandType.values()) {
            GenericCommand command = new GenericCommand(type, "");

            IllegalArgumentException exception = assertThrows(
                    IllegalArgumentException.class,
                    () -> parser.parseCoreCommand(command),
                    "parseCoreCommand should reject " + type.getKeyword()
            );
            assertEquals("Unknown command: " + type.getKeyword(), exception.getMessage());
        }
    }
}
