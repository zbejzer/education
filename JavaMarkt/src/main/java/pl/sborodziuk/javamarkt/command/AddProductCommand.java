package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

public class AddProductCommand implements Command {
    private final String code;

    public AddProductCommand(String code) {
        if (code == null || code.isBlank()) {
            throw new IllegalArgumentException("Product code cannot be blank.");
        }
        this.code = code;
    }

    public String getCode() {
        return code;
    }

    @Override
    public <T> T accept(CommandVisitor<T> visitor) {
        return visitor.visitAddProduct(this);
    }

    @Override
    public void execute(UserSession session) {
        Product listed = session.getProductCatalog().findByCode(code);
        if (listed == null) {
            throw new IllegalArgumentException(
                    "Product with code " + code + " does not exist.");
        }
        session.getCart().addProduct(listed);
    }

    @Override
    public void undo(UserSession session) {
        if (session.getCart().removeProduct(code) == null) {
            throw new IllegalStateException(
                    "Product with code " + code + " is not in the cart.");
        }
    }

}
