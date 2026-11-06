package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

public class RegisterProductCommand implements Command {
    private final Product product;

    public RegisterProductCommand(String code, String name, Double price) {
        this.product = new Product(code, name, price);
    }

    @Override
    public void execute(UserSession session) {
        session.getProductCatalog().addProduct(product);
    }

    public Product getProduct() {
        return product;
    }

    @Override
    public <T> T accept(CommandVisitor<T> visitor) {
        return visitor.visitRegisterProduct(this);
    }

    @Override
    public void undo(UserSession session) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'undo'");
    }

}
