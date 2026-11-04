package pl.sborodziuk.javamarkt.ui.tui;

import java.util.Scanner;

import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.session.UserSession;

public class TextUserInterface {
    private final Parser parser;
    private final UserSession session;
    private final Scanner scanner;
    private boolean running;

    public TextUserInterface(UserSession session) {
        this.parser = new Parser();
        this.session = session;
        this.scanner = new Scanner(System.in);
        this.running = false;
    }

    public void start() {
        this.running = true;

        printWelcome();

        while (isRunning()) {
            System.out.print("\n> ");

            if (!scanner.hasNextLine()) {
                terminate();
                break;
            }

            String input = scanner.nextLine().trim();

            try {
                processInput(input);
            } catch (UnknownCommandException e) {
                System.out.println(e.getMessage() + " — type '"
                        + CommandType.HELP.getKeyword() + "' to list available commands.");
            } catch (IllegalArgumentException e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private void processInput(String input) {
        if (input.isEmpty()) {
            return;
        }

        ParsedInput structuredCommand = parser.parse(input);
        if (structuredCommand.commandType().getTarget() == CommandType.Target.TUI) {
            handleCommand(structuredCommand);
        } else {
            Command command = parser.toCommand(structuredCommand);
            session.executeCommand(command);
        }
    }

    public void handleCommand(ParsedInput command) {
        switch (command.commandType()) {
            case HELP:
                printHelp();
                return;

            case EXIT:
                printExit();
                terminate();
                return;

            default:
                throw new IllegalStateException("Unhandled command type: " + command.commandType().getKeyword());
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
        System.out.println();
        for (CommandType entry : CommandType.values()) {
            System.out.printf("  %-8s : %s (Syntax: %s)%n",
                    entry.getKeyword(),
                    entry.getDescription(),
                    entry.getSyntax());
        }
    }

    public void terminate() {
        this.running = false;
    }

    public boolean isRunning() {
        return running;
    }
}
