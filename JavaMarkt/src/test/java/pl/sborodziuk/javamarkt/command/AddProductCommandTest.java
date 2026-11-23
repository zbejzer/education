package pl.sborodziuk.javamarkt.command;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.model.CartItem;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class AddProductCommandTest {

    @Test
    void executeAddsProductToSessionCart() {
        UserSession session = new UserSession(new ProductCatalog());
        AddProductCommand command = new AddProductCommand("P001", "Monitor", 799.99);

        command.execute(session);

        CartItem item = session.getCart().getAllItems()[0];
        assertAll(
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("P001", item.getProduct().getCode()),
                () -> assertEquals("Monitor", item.getProduct().getName()),
                () -> assertEquals(799.99, item.getProduct().getPrice()),
                () -> assertEquals(799.99, item.getDiscountPrice()));
    }

    @Test
    void constructionRejectsInvalidProductArguments() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new AddProductCommand(null, "Monitor", 1.0)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new AddProductCommand("P001", "   ", 1.0)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new AddProductCommand("P001", "Monitor", -10.0)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new AddProductCommand("P001", "Monitor", Double.NaN)));
    }

    @Test
    void invalidCommandsNeverReachTheSessionCart() {
        UserSession session = new UserSession(new ProductCatalog());

        assertThrows(IllegalArgumentException.class,
                () -> new AddProductCommand("P001", "Monitor", -10.0));

        assertEquals(0, session.getCart().getSize(),
                "Rejected commands must never modify the cart");
    }

    @Test
    void undoRemovesTheAddedProductFromCart() {
        UserSession session = new UserSession(new ProductCatalog());
        AddProductCommand command = new AddProductCommand("P001", "Monitor", 799.99);
        command.execute(session);

        command.undo(session);

        assertAll(
                () -> assertEquals(0, session.getCart().getSize()),
                () -> assertEquals(0, session.getCart().getAllItems().length));
    }

    @Test
    void undoThrowsAndKeepsCartIntactWhenProductIsAbsent() {
        UserSession session = new UserSession(new ProductCatalog());
        session.executeCommand(new AddProductCommand("P002", "Keyboard", 149.50));
        AddProductCommand command = new AddProductCommand("P001", "Monitor", 799.99);

        IllegalStateException exception = assertThrows(
                IllegalStateException.class, () -> command.undo(session));

        assertAll(
                () -> assertTrue(exception.getMessage().contains("P001")),
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("P002", session.getCart().getAllItems()[0].getProduct().getCode()));
    }
}
