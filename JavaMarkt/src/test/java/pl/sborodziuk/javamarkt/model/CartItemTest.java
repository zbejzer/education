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
    void gettersDelegateToWrappedProduct() {
        CartItem item = new CartItem(new Product("P002", "Keyboard", 149.50));

        assertAll(
                () -> assertEquals("P002", item.getCode()),
                () -> assertEquals("Keyboard", item.getName()),
                () -> assertEquals(149.50, item.getPrice()));
    }

    @Test
    void getProductReturnsWrappedProduct() {
        Product product = new Product("P003", "Mouse", 100.0);

        CartItem item = new CartItem(product);

        assertSame(product, item.getProduct());
    }

    @Test
    void setDiscountPriceUpdatesDiscountPrice() {
        CartItem item = new CartItem(new Product("P004", "Headphones", 200.0));

        item.setDiscountPrice(149.99);

        assertAll(
                () -> assertEquals(149.99, item.getDiscountPrice()),
                () -> assertEquals(200.0, item.getPrice()));
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
