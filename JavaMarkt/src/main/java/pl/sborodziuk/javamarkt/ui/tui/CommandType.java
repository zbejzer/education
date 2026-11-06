package pl.sborodziuk.javamarkt.ui.tui;

public enum CommandType {
    HELP(Target.TUI, "Show available commands"),
    EXIT(Target.TUI, "Exit the application"),
    HISTORY(Target.TUI, "Show submitted operations history"),
    UNDO(Target.TUI, "Attempt to reverse the last operation"),
    ADD_PRODUCT(Target.CORE, "add", "Add product to cart", "<code> <name> <price>"),
    REGISTER_PRODUCT(Target.CORE, "register", "Register product in catalog", "<code> <name> <price>"),
    UNREGISTER_PRODUCT(Target.CORE, "unregister", "Remove product from catalog", "<code>");

    public enum Target {
        TUI,
        CORE
    }

    private final String keyword;
    private final String description;
    private final String syntax;
    private final Target target;

    CommandType(Target target, String keyword, String description, String syntax) {
        this.target = target;
        this.keyword = keyword;
        this.description = description;
        this.syntax = syntax;
    }

    CommandType(Target target, String description, String syntax) {
        this(target, null, description, syntax);
    }

    CommandType(Target target, String description) {
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

    public int getRequiredArgumentCount() {
        if (syntax == null) {
            return 0;
        }

        int count = 0;
        int index = syntax.indexOf('<');
        while (index != -1) {
            count++;
            index = syntax.indexOf('<', index + 1);
        }
        return count;
    }

    public Target getTarget() {
        return target;
    }

    public static CommandType fromKeyword(String keyword) {
        String normalizedKeyword = keyword.toLowerCase().replace(' ', '_');

        for (CommandType cmd : values()) {
            if (cmd.getKeyword().equals(normalizedKeyword)) {
                return cmd;
            }
        }

        throw new UnknownCommandException(keyword);
    }
}
