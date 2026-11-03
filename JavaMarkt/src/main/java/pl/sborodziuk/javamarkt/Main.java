package pl.sborodziuk.javamarkt;

import pl.sborodziuk.javamarkt.session.SessionManager;
import pl.sborodziuk.javamarkt.ui.tui.TextUserInterface;

public class Main {
    public static void main(String[] args) {
        SessionManager sessionManager = new SessionManager();

        TextUserInterface tui = new TextUserInterface(sessionManager);
        tui.start();
    }
}