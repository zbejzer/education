package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

public class RemoveProductCommand implements Command {
    private final String code;
    private Product removed;

    public RemoveProductCommand(String code) {
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
        return visitor.visitRemoveProduct(this);
    }

    @Override
    public void execute(UserSession session) {
        Product removed = session.getCart().removeProduct(code);
        if (removed == null) {
            throw new IllegalArgumentException("Product with code " + code + " is not in the cart.");
        }
        this.removed = removed;
    }

    @Override
    public void undo(UserSession session) {
        session.getCart().addProduct(removed);
    }
}
