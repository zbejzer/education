package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CommandTypeTest {

    @Test
    void getKeywordReturnsLowercaseName() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getKeyword()),
                () -> assertEquals("exit", CommandType.EXIT.getKeyword()));
    }

    @Test
    void getSyntaxFallsBackToKeywordWhenNotSet() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getSyntax()),
                () -> assertEquals("exit", CommandType.EXIT.getSyntax())
        );
    }

    @Test
    void getKeywordReturnsCustomKeywordWhenSet() {
        assertEquals("add", CommandType.ADD_PRODUCT.getKeyword());
    }

    @Test
    void getSyntaxPrefixesCustomKeywordWithDeclaredSyntax() {
        assertEquals("add <code> <name> <price>", CommandType.ADD_PRODUCT.getSyntax());
    }

    @Test
    void fromKeywordResolvesCustomKeywordCaseInsensitively() {
        assertAll(
                () -> assertEquals(CommandType.ADD_PRODUCT, CommandType.fromKeyword("add")),
                () -> assertEquals(CommandType.ADD_PRODUCT, CommandType.fromKeyword("ADD")),
                () -> assertEquals(CommandType.ADD_PRODUCT, CommandType.fromKeyword("Add"))
        );
    }

    @Test
    void fromKeywordResolvesKnownCommandCaseInsensitively() {
        assertAll(
                () -> assertEquals(CommandType.HELP, CommandType.fromKeyword("help")),
                () -> assertEquals(CommandType.HELP, CommandType.fromKeyword("HELP")),
                () -> assertEquals(CommandType.HELP, CommandType.fromKeyword("HeLp")),
                () -> assertEquals(CommandType.EXIT, CommandType.fromKeyword("exit")),
                () -> assertEquals(CommandType.EXIT, CommandType.fromKeyword("EXIT")));
    }

    @Test
    void fromKeywordThrowsOnUnknownCommand() {
        UnknownCommandException exception = assertThrows(
                UnknownCommandException.class,
                () -> CommandType.fromKeyword("invalid"));
        assertEquals("Unknown command: invalid", exception.getMessage());
    }

    @Test
    void getTargetClassifiesTuiAndCoreCommands() {
        assertAll(
                () -> assertEquals(CommandType.Target.TUI, CommandType.HELP.getTarget()),
                () -> assertEquals(CommandType.Target.TUI, CommandType.EXIT.getTarget()),
                () -> assertEquals(CommandType.Target.CORE, CommandType.ADD_PRODUCT.getTarget()));
    }
}
