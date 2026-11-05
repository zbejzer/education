package pl.sborodziuk.javamarkt.session;

import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.model.Cart;
import pl.sborodziuk.javamarkt.model.ProductCatalog;

public class UserSession {
    private final Cart cart = new Cart();
    private final ProductCatalog productCatalog;

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
    }
}
