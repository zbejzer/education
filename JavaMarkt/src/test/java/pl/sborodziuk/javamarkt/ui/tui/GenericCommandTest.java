package pl.sborodziuk.javamarkt.ui.tui;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GenericCommandTest {

    @Test
    void constructorStoresCommandTypeAndArguments() {
        GenericCommand command = new GenericCommand(CommandType.HELP, "some args");

        assertAll(
                () -> assertEquals(CommandType.HELP, command.getCommandType()),
                () -> assertEquals("some args", command.getRawArguments()));
    }

    @Test
    void argumentsMayBeEmptyString() {
        GenericCommand command = new GenericCommand(CommandType.EXIT, "");

        assertEquals("", command.getRawArguments());
    }

    @Test
    void argumentsMayBeNull() {
        GenericCommand command = new GenericCommand(CommandType.EXIT, null);

        assertNull(command.getRawArguments());
    }
}
