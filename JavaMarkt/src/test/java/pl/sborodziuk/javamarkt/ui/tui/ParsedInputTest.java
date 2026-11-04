package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ParsedInputTest {

    @Test
    void constructorStoresCommandTypeAndArguments() {
        ParsedInput command = new ParsedInput(CommandType.HELP, "some args");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.commandType()),
                () -> assertEquals("some args", command.arguments()));
    }

    @Test
    void argumentsMayBeEmptyString() {
        ParsedInput command = new ParsedInput(CommandType.EXIT, "");

        assertEquals("", command.arguments());
    }

    @Test
    void argumentsMayBeNull() {
        ParsedInput command = new ParsedInput(CommandType.EXIT, null);

        assertNull(command.arguments());
    }
}
