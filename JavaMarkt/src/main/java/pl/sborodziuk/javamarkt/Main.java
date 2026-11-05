package pl.sborodziuk.javamarkt;

import pl.sborodziuk.javamarkt.model.ProductCatalog;
import pl.sborodziuk.javamarkt.session.UserSession;
import pl.sborodziuk.javamarkt.ui.tui.TextUserInterface;

public class Main {
    public static void main(String[] args) {
        ProductCatalog catalog = new ProductCatalog();
        UserSession session = new UserSession(catalog);

        TextUserInterface tui = new TextUserInterface(session);
        tui.start();
    }
}