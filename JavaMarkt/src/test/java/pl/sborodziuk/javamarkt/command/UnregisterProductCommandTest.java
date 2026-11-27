package pl.sborodziuk.javamarkt.command;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class UnregisterProductCommandTest {

    @Test
    void executeRemovesProductFromCatalog() {
        UserSession session = new UserSession(new ProductCatalog());
        ProductCatalog catalog = session.getProductCatalog();
        catalog.addProduct(new Product("PRU1", "Removable", 5.0));
        UnregisterProductCommand command = new UnregisterProductCommand("PRU1");

        command.execute(session);

        assertNull(catalog.findByCode("PRU1"));
    }

    @Test
    void executeThrowsForUnknownCode() {
        UserSession session = new UserSession(new ProductCatalog());
        UnregisterProductCommand command = new UnregisterProductCommand("PRU-UNKNOWN");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class, () -> command.execute(session));

        assertTrue(exception.getMessage().contains("PRU-UNKNOWN"));
    }

    @Test
    void constructionRejectsBlankCode() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new UnregisterProductCommand(null)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new UnregisterProductCommand("")),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new UnregisterProductCommand("   ")));
    }

    @Test
    void undoRestoresRemovedProduct() {
        UserSession session = new UserSession(new ProductCatalog());
        ProductCatalog catalog = session.getProductCatalog();
        catalog.addProduct(new Product("PRU2", "Removable", 5.0));
        UnregisterProductCommand command = new UnregisterProductCommand("PRU2");
        command.execute(session);

        command.undo(session);

        Product restored = catalog.findByCode("PRU2");
        assertAll(
                () -> assertEquals("Removable", restored.getName()),
                () -> assertEquals(5.0, restored.getPrice()));
    }

    @Test
    void executeAndUndoLeaveOtherCatalogProductsIntact() {
        UserSession session = new UserSession(new ProductCatalog());
        ProductCatalog catalog = session.getProductCatalog();
        catalog.addProduct(new Product("PRU6", "Removable", 5.0));
        catalog.addProduct(new Product("PRU7", "Kept", 7.0));
        UnregisterProductCommand command = new UnregisterProductCommand("PRU6");

        command.execute(session);
        boolean removedOnlyTarget = catalog.findByCode("PRU6") == null
                && catalog.findByCode("PRU7") != null;
        command.undo(session);

        assertAll(
                () -> assertTrue(removedOnlyTarget),
                () -> assertEquals("Removable", catalog.findByCode("PRU6").getName()),
                () -> assertEquals("Kept", catalog.findByCode("PRU7").getName()),
                () -> assertEquals(2, catalog.getSize()));
    }

    @Test
    void undoThrowsWhenCodeWasReRegisteredWithDifferentProduct() {
        UserSession session = new UserSession(new ProductCatalog());
        ProductCatalog catalog = session.getProductCatalog();
        catalog.addProduct(new Product("PRU3", "Original", 10.0));
        UnregisterProductCommand command = new UnregisterProductCommand("PRU3");
        command.execute(session);
        catalog.addProduct(new Product("PRU3", "Other", 20.0));

        assertThrows(IllegalArgumentException.class, () -> command.undo(session));

        assertEquals("Other", catalog.findByCode("PRU3").getName());
    }

    @Test
    void executeThrowsWhenProductIsInCart() {
        UserSession session = new UserSession(new ProductCatalog());
        ProductCatalog catalog = session.getProductCatalog();
        catalog.addProduct(new Product("PRU4", "Keyboard", 149.99));
        session.executeCommand(new AddProductCommand("PRU4"));
        UnregisterProductCommand command = new UnregisterProductCommand("PRU4");

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class, () -> command.execute(session));

        assertAll(
                () -> assertTrue(exception.getMessage().contains("PRU4")),
                () -> assertTrue(exception.getMessage().contains("in the cart")),
                () -> assertEquals("Keyboard", catalog.findByCode("PRU4").getName(),
                        "Blocked unregister must keep the catalog entry"),
                () -> assertEquals(1, session.getCart().getSize(),
                        "Blocked unregister must keep the cart"));
    }

    @Test
    void executeSucceedsAfterRemovedFromCart() {
        UserSession session = new UserSession(new ProductCatalog());
        ProductCatalog catalog = session.getProductCatalog();
        catalog.addProduct(new Product("PRU5", "Keyboard", 149.99));
        session.executeCommand(new AddProductCommand("PRU5"));
        session.executeCommand(new RemoveProductCommand("PRU5"));

        UnregisterProductCommand command = new UnregisterProductCommand("PRU5");
        command.execute(session);

        assertNull(catalog.findByCode("PRU5"));
    }
}
