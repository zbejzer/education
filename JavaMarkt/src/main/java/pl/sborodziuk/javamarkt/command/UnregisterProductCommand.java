package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.session.UserSession;

public class UnregisterProductCommand implements Command {
    private final String code;

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
        if (!session.getProductCatalog().removeProduct(code)) {
            throw new IllegalArgumentException("Product with code " + code + " does not exist.");
        }
    }

    @Override
    public void undo(UserSession session) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'undo'");
    }

}
