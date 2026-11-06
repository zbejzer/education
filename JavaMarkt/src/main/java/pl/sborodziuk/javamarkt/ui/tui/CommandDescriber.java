package pl.sborodziuk.javamarkt.ui.tui;

import java.util.List;

import pl.sborodziuk.javamarkt.command.AddProductCommand;
import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.CommandVisitor;
import pl.sborodziuk.javamarkt.command.RegisterProductCommand;
import pl.sborodziuk.javamarkt.command.UnregisterProductCommand;

public class CommandDescriber implements CommandVisitor<ParsedCommand> {
    public ParsedCommand parse(Command command) {
        return command.accept(this);
    }

    @Override
    public ParsedCommand visitAddProduct(AddProductCommand command) {
        return new ParsedCommand(CommandType.ADD_PRODUCT,
                List.of(command.getProduct().getCode(),
                        command.getProduct().getName(),
                        String.valueOf(command.getProduct().getPrice())));
    }

    @Override
    public ParsedCommand visitRegisterProduct(RegisterProductCommand command) {
        return new ParsedCommand(CommandType.REGISTER_PRODUCT,
                List.of(command.getProduct().getCode(),
                        command.getProduct().getName(),
                        String.valueOf(command.getProduct().getPrice())));
    }

    @Override
    public ParsedCommand visitUnregisterProduct(UnregisterProductCommand command) {
        return new ParsedCommand(CommandType.UNREGISTER_PRODUCT,
                List.of(command.getCode()));
    }

    public String describeEntry(ParsedCommand parsedCommand) {
        return parsedCommand.commandType().getKeyword() + " " + String.join(" ", parsedCommand.arguments());
    }
}
