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
        } catch (CommandFormatException e) {
            throw new IllegalArgumentException(e.getMessage() + ". Usage: " + command.commandType().getSyntax(),
                    e.getCause());
        }
    }

    private Command buildAddProduct(ParsedCommand command) {
        requireValidArgumentCount(command.commandType(), command.arguments());
        List<String> arguments = command.arguments();
        return new AddProductCommand(arguments.get(0), arguments.get(1), Double.parseDouble(arguments.get(2)));
    }

    private Command buildRegisterProduct(ParsedCommand command) {
        requireValidArgumentCount(command.commandType(), command.arguments());
        List<String> arguments = command.arguments();
        return new RegisterProductCommand(arguments.get(0), arguments.get(1), Double.parseDouble(arguments.get(2)));
    }

    private Command buildUnregisterProduct(ParsedCommand command) {
        requireValidArgumentCount(command.commandType(), command.arguments());
        return new UnregisterProductCommand(command.arguments().get(0));
    }

    private void requireValidArgumentCount(CommandType type, List<String> arguments) {
        if (arguments.isEmpty()) {
            throw new CommandFormatException("Missing arguments");
        }
        if (arguments.size() != type.getRequiredArgumentCount()) {
            throw new CommandFormatException("Invalid format");
        }
    }
}
