package pl.sborodziuk.javamarkt.session;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.CommandVisitor;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
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

        session.executeCommand(new AddProductCommand("P001", "Monitor", 799.99));

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
        AddProductCommand second = new AddProductCommand("PSU1", "Monitor", 799.99);

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
        session.executeCommand(new AddProductCommand("PSU2", "Monitor", 799.99));

        List<Command> snapshot = session.getHistory();

        assertThrows(UnsupportedOperationException.class, () -> snapshot.add(snapshot.get(0)));
    }

    @Test
    void getHistorySnapshotIsIsolatedFromLaterExecutions() {
        UserSession session = new UserSession(new ProductCatalog());
        session.executeCommand(new AddProductCommand("PSU3", "Monitor", 799.99));

        List<Command> snapshot = session.getHistory();
        session.executeCommand(new AddProductCommand("PSU4", "Keyboard", 149.99));

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
}
