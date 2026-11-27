package pl.sborodziuk.javamarkt.session;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.CommandVisitor;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
import pl.sborodziuk.javamarkt.command.RemoveProductCommand;
import pl.sborodziuk.javamarkt.command.UnregisterProductCommand;
import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;

import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.*;

class UserSessionTest {

    @Test
    void getCartReturnsSameInstanceEachCall() {
        UserSession session = new UserSession(new ProductCatalog());

        assertSame(session.getCart(), session.getCart());
    }

    @Test
    void getCatalogReturnsProvidedCatalogInstance() {
        ProductCatalog catalog = new ProductCatalog();
        UserSession session = new UserSession(catalog);

        assertSame(catalog, session.getProductCatalog());
    }

    @Test
    void constructorRejectsNullCatalog() {
        assertThrows(IllegalArgumentException.class, () -> new UserSession(null));
    }

    @Test
    void executeCommandRejectsNullCommand() {
        UserSession session = new UserSession(new ProductCatalog());

        assertThrows(IllegalArgumentException.class, () -> session.executeCommand(null));

        assertTrue(session.getHistory().isEmpty());
    }

    @Test
    void executeCommandRunsCommandAgainstThisSession() {
        UserSession session = new UserSession(new ProductCatalog());
        AtomicReference<UserSession> captured = new AtomicReference<>();

        session.executeCommand(new Command() {
            @Override
            public void execute(UserSession target) {
                captured.set(target);
            }

            @Override
            public void undo(UserSession target) {
            }

            @Override
            public <T> T accept(CommandVisitor<T> visitor) {
                throw new IllegalArgumentException(
                        "Unhandled command type: " + getClass().getSimpleName());
            }
        });

        assertSame(session, captured.get());
    }

