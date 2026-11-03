package pl.sborodziuk.javamarkt.ui.tui;

public enum CommandType {
    HELP(CommandTarget.TUI, "Show available commands"),
    EXIT(CommandTarget.TUI, "Exit the application"),
    ADD_PRODUCT(CommandTarget.CORE, "add", "Add product to cart", "<code> <name> <price>");

    private final String keyword;
    private final String description;
    private final String syntax;
    private final CommandTarget target;

    CommandType(CommandTarget target, String keyword, String description, String syntax) {
        this.target = target;
        this.keyword = keyword;
        this.description = description;
        this.syntax = syntax;
    }

    CommandType(CommandTarget target, String description, String syntax) {
        this(target, null, description, syntax);
    }

    CommandType(CommandTarget target, String description) {
        this(target, description, null);
    }

    public String getKeyword() {
        return keyword != null ? keyword : name().toLowerCase();
    }

    public String getDescription() {
        return description;
    }

    public String getSyntax() {
        return syntax != null ? getKeyword() + " " + syntax : getKeyword();
    }

    public CommandTarget getTarget() {
        return target;
    }

    public static CommandType fromKeyword(String keyword) {
        String normalizedKeyword = keyword.toLowerCase().replace(' ', '_');

        for (CommandType cmd : values()) {
            if (cmd.getKeyword().equals(normalizedKeyword)) {
                return cmd;
            }
        }

        throw new IllegalArgumentException("Unknown command: " + keyword);
    }
}
