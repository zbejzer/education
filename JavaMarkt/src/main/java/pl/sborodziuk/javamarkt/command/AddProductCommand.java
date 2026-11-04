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

    @Override
    public void undo(UserSession session) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'undo'");
    }

}
