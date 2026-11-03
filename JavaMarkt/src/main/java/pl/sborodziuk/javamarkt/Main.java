package pl.sborodziuk.javamarkt;

import pl.sborodziuk.javamarkt.session.UserSession;
import pl.sborodziuk.javamarkt.ui.tui.TextUserInterface;

public class Main {
    public static void main(String[] args) {
        UserSession session = new UserSession();

        TextUserInterface tui = new TextUserInterface(session);
        tui.start();
    }
}