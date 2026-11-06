package pl.sborodziuk.javamarkt.ui.tui;

import java.util.List;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.CommandVisitor;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
import pl.sborodziuk.javamarkt.command.UnregisterProductCommand;
import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class CommandDescriberTest {

    private final CommandDescriber describer = new CommandDescriber();
    private final Parser parser = new Parser();

    @Test
    void parseDescribesAddProductCommand() {
        ParsedCommand parsed = describer.parse(new AddProductCommand("P001", "Monitor", 799.99));

        assertAll(
                () -> assertEquals(CommandType.ADD_PRODUCT, parsed.commandType()),
                () -> assertEquals(List.of("P001", "Monitor", "799.99"), parsed.arguments()));
    }

    @Test
    void parseDescribesRegisterProductCommand() {
        ParsedCommand parsed = describer.parse(new RegisterProductCommand("R001", "Keyboard", 149.99));

        assertAll(
                () -> assertEquals(CommandType.REGISTER_PRODUCT, parsed.commandType()),
                () -> assertEquals(List.of("R001", "Keyboard", "149.99"), parsed.arguments()));
    }

    @Test
    void parseDescribesUnregisterProductCommand() {
        ParsedCommand parsed = describer.parse(new UnregisterProductCommand("R001"));

        assertAll(
                () -> assertEquals(CommandType.UNREGISTER_PRODUCT, parsed.commandType()),
                () -> assertEquals(List.of("R001"), parsed.arguments()));
    }

    @Test
    void parseThrowsOnUnhandledCommandType() {
        Command unknown = new Command() {
            @Override
            public void execute(UserSession target) {
            }

            @Override
            public void undo(UserSession target) {
            }

            @Override
            public <T> T accept(CommandVisitor<T> visitor) {
                throw new IllegalArgumentException(
                        "Unhandled command type: " + getClass().getSimpleName());
            }
        };

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class,
                () -> describer.parse(unknown));

        assertTrue(exception.getMessage().contains("Unhandled command type"));
    }

    @Test
    void describeEntryRendersAddProductEntry() {
        String entry = describer.describeEntry(describer.parse(new AddProductCommand("P001", "Monitor", 799.99)));

        assertEquals("add P001 Monitor 799.99", entry);
    }

    @Test
    void describeEntryRendersRegisterProductEntry() {
        String entry = describer.describeEntry(describer.parse(new RegisterProductCommand("R001", "Keyboard", 149.99)));

        assertEquals("register R001 Keyboard 149.99", entry);
    }

    @Test
    void describeEntryRendersUnregisterProductEntry() {
        String entry = describer.describeEntry(describer.parse(new UnregisterProductCommand("R001")));

        assertEquals("unregister R001", entry);
    }

    @Test
    void describedAddProductCommandRoundTripsThroughParser() {
        UserSession session = new UserSession(new ProductCatalog());

        Command command = parser.toCommand(describer.parse(new AddProductCommand("P001", "Monitor", 799.99)));
        command.execute(session);

        Product added = session.getCart().getAllItems()[0].getProduct();
        assertAll(
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("P001", added.getCode()),
                () -> assertEquals("Monitor", added.getName()),
                () -> assertEquals(799.99, added.getPrice()));
    }

    @Test
    void describedRegisterProductCommandRoundTripsThroughParser() {
        UserSession session = new UserSession(new ProductCatalog());

        Command command = parser.toCommand(describer.parse(new RegisterProductCommand("R001", "Keyboard", 149.99)));
        command.execute(session);

        Product registered = session.getProductCatalog().findByCode("R001");
        assertAll(
                () -> assertEquals("Keyboard", registered.getName()),
                () -> assertEquals(149.99, registered.getPrice()));
    }

    @Test
    void describedUnregisterProductCommandRoundTripsThroughParser() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("R001", "Keyboard", 149.99));

        Command command = parser.toCommand(describer.parse(new UnregisterProductCommand("R001")));
        command.execute(session);

        assertNull(session.getProductCatalog().findByCode("R001"));
    }
}
