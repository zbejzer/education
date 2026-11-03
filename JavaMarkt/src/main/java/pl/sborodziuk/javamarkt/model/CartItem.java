package pl.sborodziuk.javamarkt.model;

public class CartItem implements Sellable {
    private final Product product;
    private double discountPrice;

    public CartItem(Product product) {
        this.product = product;
        this.discountPrice = product.getPrice();
    }

    @Override
    public String getCode() {
        return product.getCode();
    }

    @Override
    public String getName() {
        return product.getName();
    }

    @Override
    public double getPrice() {
        return product.getPrice();
    }

    public Product getProduct() {
        return product;
    }

    public double getDiscountPrice() {
        return discountPrice;
    }

    public void setDiscountPrice(double discountPrice) {
        if (discountPrice < 0) {
            throw new IllegalArgumentException("Discount price cannot be negative");
        }

        this.discountPrice = discountPrice;
    }
}
