package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

public class AddProductCommand implements Command {
    private final String code;
    private final String name;
    private final Double price;

    public AddProductCommand(String code, String name, Double price) {
        this.code = code;
        this.name = name;
        this.price = price;
    }

    @Override
    public void execute(UserSession session) {
        Product product = new Product(code, name, price);
        session.getCart().addProduct(product);
    }

    @Override
    public void undo(UserSession session) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'undo'");
    }

}
