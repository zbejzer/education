package pl.sborodziuk.javamarkt.ui.tui;

public class UnknownCommandException extends IllegalArgumentException {
    public UnknownCommandException(String keyword) {
        super("Unknown command: " + keyword);
    }
}
