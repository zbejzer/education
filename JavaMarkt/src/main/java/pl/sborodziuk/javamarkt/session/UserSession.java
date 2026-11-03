package pl.sborodziuk.javamarkt.session;

import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.model.Cart;

public class UserSession {
    private final Cart cart = new Cart();

    public Cart getCart() {
        return cart;
    }

    public void executeCommand(Command command) {
        command.execute(this);
    }
}
