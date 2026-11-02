package pl.sborodziuk.javamarkt.ui;

import java.util.Scanner;

import pl.sborodziuk.javamarkt.command.Command;
import pl.sborodziuk.javamarkt.command.CommandType;
import pl.sborodziuk.javamarkt.session.SessionManager;

public class TextUserInterface {
    private final CommandParser parser;
    private final SessionManager sessionManager;
    private final Scanner scanner;

    public TextUserInterface(CommandParser parser, SessionManager sessionManager) {
        this.parser = parser;
        this.sessionManager = sessionManager;
        this.scanner = new Scanner(System.in);
    }

    public void start() {

        printWelcome();

        while (sessionManager.getSession().isRunning()) {
            System.out.print("\n> ");

            if (!scanner.hasNextLine()) {
                break;
            }

            String input = readInput();

            processInput(input);
        }
    }

    private String readInput() {
        return scanner.nextLine().trim();
    }

    private void printMessage(String message) {
        System.out.println(message);
    }

    private void processInput(String input) {
        if (input.isEmpty()) {
            return;
        }

        try {
            Command command = parser.parse(input);
            sessionManager.executeCommand(command);
        } catch (IllegalArgumentException e) {
            System.err.println("[Syntax Error] " + e.getMessage());
        } catch (IllegalStateException e) {
            System.err.println("[Action Failed] " + e.getMessage());
        } catch (Exception e) {
            System.err.println("[System Error] An unexpected error occurred: " + e.getMessage());
        }

        printMessage("Unknown command: " + input);
    }

    private void printWelcome() {
        System.out.println("Enter a command, or type '" + CommandType.EXIT.name().toLowerCase() + "' to quit.");
    }
}
