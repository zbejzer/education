package pl.sborodziuk.javamarkt.command;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.model.Cart;
import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class RemoveProductCommandTest {

    @Test
    void executeRemovesProductFromCart() {
        UserSession session = new UserSession(new ProductCatalog());
        session.executeCommand(new AddProductCommand("PRM1", "Removable", 5.0));
        RemoveProductCommand command = new RemoveProductCommand("PRM1");

        command.execute(session);

        assertAll(
                () -> assertEquals(0, session.getCart().getSize()),
                () -> assertEquals(0, session.getCart().getAllItems().length));
    }

    @Test
    void executeThrowsForUnknownCode() {
        UserSession session = new UserSession(new ProductCatalog());
        session.executeCommand(new AddProductCommand("PRM2", "Kept", 5.0));
        RemoveProductCommand command = new RemoveProductCommand("PRM-UNKNOWN");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class, () -> command.execute(session));

        assertAll(
                () -> assertTrue(exception.getMessage().contains("PRM-UNKNOWN")),
                () -> assertEquals(1, session.getCart().getSize(),
                        "Failed removal must not touch the cart"));
    }

    @Test
    void constructionRejectsBlankCode() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new RemoveProductCommand(null)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new RemoveProductCommand("")),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new RemoveProductCommand("   ")));
    }

    @Test
    void undoRestoresRemovedProduct() {
        UserSession session = new UserSession(new ProductCatalog());
        session.executeCommand(new AddProductCommand("PRM3", "Removable", 5.0));
        RemoveProductCommand command = new RemoveProductCommand("PRM3");
        command.execute(session);

        command.undo(session);

        assertEquals(1, session.getCart().getSize());
        Product restored = session.getCart().getAllItems()[0].getProduct();
        assertAll(
                () -> assertEquals("PRM3", restored.getCode()),
                () -> assertEquals("Removable", restored.getName()),
                () -> assertEquals(5.0, restored.getPrice()));
    }

    @Test
    void executeReturnsFirstMatchAndUndoReattachesAtTheEnd() {
        UserSession session = new UserSession(new ProductCatalog());
        Cart cart = session.getCart();
        cart.addProduct(new Product("PRM4", "First", 1.0));
        cart.addProduct(new Product("PRM4", "Second", 2.0));
        RemoveProductCommand command = new RemoveProductCommand("PRM4");

        command.execute(session);
        command.undo(session);

        assertAll(
                () -> assertEquals(2, cart.getSize()),
                () -> assertEquals("Second", cart.getAllItems()[0].getProduct().getName()),
                () -> assertEquals("First", cart.getAllItems()[1].getProduct().getName()));
    }
}
