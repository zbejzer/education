package pl.sborodziuk.javamarkt.command;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.model.CartItem;
import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class AddProductCommandTest {

    @Test
    void executeAddsProductToSessionCart() {
        UserSession session = new UserSession();
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
    void executeRejectsInvalidProductAndLeavesCartUnchanged() {
        UserSession session = new UserSession();
        AddProductCommand command = new AddProductCommand("P001", "Monitor", -10.0);

        assertThrows(IllegalArgumentException.class, () -> command.execute(session));
        assertEquals(0, session.getCart().getSize());
    }

    @Test
    void undoIsNotImplemented() {
        UserSession session = new UserSession();
        AddProductCommand command = new AddProductCommand("P001", "Monitor", 799.99);

        assertThrows(UnsupportedOperationException.class, () -> command.undo(session));
    }
}
