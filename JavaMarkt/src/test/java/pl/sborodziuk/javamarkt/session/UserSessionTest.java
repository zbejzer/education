package pl.sborodziuk.javamarkt.session;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.model.ProductCatalog;

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
}
