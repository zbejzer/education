package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.model.Product;
import pl.sborodziuk.javamarkt.session.UserSession;

public class UnregisterProductCommand implements Command {
    private final String code;
    private Product removed;

    public UnregisterProductCommand(String code) {
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
        return visitor.visitUnregisterProduct(this);
    }

    @Override
    public void execute(UserSession session) {
        Product removed = session.getProductCatalog().findByCode(code);
        if (removed == null) {
            throw new IllegalArgumentException("Product with code " + code + " does not exist.");
        }
        session.getProductCatalog().removeProduct(code);
        this.removed = removed;
    }

    @Override
    public void undo(UserSession session) {
        session.getProductCatalog().addProduct(removed);
    }

}
