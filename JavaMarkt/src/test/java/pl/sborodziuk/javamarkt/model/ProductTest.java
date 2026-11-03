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
    void constructorAcceptsZeroPrice() {
        Product product = new Product("P003", "Free sample", 0.0);

        assertEquals(0.0, product.getPrice());
    }

    @Test
    void constructorRejectsNegativePrice() {
        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> new Product("P004", "Invalid", -10.0)
        );
        assertEquals("Price cannot be negative or infinite", exception.getMessage());
    }

    @Test
    void constructorRejectsNonFinitePrice() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new Product("P004", "NaN item", Double.NaN)),
                () -> assertThrows(IllegalArgumentException.class,
                        () -> new Product("P004", "Infinite item", Double.POSITIVE_INFINITY))
        );
    }

    @Test
    void constructorRejectsBlankCode() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class, () -> new Product(null, "Monitor", 1.0)),
                () -> assertThrows(IllegalArgumentException.class, () -> new Product("", "Monitor", 1.0)),
                () -> assertThrows(IllegalArgumentException.class, () -> new Product("   ", "Monitor", 1.0))
        );
    }

    @Test
    void constructorRejectsBlankName() {
        assertAll(
                () -> assertThrows(IllegalArgumentException.class, () -> new Product("P001", null, 1.0)),
                () -> assertThrows(IllegalArgumentException.class, () -> new Product("P001", "", 1.0)),
                () -> assertThrows(IllegalArgumentException.class, () -> new Product("P001", "   ", 1.0))
        );
    }

    @Test
    void constructorTrimsSurroundingWhitespaceFromCodeAndName() {
        Product product = new Product("  P001  ", "  Monitor  ", 100.0);

        assertAll(
                () -> assertEquals("P001", product.getCode()),
                () -> assertEquals("Monitor", product.getName()));
    }
}
