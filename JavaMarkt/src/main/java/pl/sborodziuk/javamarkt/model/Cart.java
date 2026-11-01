package pl.sborodziuk.javamarkt.model;

import pl.sborodziuk.javamarkt.model.Product;
import static java.util.Arrays.copyOf;

public class Cart {
    private Product[] products;
    private int productCount;

    public Cart() {
        this.products = new Product[0];
        this.productCount = 0;
    }

    public Product[] getProducts() {
        return products;
    }

    public void addProduct(Product product) {
        products = copyOf(products, productCount + 1);
        products[productCount] = product;
        productCount++;
        recalculate();
    }

    public int getProductCount() {
        return productCount;
    }

    public void recalculate() {
        for (Product p : products) {
            p.setDiscountPrice(p.getPrice());
        }
    }
}
