package pl.sborodziuk.javamarkt.ui.tui;

import java.util.Scanner;

import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.session.SessionManager;

public class TextUserInterface {
    private final Parser parser;
    private final SessionManager sessionManager;
    private final Scanner scanner;
    private boolean running;

    public TextUserInterface(SessionManager sessionManager) {
        this.parser = new Parser();
        this.sessionManager = sessionManager;
        this.scanner = new Scanner(System.in);
        this.running = false;
    }

    public void start() {
        this.running = true;

        printWelcome();

        while (isRunning()) {
            if (!scanner.hasNextLine()) {
                terminate();
                break;
            }

            System.out.print("\n> ");
            String input = scanner.nextLine().trim();

            processInput(input);
        }
    }

    private void processInput(String input) {
        if (input.isEmpty()) {
            return;
        }

        GenericCommand structuredCommand = parser.parse(input);
        if (structuredCommand.getCommandType().getTarget().equals(CommandTarget.TUI)) {
            handleCommand(structuredCommand);
            return;
        }

        Command command = parser.parseCoreCommand(structuredCommand);
        sessionManager.executeCommand(command);
    }

    public void handleCommand(GenericCommand command) {
        switch (command.getCommandType()) {
            case HELP:
                printHelp();
                return;

            case EXIT:
                printExit();
                terminate();
                return;

            default:
                throw new IllegalStateException("Unhandled command type: " + command.getCommandType().getKeyword());
        }
    }

    private void printWelcome() {
        System.out.println(
                "Enter a command, or type '" + CommandType.HELP.getKeyword() + "' to list all available commands.");
    }

    private void printExit() {
        System.out.println(
                "App terminated successfully.");
    }

    private void printHelp() {
        for (CommandType entry : CommandType.values()) {
            System.out.printf("  %-8s : %s (Syntax: %s)%n",
                    entry.getKeyword(),
                    entry.getDescription(),
                    entry.getSyntax());
        }
        System.out.println();
    }

    public void terminate() {
        this.running = false;
    }

    public boolean isRunning() {
        return running;
    }
}
