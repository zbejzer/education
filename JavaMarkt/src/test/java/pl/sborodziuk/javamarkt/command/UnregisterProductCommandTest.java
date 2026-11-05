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
}
