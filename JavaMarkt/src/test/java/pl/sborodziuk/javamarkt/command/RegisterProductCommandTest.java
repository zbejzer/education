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
}
