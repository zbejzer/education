package pl.sborodziuk.javamarkt.ui.tui;

import java.util.List;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
import pl.sborodziuk.javamarkt.command.UnregisterProductCommand;

public class Parser {
    public ParsedCommand parse(String rawInput) {
        if (rawInput == null || rawInput.trim().isEmpty()) {
            throw new IllegalArgumentException("Input cannot be empty.");
        }

        String[] parts = rawInput.trim().split("\\s+", 2);

        String normalizedKeyword = parts[0].toLowerCase().replace(' ', '_');
        String rest = parts.length > 1 ? parts[1] : "";
        List<String> arguments = rest.isBlank() ? List.of() : List.of(rest.trim().split("\\s+"));

        CommandType commandType = CommandType.fromKeyword(normalizedKeyword);
        return new ParsedCommand(commandType, arguments);
    }

    public Command toCommand(ParsedCommand command) {
        try {
            requireValidArgumentCount(command.commandType(), command.arguments());
            switch (command.commandType()) {
                case ADD_PRODUCT:
                    return buildAddProduct(command);
                case REGISTER_PRODUCT:
                    return buildRegisterProduct(command);
                case UNREGISTER_PRODUCT:
                    return buildUnregisterProduct(command);
                default:
                    throw new UnknownCommandException(command.commandType().getKeyword());
            }
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Invalid price. Usage: " + command.commandType().getSyntax(), e);
        }
    }

    private Command buildAddProduct(ParsedCommand command) {
        List<String> arguments = command.arguments();
        return new AddProductCommand(arguments.get(0), arguments.get(1), Double.parseDouble(arguments.get(2)));
    }

    private Command buildRegisterProduct(ParsedCommand command) {
        List<String> arguments = command.arguments();
        return new RegisterProductCommand(arguments.get(0), arguments.get(1), Double.parseDouble(arguments.get(2)));
    }

    private Command buildUnregisterProduct(ParsedCommand command) {
        return new UnregisterProductCommand(command.arguments().get(0));
    }

    void requireValidArgumentCount(CommandType type, List<String> arguments) {
        int expected = type.getRequiredArgumentCount();
        if (arguments.size() != expected) {
            String problem = arguments.size() < expected ? "Missing arguments" : "Too many arguments";
            throw new CommandFormatException(problem + ". Usage: " + type.getSyntax());
        }
    }
}
