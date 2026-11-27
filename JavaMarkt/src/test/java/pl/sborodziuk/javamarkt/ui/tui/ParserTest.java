package pl.sborodziuk.javamarkt.ui.tui;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
import pl.sborodziuk.javamarkt.command.RemoveProductCommand;
import pl.sborodziuk.javamarkt.command.UnregisterProductCommand;
import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class ParserTest {

    private final Parser parser = new Parser();

    @Test
    void parseResolvesKeywordWithoutArguments() {
        ParsedCommand command = parser.parse("help");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.commandType()),
                () -> assertEquals(List.of(), command.arguments()));
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
        ParsedCommand command = parser.parse("   exit   ");

        assertEquals(CommandType.EXIT, command.commandType());
    }

    @Test
    void parseExtractsArgumentsAfterFirstWhitespace() {
        ParsedCommand command = parser.parse("add   P001");

        assertAll(
                () -> assertEquals(CommandType.ADD_PRODUCT, command.commandType()),
                () -> assertEquals(List.of("P001"), command.arguments()));
    }

    @Test
    void parseTokenizesArgumentsOnWhitespace() {
        ParsedCommand command = parser.parse("add P001  ");

        assertEquals(List.of("P001"), command.arguments());
    }

    @Test
    void parseTreatsTabsAndRepeatedSpacesAsWhitespace() {
        ParsedCommand command = parser.parse("register\tR001\tKeyboard   149.99");

        assertAll(
                () -> assertEquals(CommandType.REGISTER_PRODUCT, command.commandType()),
                () -> assertEquals(List.of("R001", "Keyboard", "149.99"), command.arguments()));
    }

    @Test
    void parsedCommandCopiesArgumentsDefensively() {
        List<String> source = new ArrayList<>(List.of("P001"));

        ParsedCommand command = new ParsedCommand(CommandType.ADD_PRODUCT, source);
        source.add("P002");

        assertAll(
                () -> assertEquals(List.of("P001"), command.arguments()),
                () -> assertThrows(UnsupportedOperationException.class,
                        () -> command.arguments().add("P003")));
    }

    @Test
    void parseThrowsOnNullInput() {
        assertThrows(IllegalArgumentException.class, () -> parser.parse(null));
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
        assertTrue(exception.getMessage().contains("invalid"));
    }

    @Test
    void parseThrowsOnUnknownKeywordWithArguments() {
        UnknownCommandException exception = assertThrows(
                UnknownCommandException.class,
                () -> parser.parse("invalid argument"));
        assertTrue(exception.getMessage().contains("invalid"));
    }

    @Test
    void parseReturnsArgumentsWithoutArityValidation() {
        ParsedCommand extraHelp = parser.parse("help now");
        ParsedCommand extraUnregister = parser.parse("unregister a b");

        assertAll(
                () -> assertEquals(CommandType.HELP, extraHelp.commandType()),
                () -> assertEquals(List.of("now"), extraHelp.arguments()),
                () -> assertEquals(CommandType.UNREGISTER_PRODUCT, extraUnregister.commandType()),
                () -> assertEquals(List.of("a", "b"), extraUnregister.arguments()));
    }

    @Test
    void requireValidArgumentCountAcceptsExactArgumentCountForEveryCommand() {
        for (CommandType type : CommandType.values()) {
            String[] args = new String[type.getRequiredArgumentCount()];
            Arrays.fill(args, "x");

            assertDoesNotThrow(() -> parser.requireValidArgumentCount(type, Arrays.asList(args)),
                    "validateArgumentCount should accept: " + type.getKeyword());
        }
    }

    @Test
    void requireValidArgumentCountRejectsTooManyArgumentsForEveryCommand() {
        for (CommandType type : CommandType.values()) {
            String[] args = new String[type.getRequiredArgumentCount() + 1];
            Arrays.fill(args, "x");

            CommandFormatException exception = assertThrows(
                    CommandFormatException.class, () -> parser.requireValidArgumentCount(type, Arrays.asList(args)),
                    "validateArgumentCount should reject: " + type.getKeyword());
            assertTrue(exception.getMessage().contains(type.getSyntax()));
        }
    }

    @Test
    void requireValidArgumentCountRejectsTooFewArgumentsForEveryCommand() {
        for (CommandType type : CommandType.values()) {
            if (type.getRequiredArgumentCount() == 0) {
                continue;
            }

            CommandFormatException exception = assertThrows(
                    CommandFormatException.class, () -> parser.requireValidArgumentCount(type, List.of()),
                    "validateArgumentCount should reject: " + type.getKeyword());
            assertTrue(exception.getMessage().contains(type.getSyntax()));
        }
    }

    @Test
    void parseResolvesAddProductKeywordWithArguments() {
        ParsedCommand command = parser.parse("add P001");

        assertAll(
                () -> assertEquals(CommandType.ADD_PRODUCT, command.commandType()),
                () -> assertEquals(List.of("P001"), command.arguments()));
    }

    @Test
    void parseResolvesRegisterProductKeywordWithArguments() {
        ParsedCommand command = parser.parse("register R001 Keyboard 149.99");

        assertAll(
                () -> assertEquals(CommandType.REGISTER_PRODUCT, command.commandType()),
                () -> assertEquals(List.of("R001", "Keyboard", "149.99"), command.arguments()));
    }

    @Test
    void parseResolvesUnregisterProductKeyword() {
        ParsedCommand command = parser.parse("unregister R001");

        assertAll(
                () -> assertEquals(CommandType.UNREGISTER_PRODUCT, command.commandType()),
                () -> assertEquals(List.of("R001"), command.arguments()));
    }

    @Test
    void parseResolvesRemoveProductKeyword() {
        ParsedCommand command = parser.parse("remove P001");

        assertAll(
                () -> assertEquals(CommandType.REMOVE_PRODUCT, command.commandType()),
                () -> assertEquals(List.of("P001"), command.arguments()));
    }

    @Test
    void parseResolvesHistoryKeyword() {
        ParsedCommand command = parser.parse("history");

        assertAll(
                () -> assertEquals(CommandType.HISTORY, command.commandType()),
                () -> assertEquals(List.of(), command.arguments()));
    }

    @Test
    void parseResolvesUndoKeyword() {
        ParsedCommand command = parser.parse("undo");

        assertAll(
                () -> assertEquals(CommandType.UNDO, command.commandType()),
                () -> assertEquals(List.of(), command.arguments()));
    }

    @Test
    void parseResolvesClearHistoryKeyword() {
        ParsedCommand command = parser.parse("clear_history");

        assertAll(
                () -> assertEquals(CommandType.CLEAR_HISTORY, command.commandType()),
                () -> assertEquals(List.of(), command.arguments()));
    }

    @Test
    void toCommandBuildsAddProductCommand() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("P001", "Monitor", 799.99));

        Command command = parser.toCommand(parser.parse("add P001"));
        command.execute(session);

        Product added = session.getCart().getAllItems()[0].getProduct();
        assertAll(
                () -> assertTrue(command instanceof AddProductCommand,
                        "toCommand should build an AddProductCommand"),
                () -> assertSame(session.getProductCatalog().findByCode("P001"), added),
                () -> assertEquals("P001", added.getCode()));
    }

    @Test
    void toCommandBuildsRegisterProductCommand() {
        UserSession session = new UserSession(new ProductCatalog());

        Command command = parser.toCommand(parser.parse("register PRG7 Keyboard 149.99"));
        command.execute(session);

        Product registered = session.getProductCatalog().findByCode("PRG7");
        assertAll(
                () -> assertTrue(command instanceof RegisterProductCommand,
                        "toCommand should build a RegisterProductCommand"),
                () -> assertEquals("Keyboard", registered.getName()),
                () -> assertEquals(149.99, registered.getPrice()));
    }

    @Test
    void toCommandBuildsUnregisterProductCommand() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PRU7", "Removable", 5.0));

        Command command = parser.toCommand(parser.parse("unregister PRU7"));
        command.execute(session);

        assertAll(
                () -> assertTrue(command instanceof UnregisterProductCommand,
                        "toCommand should build an UnregisterProductCommand"),
                () -> assertNull(session.getProductCatalog().findByCode("PRU7")));
    }

    @Test
    void toCommandBuildsRemoveProductCommand() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PRM7", "Removable", 5.0));
        session.executeCommand(new AddProductCommand("PRM7"));

        Command command = parser.toCommand(parser.parse("remove PRM7"));
        command.execute(session);

        assertAll(
                () -> assertTrue(command instanceof RemoveProductCommand,
                        "toCommand should build a RemoveProductCommand"),
                () -> assertEquals(0, session.getCart().getSize()));
    }

    @Test
    void toCommandRejectsRemoveProductWithWrongArgumentCount() {
        ParsedCommand noArgs = new ParsedCommand(CommandType.REMOVE_PRODUCT, List.of());
        ParsedCommand twoArgs = new ParsedCommand(CommandType.REMOVE_PRODUCT, List.of("P001", "P002"));

        CommandFormatException missing = assertThrows(
                CommandFormatException.class, () -> parser.toCommand(noArgs));
        CommandFormatException tooMany = assertThrows(
                CommandFormatException.class, () -> parser.toCommand(twoArgs));

        assertAll(
                () -> assertTrue(missing.getMessage().contains("Missing arguments")),
                () -> assertTrue(missing.getMessage().contains(CommandType.REMOVE_PRODUCT.getSyntax())),
                () -> assertTrue(tooMany.getMessage().contains("Too many arguments")),
                () -> assertTrue(tooMany.getMessage().contains(CommandType.REMOVE_PRODUCT.getSyntax())));
    }

    @Test
    void toCommandThrowsOnNonNumericPriceForRegister() {
        ParsedCommand command = new ParsedCommand(CommandType.REGISTER_PRODUCT, List.of("R001", "Keyboard", "abc"));

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.REGISTER_PRODUCT.getSyntax()));
        assertInstanceOf(NumberFormatException.class, exception.getCause(),
                "Original NumberFormatException should be chained as the cause");
    }

    @Test
    void toCommandRejectsPricesRejectedByProductValidation() {
        ParsedCommand negative = new ParsedCommand(CommandType.REGISTER_PRODUCT,
                List.of("R001", "Keyboard", "-5.0"));
        ParsedCommand notANumber = new ParsedCommand(CommandType.REGISTER_PRODUCT,
                List.of("R001", "Keyboard", "NaN"));

        IllegalArgumentException negativeError = assertThrows(IllegalArgumentException.class,
                () -> parser.toCommand(negative));
        IllegalArgumentException notANumberError = assertThrows(IllegalArgumentException.class,
                () -> parser.toCommand(notANumber));

        assertAll(
                () -> assertTrue(negativeError.getMessage().contains("Price cannot be negative or infinite")),
                () -> assertTrue(notANumberError.getMessage().contains("Price cannot be negative or infinite")));
    }

    @Test
    void toCommandThrowsForNonCommandTypes() {
        for (CommandType type : CommandType.values()) {
            if (type.getTarget() == CommandType.Target.COMMAND) {
                continue;
            }

            ParsedCommand command = new ParsedCommand(type, List.of());

            UnknownCommandException exception = assertThrows(
                    UnknownCommandException.class,
                    () -> parser.toCommand(command),
                    "toCommand should reject " + type.getKeyword());
            assertTrue(exception.getMessage().contains(type.getKeyword()));
        }
    }
}
