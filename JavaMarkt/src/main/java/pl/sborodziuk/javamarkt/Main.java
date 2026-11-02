package pl.sborodziuk.javamarkt;

import pl.sborodziuk.javamarkt.session.SessionManager;
import pl.sborodziuk.javamarkt.ui.CommandParser;
import pl.sborodziuk.javamarkt.ui.TextUserInterface;

public class Main {
    public static void main(String[] args) {
        SessionManager sessionManager = new SessionManager();
        CommandParser parser = new CommandParser();

        TextUserInterface tui = new TextUserInterface(parser, sessionManager);
        tui.start();
    }
}