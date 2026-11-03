package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CommandTypeTest {

    @Test
    void getKeywordReturnsLowercaseName() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getKeyword()),
                () -> assertEquals("exit", CommandType.EXIT.getKeyword())
        );
    }

    @Test
    void getDescriptionReturnsCommandDescription() {
        assertAll(
                () -> assertEquals("Show available commands", CommandType.HELP.getDescription()),
                () -> assertEquals("Exit the application", CommandType.EXIT.getDescription())
        );
    }

    @Test
    void getSyntaxFallsBackToKeywordWhenNotSet() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getSyntax()),
                () -> assertEquals("exit", CommandType.EXIT.getSyntax())
        );
    }

    @Test
    void allCommandsTargetTui() {
        for (CommandType command : CommandType.values()) {
            assertEquals(CommandTarget.TUI, command.getTarget(),
                    command.getKeyword() + " should target TUI");
        }
    }

    @Test
    void commandTargetEnumContainsExpectedValues() {
        assertAll(
                () -> assertEquals(CommandTarget.TUI, CommandTarget.valueOf("TUI")),
                () -> assertEquals(CommandTarget.CORE, CommandTarget.valueOf("CORE")),
                () -> assertEquals(2, CommandTarget.values().length)
        );
    }

    @Test
    void fromKeywordResolvesKnownCommandCaseInsensitively() {
        assertAll(
                () -> assertEquals(CommandType.HELP, CommandType.fromKeyword("help")),
                () -> assertEquals(CommandType.HELP, CommandType.fromKeyword("HELP")),
                () -> assertEquals(CommandType.HELP, CommandType.fromKeyword("HeLp")),
                () -> assertEquals(CommandType.EXIT, CommandType.fromKeyword("exit")),
                () -> assertEquals(CommandType.EXIT, CommandType.fromKeyword("EXIT"))
        );
    }

    @Test
    void fromKeywordThrowsOnUnknownCommand() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> CommandType.fromKeyword("invalid")
        );
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void fromKeywordThrowsOnNull() {
        assertThrows(NullPointerException.class, () -> CommandType.fromKeyword(null));
    }
}
