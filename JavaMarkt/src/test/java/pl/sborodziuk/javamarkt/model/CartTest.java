package pl.sborodziuk.javamarkt.model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CartTest {

    @Test
    void newCartIsEmpty() {
        Cart cart = new Cart();

        assertEquals(0, cart.getProductCount());
        assertEquals(0, cart.getProducts().length);
    }

    @Test
    void addProductIncrementsProductCount() {
        Cart cart = new Cart();

        cart.addProduct(new Product("P001", "Monitor", 799.99));
        cart.addProduct(new Product("P002", "Keyboard", 149.50));

        assertEquals(2, cart.getProductCount());
    }

    @Test
    void addProductStoresProductsInInsertionOrder() {
        Cart cart = new Cart();
        Product first = new Product("P001", "Monitor", 799.99);
        Product second = new Product("P002", "Keyboard", 149.50);

        cart.addProduct(first);
        cart.addProduct(second);

        assertAll(
                () -> assertSame(first, cart.getProducts()[0]),
                () -> assertSame(second, cart.getProducts()[1]),
                () -> assertEquals(2, cart.getProducts().length)
        );
    }

    @Test
    void addProductRecalculatesDiscountPriceForAddedProduct() {
        Cart cart = new Cart();
        Product product = new Product("P003", "Mouse", 100.0);
        product.setDiscountPrice(50.0);

        cart.addProduct(product);

        assertEquals(100.0, cart.getProducts()[0].getDiscountPrice());
    }

    @Test
    void recalculateResetsDiscountPriceToPriceForAllProducts() {
        Cart cart = new Cart();
        Product product = new Product("P004", "Headphones", 200.0);
        Product product2 = new Product("P005", "Webcam", 300.0);
        cart.addProduct(product);
        cart.addProduct(product2);

        product.setDiscountPrice(99.0);
        product2.setDiscountPrice(1.0);
        cart.recalculate();

        assertAll(
                () -> assertEquals(200.0, cart.getProducts()[0].getDiscountPrice()),
                () -> assertEquals(300.0, cart.getProducts()[1].getDiscountPrice())
        );
    }

    @Test
    void recalculateDoesNotChangeBasePrice() {
        Cart cart = new Cart();
        Product product = new Product("P006", "USB hub", 80.0);
        cart.addProduct(product);

        cart.recalculate();

        assertEquals(80.0, cart.getProducts()[0].getPrice());
    }

    @Test
    void recalculateOnEmptyCartDoesNotThrow() {
        Cart cart = new Cart();

        assertDoesNotThrow(cart::recalculate);
    }
}
