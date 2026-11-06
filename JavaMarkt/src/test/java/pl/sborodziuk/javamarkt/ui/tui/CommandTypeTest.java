package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CommandTypeTest {

    @Test
    void getKeywordReturnsLowercaseName() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getKeyword()),
                () -> assertEquals("exit", CommandType.EXIT.getKeyword()),
                () -> assertEquals("history", CommandType.HISTORY.getKeyword()));
    }

    @Test
    void getSyntaxFallsBackToKeywordWhenNotSet() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getSyntax()),
                () -> assertEquals("exit", CommandType.EXIT.getSyntax()),
                () -> assertEquals("history", CommandType.HISTORY.getSyntax())
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
        assertTrue(exception.getMessage().contains("invalid"));
    }

    @Test
    void getTargetClassifiesTuiAndCoreCommands() {
        assertAll(
                () -> assertEquals(CommandType.Target.TUI, CommandType.HELP.getTarget()),
                () -> assertEquals(CommandType.Target.TUI, CommandType.EXIT.getTarget()),
                () -> assertEquals(CommandType.Target.TUI, CommandType.HISTORY.getTarget()),
                () -> assertEquals(CommandType.Target.CORE, CommandType.ADD_PRODUCT.getTarget()),
                () -> assertEquals(CommandType.Target.CORE, CommandType.REGISTER_PRODUCT.getTarget()),
                () -> assertEquals(CommandType.Target.CORE, CommandType.UNREGISTER_PRODUCT.getTarget()));
    }

    @Test
    void registerAndUnregisterUseSimplifiedKeywords() {
        assertAll(
                () -> assertEquals("register", CommandType.REGISTER_PRODUCT.getKeyword()),
                () -> assertEquals("unregister", CommandType.UNREGISTER_PRODUCT.getKeyword()));
    }

    @Test
    void registerAndUnregisterDeclareSyntax() {
        assertAll(
                () -> assertEquals("register <code> <name> <price>", CommandType.REGISTER_PRODUCT.getSyntax()),
                () -> assertEquals("unregister <code>", CommandType.UNREGISTER_PRODUCT.getSyntax()));
    }

    @Test
    void fromKeywordResolvesRegisterAndUnregisterCaseInsensitively() {
        assertAll(
                () -> assertEquals(CommandType.REGISTER_PRODUCT, CommandType.fromKeyword("register")),
                () -> assertEquals(CommandType.REGISTER_PRODUCT, CommandType.fromKeyword("REGISTER")),
                () -> assertEquals(CommandType.UNREGISTER_PRODUCT, CommandType.fromKeyword("unregister")),
                () -> assertEquals(CommandType.UNREGISTER_PRODUCT, CommandType.fromKeyword("Unregister")));
    }

    @Test
    void getRequiredArgumentCountMatchesSyntaxPlaceholders() {
        assertAll(
                () -> assertEquals(0, CommandType.HELP.getRequiredArgumentCount()),
                () -> assertEquals(0, CommandType.EXIT.getRequiredArgumentCount()),
                () -> assertEquals(0, CommandType.HISTORY.getRequiredArgumentCount()),
                () -> assertEquals(3, CommandType.ADD_PRODUCT.getRequiredArgumentCount()),
                () -> assertEquals(3, CommandType.REGISTER_PRODUCT.getRequiredArgumentCount()),
                () -> assertEquals(1, CommandType.UNREGISTER_PRODUCT.getRequiredArgumentCount()));
    }
}
