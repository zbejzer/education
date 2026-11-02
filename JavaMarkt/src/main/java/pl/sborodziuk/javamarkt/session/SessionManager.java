package pl.sborodziuk.javamarkt.session;

import pl.sborodziuk.javamarkt.command.Command;

public class SessionManager {
    private final UserSession session = new UserSession();

    public UserSession getSession() {
        return session;
    }

    public void executeCommand(Command command) {

    }
}
