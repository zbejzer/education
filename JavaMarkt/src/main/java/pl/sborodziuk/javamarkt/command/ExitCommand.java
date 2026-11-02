package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.session.UserSession;

public class ExitCommand implements Command {
    @Override
    public void execute(UserSession session) {
        session.terminate();
    }

    @Override
    public void undo(UserSession session) {
        throw new UnsupportedOperationException("Cannot undo exit command.");
    }
}
