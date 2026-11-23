package pl.sborodziuk.javamarkt.model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CartTest {

    @Test
    void newCartIsEmpty() {
        Cart cart = new Cart();

        assertEquals(0, cart.getSize());
        assertEquals(0, cart.getAllItems().length);
    }

    @Test
    void addProductIncrementsProductCount() {
        Cart cart = new Cart();

        cart.addProduct(new Product("P001", "Monitor", 799.99));
        cart.addProduct(new Product("P002", "Keyboard", 149.50));

        assertEquals(2, cart.getSize());
    }

    @Test
    void addProductRecalculatesDiscountPriceForAddedProduct() {
        Cart cart = new Cart();
        Product product = new Product("P003", "Mouse", 100.0);
        cart.addProduct(product);
        cart.getAllItems()[0].setDiscountPrice(50.0);

        cart.addProduct(new Product("P004", "Keyboard", 149.50));

        assertEquals(100.0, cart.getAllItems()[0].getDiscountPrice());
    }

    @Test
    void recalculateResetsDiscountPriceToPriceForAllProducts() {
        Cart cart = new Cart();
        Product product = new Product("P004", "Headphones", 200.0);
        Product product2 = new Product("P005", "Webcam", 300.0);
        cart.addProduct(product);
        cart.addProduct(product2);

        cart.getAllItems()[0].setDiscountPrice(99.0);
        cart.getAllItems()[1].setDiscountPrice(1.0);
        cart.recalculate();

        assertAll(
                () -> assertEquals(200.0, cart.getAllItems()[0].getDiscountPrice()),
                () -> assertEquals(300.0, cart.getAllItems()[1].getDiscountPrice()));
    }

    @Test
    void recalculateDoesNotChangeBasePrice() {
        Cart cart = new Cart();
        Product product = new Product("P006", "USB hub", 80.0);
        cart.addProduct(product);

        cart.recalculate();

        assertEquals(80.0, cart.getAllItems()[0].getPrice());
    }

    @Test
    void recalculateOnEmptyCartDoesNotThrow() {
        Cart cart = new Cart();

        assertDoesNotThrow(cart::recalculate);
    }

    @Test
    void removeProductReturnsAndRemovesTheOnlyItem() {
        Cart cart = new Cart();
        Product product = new Product("P010", "Monitor", 799.99);
        cart.addProduct(product);

        Product removed = cart.removeProduct("P010");

        assertAll(
                () -> assertSame(product, removed),
                () -> assertEquals(0, cart.getSize()),
                () -> assertEquals(0, cart.getAllItems().length));
    }

    @Test
    void removeProductRemovesFirstItemAndKeepsOrder() {
        Cart cart = new Cart();
        Product first = new Product("P011", "Monitor", 799.99);
        Product second = new Product("P012", "Keyboard", 149.50);
        Product third = new Product("P013", "Mouse", 100.0);
        cart.addProduct(first);
        cart.addProduct(second);
        cart.addProduct(third);

        Product removed = cart.removeProduct("P011");

        assertAll(
                () -> assertSame(first, removed),
                () -> assertEquals(2, cart.getSize()),
                () -> assertSame(second, cart.getAllItems()[0].getProduct()),
                () -> assertSame(third, cart.getAllItems()[1].getProduct()));
    }

    @Test
    void removeProductRemovesFirstMatchAmongDuplicatesAndKeepsOrder() {
        Cart cart = new Cart();
        Product firstMatch = new Product("P015", "Monitor A", 799.99);
        Product secondMatch = new Product("P015", "Monitor B", 899.99);
        Product other = new Product("P016", "Keyboard", 149.50);
        cart.addProduct(firstMatch);
        cart.addProduct(secondMatch);
        cart.addProduct(other);

        Product removed = cart.removeProduct("P015");

        assertAll(
                () -> assertSame(firstMatch, removed),
                () -> assertEquals(2, cart.getSize()),
                () -> assertSame(secondMatch, cart.getAllItems()[0].getProduct()),
                () -> assertSame(other, cart.getAllItems()[1].getProduct()));
    }

    @Test
    void removeProductReturnsNullForUnknownCode() {
        Cart cart = new Cart();
        cart.addProduct(new Product("P017", "Monitor", 799.99));

        assertNull(cart.removeProduct("P018"));

        assertEquals(1, cart.getSize());
    }

    @Test
    void removeProductReturnsNullOnEmptyCart() {
        Cart cart = new Cart();

        assertNull(cart.removeProduct("P019"));
    }

    @Test
    void removeProductRejectsNullOrBlankCode() {
        Cart cart = new Cart();
        cart.addProduct(new Product("P020", "Monitor", 799.99));

        assertAll(
                () -> assertThrows(IllegalArgumentException.class, () -> cart.removeProduct(null)),
                () -> assertThrows(IllegalArgumentException.class, () -> cart.removeProduct("")),
                () -> assertThrows(IllegalArgumentException.class, () -> cart.removeProduct("   ")),
                () -> assertEquals(1, cart.getSize(), "Rejected removals must not touch the cart"));
    }

    @Test
    void removeProductRecalculatesDiscountPricesOfRemainingItems() {
        Cart cart = new Cart();
        Product kept = new Product("P021", "Monitor", 799.99);
        Product dropped = new Product("P022", "Keyboard", 149.50);
        cart.addProduct(kept);
        cart.addProduct(dropped);
        cart.getAllItems()[0].setDiscountPrice(50.0);

        cart.removeProduct("P022");

        assertEquals(799.99, cart.getAllItems()[0].getDiscountPrice());
    }
}
