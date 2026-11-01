package pl.sborodziuk.javamarkt.model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ProductTest {

    @Test
    void constructorSetsCodeNameAndPrice() {
        Product product = new Product("P001", "Monitor", 799.99);

        assertAll(
                () -> assertEquals("P001", product.getCode()),
                () -> assertEquals("Monitor", product.getName()),
                () -> assertEquals(799.99, product.getPrice())
        );
    }

    @Test
    void constructorInitializesDiscountPriceToPrice() {
        Product product = new Product("P002", "Keyboard", 149.50);

        assertEquals(product.getPrice(), product.getDiscountPrice());
    }

    @Test
    void constructorAcceptsZeroPrice() {
        Product product = new Product("P003", "Free sample", 0.0);

        assertEquals(0.0, product.getPrice());
        assertEquals(0.0, product.getDiscountPrice());
    }

    @Test
    void constructorRejectsNegativePrice() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> new Product("P004", "Invalid", -10.0)
        );
        assertEquals("Price cannot be negative", exception.getMessage());
    }

    @Test
    void setDiscountPriceUpdatesDiscountPrice() {
        Product product = new Product("P005", "Mouse", 100.0);

        product.setDiscountPrice(79.99);

        assertEquals(79.99, product.getDiscountPrice());
        assertEquals(100.0, product.getPrice());
    }

    @Test
    void setDiscountPriceAcceptsZero() {
        Product product = new Product("P006", "Promo item", 50.0);

        product.setDiscountPrice(0.0);

        assertEquals(0.0, product.getDiscountPrice());
    }

    @Test
    void setDiscountPriceRejectsNegativeValue() {
        Product product = new Product("P007", "Headphones", 200.0);

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> product.setDiscountPrice(-1.0)
        );
        assertEquals("Price cannot be negative", exception.getMessage());
        assertEquals(200.0, product.getDiscountPrice());
    }
}
