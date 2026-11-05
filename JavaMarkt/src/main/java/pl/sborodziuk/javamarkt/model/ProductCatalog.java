package pl.sborodziuk.javamarkt.model;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class ProductCatalog implements Iterable<Product> {
    private final Map<String, Product> products;

    public ProductCatalog() {
        this.products = new HashMap<>();
    }

    public void addProduct(Product product) {
        if (product == null) {
            throw new IllegalArgumentException("Product cannot be null.");
        }
        if (products.putIfAbsent(product.getCode(), product) != null) {
            throw new IllegalArgumentException(
                    "Product with code " + product.getCode() + " already exists.");
        }
    }

    public void updateProduct(Product product) {
        if (product == null) {
            throw new IllegalArgumentException("Product cannot be null.");
        }
        if (products.replace(product.getCode(), product) == null) {
            throw new IllegalArgumentException(
                    "Product with code " + product.getCode() + " does not exist.");
        }
    }

    public boolean removeProduct(String code) {
        if (code == null || code.isBlank()) {
            throw new IllegalArgumentException("Product code cannot be blank.");
        }
        return products.remove(code) != null;
    }

    public Product findByCode(String code) {
        if (code == null || code.isBlank()) {
            return null;
        }
        return products.get(code);
    }

    public Product[] getAllProducts() {
        return products.values().toArray(new Product[0]);
    }

    public int getSize() {
        return products.size();
    }

    public boolean isEmpty() {
        return products.isEmpty();
    }

    @Override
    public Iterator<Product> iterator() {
        return products.values().iterator();
    }
}
