package pl.sborodziuk.javamarkt.ui.tui;

import java.util.HashSet;
import java.util.Set;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CommandTypeTest {

    @Test
    void everyCommandTypeHasDistinctKeywordAndResolvesFromIt() {
        Set<String> keywords = new HashSet<>();

        for (CommandType type : CommandType.values()) {
            String keyword = type.getKeyword();
            assertAll(
                    () -> assertTrue(keywords.add(keyword), "Duplicate keyword: " + keyword),
                    () -> assertSame(type, CommandType.fromKeyword(keyword)),
                    () -> assertSame(type, CommandType.fromKeyword(keyword.toUpperCase())));
        }

        assertEquals(CommandType.values().length, keywords.size());
    }

    @Test
    void getKeywordReturnsLowercaseName() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getKeyword()),
                () -> assertEquals("exit", CommandType.EXIT.getKeyword()),
                () -> assertEquals("history", CommandType.HISTORY.getKeyword()),
                () -> assertEquals("undo", CommandType.UNDO.getKeyword()),
                () -> assertEquals("clear_history", CommandType.CLEAR_HISTORY.getKeyword()));
    }

    @Test
    void getSyntaxFallsBackToKeywordWhenNotSet() {
        assertAll(
                () -> assertEquals("help", CommandType.HELP.getSyntax()),
                () -> assertEquals("exit", CommandType.EXIT.getSyntax()),
                () -> assertEquals("history", CommandType.HISTORY.getSyntax()),
                () -> assertEquals("undo", CommandType.UNDO.getSyntax()),
                () -> assertEquals("clear_history", CommandType.CLEAR_HISTORY.getSyntax())
        );
    }

    @Test
    void getKeywordReturnsCustomKeywordWhenSet() {
        assertEquals("add", CommandType.ADD_PRODUCT.getKeyword());
    }

    @Test
    void getSyntaxPrefixesCustomKeywordWithDeclaredSyntax() {
        assertEquals("add <code>", CommandType.ADD_PRODUCT.getSyntax());
    }

    @Test
    void fromKeywordResolvesClearHistoryCaseInsensitively() {
        assertAll(
                () -> assertEquals(CommandType.CLEAR_HISTORY, CommandType.fromKeyword("clear_history")),
                () -> assertEquals(CommandType.CLEAR_HISTORY, CommandType.fromKeyword("CLEAR_HISTORY")),
                () -> assertEquals(CommandType.CLEAR_HISTORY, CommandType.fromKeyword("Clear_History")));
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
    void fromKeywordRejectsNullKeyword() {
        assertThrows(IllegalArgumentException.class, () -> CommandType.fromKeyword(null));
    }

    @Test
    void getTargetClassifiesCommandsByTarget() {
        assertAll(
                () -> assertEquals(CommandType.Target.SHELL, CommandType.HELP.getTarget()),
                () -> assertEquals(CommandType.Target.SHELL, CommandType.EXIT.getTarget()),
                () -> assertEquals(CommandType.Target.QUERY, CommandType.HISTORY.getTarget()),
                () -> assertEquals(CommandType.Target.SESSION, CommandType.UNDO.getTarget()),
                () -> assertEquals(CommandType.Target.SESSION, CommandType.CLEAR_HISTORY.getTarget()),
                () -> assertEquals(CommandType.Target.COMMAND, CommandType.ADD_PRODUCT.getTarget()),
                () -> assertEquals(CommandType.Target.COMMAND, CommandType.REGISTER_PRODUCT.getTarget()),
                () -> assertEquals(CommandType.Target.COMMAND, CommandType.UNREGISTER_PRODUCT.getTarget()),
                () -> assertEquals(CommandType.Target.COMMAND, CommandType.REMOVE_PRODUCT.getTarget()));
    }

    @Test
    void registerAndUnregisterUseSimplifiedKeywords() {
        assertAll(
                () -> assertEquals("register", CommandType.REGISTER_PRODUCT.getKeyword()),
                () -> assertEquals("unregister", CommandType.UNREGISTER_PRODUCT.getKeyword()));
    }

    @Test
    void removeProductUsesKeywordAndSyntax() {
        assertAll(
                () -> assertEquals("remove", CommandType.REMOVE_PRODUCT.getKeyword()),
                () -> assertEquals("remove <code>", CommandType.REMOVE_PRODUCT.getSyntax()));
    }

    @Test
    void fromKeywordResolvesRemoveProductCaseInsensitively() {
        assertAll(
                () -> assertEquals(CommandType.REMOVE_PRODUCT, CommandType.fromKeyword("remove")),
                () -> assertEquals(CommandType.REMOVE_PRODUCT, CommandType.fromKeyword("REMOVE")),
                () -> assertEquals(CommandType.REMOVE_PRODUCT, CommandType.fromKeyword("Remove")));
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
                () -> assertEquals(0, CommandType.UNDO.getRequiredArgumentCount()),
                () -> assertEquals(0, CommandType.CLEAR_HISTORY.getRequiredArgumentCount()),
                () -> assertEquals(1, CommandType.ADD_PRODUCT.getRequiredArgumentCount()),
                () -> assertEquals(3, CommandType.REGISTER_PRODUCT.getRequiredArgumentCount()),
                () -> assertEquals(1, CommandType.UNREGISTER_PRODUCT.getRequiredArgumentCount()),
                () -> assertEquals(1, CommandType.REMOVE_PRODUCT.getRequiredArgumentCount()));
    }
}
