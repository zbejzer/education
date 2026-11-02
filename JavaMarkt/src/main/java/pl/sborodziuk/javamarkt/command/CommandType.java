package pl.sborodziuk.javamarkt.command;

public enum CommandType {
    EXIT {
        @Override
        public Command parse(String[] tokens) {
            return new ExitCommand();
        }
    };

    public abstract Command parse(String[] tokens);

    public static CommandType fromKeyword(String keyword) {
        String normalizedKeyword = keyword.toUpperCase().replace(' ', '_');

        for (CommandType cmd : values()) {
            if (cmd.toString() == normalizedKeyword) {
                return cmd;
            }
        }
        throw new IllegalArgumentException("Unknown command: " + keyword);
    }
}
