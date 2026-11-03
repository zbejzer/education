package pl.sborodziuk.javamarkt.ui.tui;

import pl.sborodziuk.javamarkt.command.Command;

public class Parser {
    public GenericCommand parse(String rawInput) {
        if (rawInput == null || rawInput.trim().isEmpty()) {
            throw new IllegalArgumentException("Input cannot be empty.");
        }

        String[] parts = rawInput.trim().split("\\s+", 2);

        String normalizedKeyword = parts[0].toLowerCase().replace(' ', '_');
        String args = parts.length > 1 ? parts[1] : "";

        CommandType commandType = CommandType.fromKeyword(normalizedKeyword);
        return new GenericCommand(commandType, args);
    }

    public Command parseCoreCommand(GenericCommand command) {
        switch (command.getCommandType()) {
            default:
                throw new IllegalArgumentException("Unknown command: " + command.getCommandType().getKeyword());
        }
    }
}