    @Test
    void executeCommandAppliesCommandEffectToCart() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("P001", "Monitor", 799.99));

        session.executeCommand(new AddProductCommand("P001"));

        assertAll(
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("P001", session.getCart().getAllItems()[0].getProduct().getCode()));
    }

    @Test
    void executeCommandRecordsCommandsInSubmissionOrder() {
        UserSession session = new UserSession(new ProductCatalog());
        Command first = new Command() {
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
        session.getProductCatalog().addProduct(new Product("PSU1", "Monitor", 799.99));
        AddProductCommand second = new AddProductCommand("PSU1");

        session.executeCommand(first);
        session.executeCommand(second);

        List<Command> history = session.getHistory();
        assertAll(
                () -> assertEquals(2, history.size()),
                () -> assertSame(first, history.get(0)),
                () -> assertSame(second, history.get(1)));
    }

    @Test
    void executeCommandDoesNotRecordCommandThatThrows() {
        UserSession session = new UserSession(new ProductCatalog());
        Command failing = new Command() {
            @Override
            public void execute(UserSession target) {
                throw new IllegalArgumentException("Rejected");
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

        assertThrows(IllegalArgumentException.class, () -> session.executeCommand(failing));

        assertTrue(session.getHistory().isEmpty());
    }

    @Test
    void getHistorySnapshotIsImmutable() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PSU2", "Monitor", 799.99));
        session.executeCommand(new AddProductCommand("PSU2"));

        List<Command> snapshot = session.getHistory();

        assertThrows(UnsupportedOperationException.class, () -> snapshot.add(snapshot.get(0)));
    }

    @Test
    void getHistorySnapshotIsIsolatedFromLaterExecutions() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PSU3", "Monitor", 799.99));
        session.getProductCatalog().addProduct(new Product("PSU4", "Keyboard", 149.99));
        session.executeCommand(new AddProductCommand("PSU3"));

        List<Command> snapshot = session.getHistory();
        session.executeCommand(new AddProductCommand("PSU4"));

        assertAll(
                () -> assertEquals(1, snapshot.size()),
                () -> assertEquals(2, session.getHistory().size()));
    }

    @Test
    void undoLastCommandReturnsNullOnEmptyHistory() {
        UserSession session = new UserSession(new ProductCatalog());

        assertNull(session.undoLastCommand());

        assertTrue(session.getHistory().isEmpty());
    }

    @Test
    void undoLastCommandReversesLastRegister() {
        UserSession session = new UserSession(new ProductCatalog());
        RegisterProductCommand command = new RegisterProductCommand("URG1", "Keyboard", 149.99);
        session.executeCommand(command);

        Command undone = session.undoLastCommand();

        assertAll(
                () -> assertSame(command, undone),
                () -> assertTrue(session.getProductCatalog().isEmpty()),
                () -> assertTrue(session.getHistory().isEmpty()));
    }

    @Test
    void undoLastCommandRestoresUnregisteredProduct() {
        UserSession session = new UserSession(new ProductCatalog());
        RegisterProductCommand register = new RegisterProductCommand("URG2", "Keyboard", 149.99);
        session.executeCommand(register);
        session.executeCommand(new UnregisterProductCommand("URG2"));

        session.undoLastCommand();

        Product restored = session.getProductCatalog().findByCode("URG2");
        assertAll(
                () -> assertEquals("Keyboard", restored.getName()),
                () -> assertEquals(149.99, restored.getPrice()),
                () -> assertEquals(1, session.getHistory().size()),
                () -> assertSame(register, session.getHistory().get(0)));
    }

    @Test
    void undoLastCommandReversesAddProduct() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("USC1", "Monitor", 100.0));
        Command command = new AddProductCommand("USC1");
        session.executeCommand(command);

        Command undone = session.undoLastCommand();

        assertAll(
                () -> assertSame(command, undone),
                () -> assertEquals(0, session.getCart().getSize()),
                () -> assertTrue(session.getHistory().isEmpty()));
    }

    @Test
    void undoLastCommandRestoresRemovedProduct() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("USC2", "Keyboard", 149.99));
        session.executeCommand(new AddProductCommand("USC2"));
        Command remove = new RemoveProductCommand("USC2");
        session.executeCommand(remove);

        Command undone = session.undoLastCommand();

        assertAll(
                () -> assertSame(remove, undone),
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("USC2", session.getCart().getAllItems()[0].getProduct().getCode()),
                () -> assertEquals(1, session.getHistory().size()));
    }

    @Test
    void undoLastCommandUnwindsMultipleCommandsInLifoOrder() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("USC3", "Monitor", 100.0));
        session.getProductCatalog().addProduct(new Product("USC4", "Keyboard", 149.99));
        Command first = new AddProductCommand("USC3");
        Command second = new AddProductCommand("USC4");
        Command third = new AddProductCommand("USC3");
        session.executeCommand(first);
        session.executeCommand(second);
        session.executeCommand(third);

        Command undoneThird = session.undoLastCommand();
        int sizeAfterFirstUndo = session.getCart().getSize();
        Command undoneSecond = session.undoLastCommand();
        int sizeAfterSecondUndo = session.getCart().getSize();
        String remainingCode = session.getCart().getAllItems()[0].getProduct().getCode();
        Command undoneFirst = session.undoLastCommand();

        assertAll(
                () -> assertSame(third, undoneThird),
                () -> assertEquals(2, sizeAfterFirstUndo),
                () -> assertSame(second, undoneSecond),
                () -> assertEquals(1, sizeAfterSecondUndo),
                () -> assertEquals("USC3", remainingCode),
                () -> assertSame(first, undoneFirst),
                () -> assertEquals(0, session.getCart().getSize()),
                () -> assertTrue(session.getHistory().isEmpty()));
    }

    @Test
    void undoLastCommandPropagatesUnsupportedUndoAndRetainsEntry() {
        UserSession session = new UserSession(new ProductCatalog());
        Command blocked = new Command() {
            @Override
            public void execute(UserSession target) {
            }

            @Override
            public void undo(UserSession target) {
                throw new UnsupportedOperationException("Cannot undo");
            }

            @Override
            public <T> T accept(CommandVisitor<T> visitor) {
                throw new IllegalArgumentException(
                        "Unhandled command type: " + getClass().getSimpleName());
            }
        };
        session.executeCommand(blocked);

        assertThrows(UnsupportedOperationException.class, () -> session.undoLastCommand());

        List<Command> history = session.getHistory();
        assertAll(
                () -> assertEquals(1, history.size()),
                () -> assertSame(blocked, history.get(0)));
    }

    @Test
    void clearHistoryEmptiesHistory() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PSU5", "Monitor", 799.99));
        session.executeCommand(new AddProductCommand("PSU5"));

        session.clearHistory();

        assertTrue(session.getHistory().isEmpty());
    }

    @Test
    void undoLastCommandReturnsNullAfterClear() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PSU6", "Monitor", 799.99));
        session.executeCommand(new AddProductCommand("PSU6"));

        session.clearHistory();

        assertNull(session.undoLastCommand());
    }

    @Test
    void clearHistoryKeepsCartAndCatalogIntact() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PSU7", "Monitor", 799.99));
        session.executeCommand(new AddProductCommand("PSU7"));

        session.clearHistory();

        assertAll(
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("PSU7", session.getCart().getAllItems()[0].getProduct().getCode()),
                () -> assertEquals("Monitor", session.getProductCatalog().findByCode("PSU7").getName()));
    }
}
