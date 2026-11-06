package pl.sborodziuk.javamarkt.session;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.List;

import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.model.Cart;
import pl.sborodziuk.javamarkt.model.ProductCatalog;

public class UserSession {
    private final Cart cart = new Cart();
    private final ProductCatalog productCatalog;
    private final Deque<Command> history = new ArrayDeque<>();

    public UserSession(ProductCatalog productCatalog) {
        if (productCatalog == null) {
            throw new IllegalArgumentException("Product catalog cannot be null.");
        }
        this.productCatalog = productCatalog;
    }

    public Cart getCart() {
        return cart;
    }

    public ProductCatalog getProductCatalog() {
        return productCatalog;
    }

    public void executeCommand(Command command) {
        command.execute(this);
        history.addLast(command);
    }

    public Command undoLastCommand() {
        Command command = history.peekLast();
        if (command == null) {
            return null;
        }

        command.undo(this);
        history.removeLast();
        return command;
    }

    public List<Command> getHistory() {
        return List.copyOf(history);
    }
}
