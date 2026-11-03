package pl.sborodziuk.javamarkt.session;

import org.junit.jupiter.api.Test;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;

import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.*;

class UserSessionTest {

    @Test
    void getCartReturnsSameInstanceEachCall() {
        UserSession session = new UserSession();

        assertSame(session.getCart(), session.getCart());
    }

    @Test
    void executeCommandRunsCommandAgainstThisSession() {
        UserSession session = new UserSession();
        AtomicReference<UserSession> captured = new AtomicReference<>();

        session.executeCommand(new Command() {
            @Override
            public void execute(UserSession target) {
                captured.set(target);
            }

            @Override
            public void undo(UserSession target) {
            }
        });

        assertSame(session, captured.get());
    }

    @Test
    void executeCommandAppliesCommandEffectToCart() {
        UserSession session = new UserSession();

        session.executeCommand(new AddProductCommand("P001", "Monitor", 799.99));

        assertAll(
                () -> assertEquals(1, session.getCart().getSize()),
                () -> assertEquals("P001", session.getCart().getAllItems()[0].getProduct().getCode()));
    }
}
