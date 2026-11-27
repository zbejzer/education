package pl.sborodziuk.javamarkt.command;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;

import static org.junit.jupiter.api.Assertions.*;

class RegisterProductCommandTest {

    @Test
    void executeRegistersProductInCatalog() {
        UserSession session = new UserSession(new ProductCatalog());
        RegisterProductCommand command = new RegisterProductCommand("PRG1", "Keyboard", 149.99);

        command.execute(session);

        Product registered = session.getProductCatalog().findByCode("PRG1");
        assertAll(
                () -> assertEquals("Keyboard", registered.getName()),
                () -> assertEquals(149.99, registered.getPrice()));
    }

    @Test
    void executeRejectsDuplicateCodeAndKeepsOriginal() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PRG2", "Original", 10.0));
        RegisterProductCommand command = new RegisterProductCommand("PRG2", "Duplicate", 99.0);

        assertThrows(IllegalArgumentException.class, () -> command.execute(session));

        assertEquals("Original", session.getProductCatalog().findByCode("PRG2").getName());
    }

    @Test
    void constructionRejectsInvalidProductArguments() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new RegisterProductCommand(null, "Keyboard", 1.0)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new RegisterProductCommand("PRG3", "   ", 1.0)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new RegisterProductCommand("PRG3", "Keyboard", -10.0)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new RegisterProductCommand("PRG3", "Keyboard", Double.NaN)));
    }

    @Test
    void undoRemovesRegisteredProductFromCatalog() {
        UserSession session = new UserSession(new ProductCatalog());
        RegisterProductCommand command = new RegisterProductCommand("PRG4", "Keyboard", 149.99);
        command.execute(session);

        command.undo(session);

        assertTrue(session.getProductCatalog().isEmpty());
    }

    @Test
    void undoLeavesOtherProductsInCatalog() {
        UserSession session = new UserSession(new ProductCatalog());
        session.getProductCatalog().addProduct(new Product("PRG5", "Existing", 10.0));
        RegisterProductCommand command = new RegisterProductCommand("PRG6", "Keyboard", 149.99);
        command.execute(session);

        command.undo(session);

        Product existing = session.getProductCatalog().findByCode("PRG5");
        assertAll(
                () -> assertNull(session.getProductCatalog().findByCode("PRG6")),
                () -> assertEquals("Existing", existing.getName()),
                () -> assertEquals(1, session.getProductCatalog().getSize()));
    }

    @Test
    void undoThrowsWhenProductIsMissingFromCatalog() {
        UserSession session = new UserSession(new ProductCatalog());
        RegisterProductCommand command = new RegisterProductCommand("PRG8", "Keyboard", 149.99);

        IllegalStateException exception = assertThrows(
                IllegalStateException.class, () -> command.undo(session));

        assertTrue(exception.getMessage().contains("PRG8"));
    }
}
