package pl.sborodziuk.javamarkt.ui.tui;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;

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
            default:
                throw new IllegalArgumentException("Unknown command: " + command.commandType().getKeyword());
        }
    }

    private AddProductCommand parseAddProduct(ParsedInput command) {
        if (command.arguments().isBlank()) {
            throw new IllegalArgumentException("Missing arguments. Usage: " + command.commandType().getSyntax());
        }

        String[] productParts = command.arguments().split("\\s+", 3);
        if (productParts.length < 3) {
            throw new IllegalArgumentException("Invalid format. Usage: " + command.commandType().getSyntax());
        }

        String code = productParts[0];
        String name = productParts[1];
        Double price = Double.parseDouble(productParts[2]);

        return new AddProductCommand(code, name, price);
    }
}
