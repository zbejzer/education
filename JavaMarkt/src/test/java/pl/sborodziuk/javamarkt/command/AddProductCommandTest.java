package pl.sborodziuk.javamarkt.command;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.model.CartItem;
import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class AddProductCommandTest {

    @Test
    void constructionRejectsBlankCode() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new AddProductCommand(null)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new AddProductCommand("")),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new AddProductCommand("   ")));
    }

    @Test
    void executeAddsCatalogInstanceToCart() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("P001", "Monitor", 799.99));

        AddProductCommand command = new AddProductCommand("P001");
        command.execute(session);

        CartItem item = session.getCart().getAllItems()[0];
        assertAll(
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertSame(session.getProductCatalog().findByCode("P001"), item.getProduct()),
                () -> assertEquals("P001", item.getProduct().getCode()),
                () -> assertEquals(799.99, item.getDiscountPrice()));
    }

    @Test
    void executeTwiceCreatesTwoEntriesAndUndoRemovesOne() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("P003", "Mouse", 100.0));
        AddProductCommand command = new AddProductCommand("P003");

        command.execute(session);
        command.execute(session);

        int sizeAfterTwoAdds = session.getCart().getSize();
        command.undo(session);

        assertAll(
                () -> assertEquals(2, sizeAfterTwoAdds),
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertSame(session.getProductCatalog().findByCode("P003"),
                        session.getCart().getAllItems()[0].getProduct()));
    }

    @Test
    void executeThrowsForUnregisteredCode() {
        UserSession session = new UserSession(new ProductCatalog());

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> new AddProductCommand("P001").execute(session));

        assertAll(
                () -> assertTrue(exception.getMessage().contains("P001")),
                () -> assertEquals(0, session.getCart().getSize(),
                        "Failed add must never touch the cart"));
    }

    @Test
    void undoRemovesTheAddedProductFromCart() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("P001", "Monitor", 799.99));
        AddProductCommand command = new AddProductCommand("P001");
        command.execute(session);

        command.undo(session);

        assertAll(
                () -> assertEquals(0, session.getCart().getSize()),
                () -> assertEquals(0, session.getCart().getAllItems().length));
    }

    @Test
    void undoThrowsAndKeepsCartIntactWhenProductIsAbsent() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("P002", "Keyboard", 149.50));
        session.executeCommand(new AddProductCommand("P002"));
        AddProductCommand command = new AddProductCommand("P001");

        IllegalStateException exception = assertThrows(
                IllegalStateException.class, () -> command.undo(session));

        assertAll(
                () -> assertTrue(exception.getMessage().contains("P001")),
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("P002", session.getCart().getAllItems()[0].getProduct().getCode()));
    }
}
