package pl.sborodziuk.javamarkt.ui.tui;

import java.math.BigDecimal;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;

public class Parser {
    public GenericCommand slice(String rawInput) {
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
            case ADD_PRODUCT:
                return parseAddProduct(command);
            default:
                throw new IllegalArgumentException("Unknown command: " + command.getCommandType().getKeyword());
        }
    }

    private AddProductCommand parseAddProduct(GenericCommand command) {
        if (command.getRawArguments().isBlank()) {
            throw new IllegalArgumentException("Missing arguments. Usage: " + command.getCommandType().getSyntax());
        }

        String[] productParts = command.getRawArguments().split("\\s+", 3);
        if (productParts.length < 3) {
            throw new IllegalArgumentException("Invalid format. Usage: " + command.getCommandType().getSyntax());
        }

        String code = productParts[0];
        String name = productParts[1];
        Double price = Double.parseDouble(productParts[2]);

        return new AddProductCommand(code, name, price);
    }
}
