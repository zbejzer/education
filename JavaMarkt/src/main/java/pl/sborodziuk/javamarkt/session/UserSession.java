package pl.sborodziuk.javamarkt.session;

import pl.sborodziuk.javamarkt.model.Cart;

public class UserSession {
    private boolean running = true;
    private final Cart cart = new Cart();

    public Cart getCart() {
        return cart;
    }

    public void terminate() {
        this.running = false;
    }

    public boolean isRunning() {
        return running;
    }

}
