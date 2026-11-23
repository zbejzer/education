package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

public class AddProductCommand implements Command {
    private final Product product;

    public AddProductCommand(String code, String name, Double price) {
        this.product = new Product(code, name, price);
    }

    @Override
    public void execute(UserSession session) {
        session.getCart().addProduct(product);
    }

    public Product getProduct() {
        return product;
    }

    @Override
    public <T> T accept(CommandVisitor<T> visitor) {
        return visitor.visitAddProduct(this);
    }

    @Override
    public void undo(UserSession session) {
        if (session.getCart().removeProduct(product.getCode()) == null) {
            throw new IllegalStateException(
                    "Product with code " + product.getCode() + " is not in the cart.");
        }
    }

}
