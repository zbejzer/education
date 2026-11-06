package pl.sborodziuk.javamarkt.ui.tui;

import java.util.List;

record ParsedCommand(CommandType commandType, List<String> arguments) {
    ParsedCommand {
        arguments = List.copyOf(arguments);
    }
}
