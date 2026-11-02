package pl.sborodziuk.javamarkt.command;

import pl.sborodziuk.javamarkt.session.UserSession;

public interface Command {
    public void execute(UserSession session);

    public void undo(UserSession session);
}