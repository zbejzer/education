package pl.sborodziuk.javamarkt.ui.tui;

import java.util.List;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
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
        ParsedCommand command = parser.parse("help   extra arguments");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.commandType()),
                () -> assertEquals(List.of("extra", "arguments"), command.arguments()));
    }

    @Test
    void parseTokenizesArgumentsOnWhitespace() {
        ParsedCommand command = parser.parse("help a  b");

        assertEquals(List.of("a", "b"), command.arguments());
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
    void parseResolvesAddProductKeywordWithArguments() {
        ParsedCommand command = parser.parse("add P001 Monitor 799.99");

        assertAll(
                () -> assertEquals(CommandType.ADD_PRODUCT, command.commandType()),
                () -> assertEquals(List.of("P001", "Monitor", "799.99"), command.arguments()));
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
    void toCommandBuildsAddProductCommand() {
        UserSession session = new UserSession(new ProductCatalog());

        Command command = parser.toCommand(parser.parse("add P001 Monitor 799.99"));
        command.execute(session);

        Product added = session.getCart().getAllItems()[0].getProduct();
        assertAll(
                () -> assertTrue(command instanceof AddProductCommand,
                        "toCommand should build an AddProductCommand"),
                () -> assertEquals("P001", added.getCode()),
                () -> assertEquals("Monitor", added.getName()),
                () -> assertEquals(799.99, added.getPrice()));
    }

    @Test
    void toCommandThrowsOnMissingArguments() {
        ParsedCommand command = new ParsedCommand(CommandType.ADD_PRODUCT, List.of());

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.ADD_PRODUCT.getSyntax()));
    }

    @Test
    void toCommandThrowsOnIncompleteArguments() {
        ParsedCommand command = new ParsedCommand(CommandType.ADD_PRODUCT, List.of("P001", "Monitor"));

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.ADD_PRODUCT.getSyntax()));
    }

    @Test
    void toCommandThrowsOnNonNumericPrice() {
        ParsedCommand command = new ParsedCommand(CommandType.ADD_PRODUCT, List.of("P001", "Monitor", "abc"));

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.ADD_PRODUCT.getSyntax()));
        assertInstanceOf(NumberFormatException.class, exception.getCause(),
                "Original NumberFormatException should be chained as the cause");
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
    void toCommandThrowsOnMissingArgumentsForRegister() {
        ParsedCommand command = new ParsedCommand(CommandType.REGISTER_PRODUCT, List.of());

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.REGISTER_PRODUCT.getSyntax()));
    }

    @Test
    void toCommandThrowsOnIncompleteArgumentsForRegister() {
        ParsedCommand command = new ParsedCommand(CommandType.REGISTER_PRODUCT, List.of("R001", "Keyboard"));

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.REGISTER_PRODUCT.getSyntax()));
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
    void toCommandThrowsOnMissingArgumentsForUnregister() {
        ParsedCommand command = new ParsedCommand(CommandType.UNREGISTER_PRODUCT, List.of());

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.UNREGISTER_PRODUCT.getSyntax()));
    }

    @Test
    void toCommandThrowsOnExtraArgumentsForUnregister() {
        ParsedCommand command = new ParsedCommand(CommandType.UNREGISTER_PRODUCT, List.of("R001", "extra"));

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.UNREGISTER_PRODUCT.getSyntax()));
    }

    @Test
    void toCommandThrowsOnExtraArguments() {
        ParsedCommand command = new ParsedCommand(
                CommandType.ADD_PRODUCT, List.of("P001", "Monitor", "799.99", "extra"));

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> parser.toCommand(command));
        assertTrue(exception.getMessage().contains(CommandType.ADD_PRODUCT.getSyntax()));
    }

    @Test
    void toCommandThrowsForTuiCommandTypes() {
        for (CommandType type : CommandType.values()) {
            if (type.getTarget() != CommandType.Target.TUI) {
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
