package pl.sborodziuk.javamarkt.model;

import java.util.Comparator;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class ProductCatalog implements Iterable<Product> {
    private static ProductCatalog instance;

    private final Set<Product> products;

    private ProductCatalog() {
        this.products = new TreeSet<>(Comparator.comparing(Product::getCode));
    }

    public static ProductCatalog getInstance() {
        if (instance == null) {
            instance = new ProductCatalog();
        }
        return instance;
    }

    public void addProduct(Product product) {
        if (product == null) {
            throw new IllegalArgumentException("Product cannot be null.");
        }
        if (!products.add(product)) {
            throw new IllegalArgumentException(
                    "Product with code " + product.getCode() + " already exists.");
        }
    }

    public boolean removeProduct(String code) {
        if (code == null || code.isBlank()) {
            throw new IllegalArgumentException("Product code cannot be blank.");
        }
        Product product = findByCode(code);
        return product != null && products.remove(product);
    }

    public Product findByCode(String code) {
        if (code == null || code.isBlank()) {
            return null;
        }
        for (Product product : products) {
            if (product.getCode().equals(code.trim())) {
                return product;
            }
        }
        return null;
    }

    public Product[] getAllProducts() {
        return products.toArray(new Product[0]);
    }

    public int getSize() {
        return products.size();
    }

    public boolean isEmpty() {
        return products.isEmpty();
    }

    @Override
    public Iterator<Product> iterator() {
        return products.iterator();
    }
}
