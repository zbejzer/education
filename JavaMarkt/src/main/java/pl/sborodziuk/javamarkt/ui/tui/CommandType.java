package pl.sborodziuk.javamarkt.ui.tui;

public enum CommandType {
    HELP(CommandTarget.TUI, "Show available commands"),
    EXIT(CommandTarget.TUI, "Exit the application");

    private final String description;
    private final String syntax;
    private final CommandTarget target;

    CommandType(CommandTarget target, String description, String syntax) {
        this.description = description;
        this.syntax = syntax;
        this.target = target;
    }

    CommandType(CommandTarget target, String description) {
        this(target, description, null);
    }

    public String getKeyword() {
        return name().toLowerCase();
    }

    public String getDescription() {
        return description;
    }

    public String getSyntax() {
        return syntax != null ? syntax : getKeyword();
    }

    public CommandTarget getTarget() {
        return target;
    }

    public static CommandType fromKeyword(String keyword) {
        String normalizedKeyword = keyword.toUpperCase().replace(' ', '_');

        for (CommandType cmd : values()) {
            if (cmd.toString().equals(normalizedKeyword)) {
                return cmd;
            }
        }
        throw new IllegalArgumentException("Unknown command: " + keyword);
    }
}
