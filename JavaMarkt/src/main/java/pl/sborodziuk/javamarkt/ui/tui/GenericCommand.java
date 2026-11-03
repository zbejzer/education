package pl.sborodziuk.javamarkt.ui.tui;

public class GenericCommand {
    private final CommandType cmd;
    private final String args;

    public GenericCommand(CommandType cmd, String args) {
        this.cmd = cmd;
        this.args = args;
    }

    public CommandType getCommandType() {
        return cmd;
    }

    public String getRawArguments() {
        return args;
    }
}
