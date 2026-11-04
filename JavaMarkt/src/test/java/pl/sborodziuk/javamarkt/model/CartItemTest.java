package pl.sborodziuk.javamarkt.model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CartItemTest {

    @Test
    void constructorInitializesDiscountPriceToProductPrice() {
        CartItem item = new CartItem(new Product("P001", "Monitor", 799.99));

        assertEquals(799.99, item.getDiscountPrice());
    }

    @Test
    void setDiscountPriceAcceptsZero() {
        CartItem item = new CartItem(new Product("P005", "Promo item", 50.0));

        item.setDiscountPrice(0.0);

        assertEquals(0.0, item.getDiscountPrice());
    }

    @Test
    void setDiscountPriceRejectsNegativeValue() {
        CartItem item = new CartItem(new Product("P006", "Webcam", 300.0));

        IllegalArgumentException exception = assertThrows(
                IllegalArgumentException.class,
                () -> item.setDiscountPrice(-1.0));

        assertAll(
                () -> assertEquals("Discount price cannot be negative", exception.getMessage()),
                () -> assertEquals(300.0, item.getDiscountPrice()));
    }
}
