package pl.sborodziuk.javamarkt.ui.tui;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
import pl.sborodziuk.javamarkt.command.UnregisterProductCommand;

public class Parser {
    public ParsedInput parse(String rawInput) {
        if (rawInput == null || rawInput.trim().isEmpty()) {
            throw new IllegalArgumentException("Input cannot be empty.");
        }

        String[] parts = rawInput.trim().split("\\s+", 2);

        String normalizedKeyword = parts[0].toLowerCase().replace(' ', '_');
        String args = parts.length > 1 ? parts[1] : "";

        CommandType commandType = CommandType.fromKeyword(normalizedKeyword);
        return new ParsedInput(commandType, args);
    }

    public Command toCommand(ParsedInput command) {
        switch (command.commandType()) {
            case ADD_PRODUCT:
                return parseAddProduct(command);
            case REGISTER_PRODUCT:
                return parseRegisterProduct(command);
            case UNREGISTER_PRODUCT:
                return parseUnregisterProduct(command);
            default:
                throw new UnknownCommandException(command.commandType().getKeyword());
        }
    }

    private Command parseAddProduct(ParsedInput command) {
        String[] arguments = parseTokens(command);
        requireExactTokenCount(command, arguments);
        return new AddProductCommand(arguments[0], arguments[1], parsePrice(command, arguments[2]));
    }

    private Command parseRegisterProduct(ParsedInput command) {
        String[] arguments = parseTokens(command);
        requireExactTokenCount(command, arguments);
        return new RegisterProductCommand(arguments[0], arguments[1], parsePrice(command, arguments[2]));
    }

    private Command parseUnregisterProduct(ParsedInput command) {
        String[] arguments = parseTokens(command);
        requireExactTokenCount(command, arguments);
        return new UnregisterProductCommand(arguments[0]);
    }

    private String[] parseTokens(ParsedInput command) {
        requireArguments(command);
        return command.arguments().split("\\s+");
    }

    private void requireArguments(ParsedInput command) {
        if (command.arguments().isBlank()) {
            throw new IllegalArgumentException("Missing arguments. Usage: " + command.commandType().getSyntax());
        }
    }

    private void requireExactTokenCount(ParsedInput command, String[] tokens) {
        int expectedTokenCount = command.commandType().getRequiredArgumentCount();
        if (tokens.length != expectedTokenCount) {
            throw new IllegalArgumentException("Invalid format. Usage: " + command.commandType().getSyntax());
        }
    }

    private double parsePrice(ParsedInput command, String rawPrice) {
        try {
            return Double.parseDouble(rawPrice);
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Invalid price. Usage: " + command.commandType().getSyntax(), e);
        }
    }
}
