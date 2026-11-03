package pl.sborodziuk.javamarkt.model;

public class Product implements Sellable {
    private final String code;
    private final String name;
    private final double price;

    public Product(String code, String name, double price) {
        if (code == null || code.isBlank()) {
            throw new IllegalArgumentException("Product code cannot be blank.");
        }
        if (name == null || name.isBlank()) {
            throw new IllegalArgumentException("Product name cannot be blank.");
        }
        if (!(Double.isFinite(price) && price >= 0)) {
            throw new IllegalArgumentException("Price cannot be negative or infinite");
        }

        this.code = code.trim();
        this.name = name.trim();
        this.price = price;
    }

    @Override
    public String getCode() {
        return code;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getPrice() {
        return price;
    }
}
