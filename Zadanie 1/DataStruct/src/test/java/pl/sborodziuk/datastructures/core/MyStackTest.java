package pl.sborodziuk.datastructures.core;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

@DisplayName("MyStack")
class MyStackTest {

    private static <T> List<T> drain(MyStack<T> stack) {
        List<T> out = new ArrayList<>();
        while (!stack.isEmpty()) {
            out.add(stack.remove());
        }
        return out;
    }

    @Test
    @DisplayName("new stack is empty with size 0")
    void newStackIsEmpty() {
        MyStack<Integer> stack = new MyStack<>();

        assertEquals(0, stack.size());
        assertTrue(stack.isEmpty());
    }

    @Test
    @DisplayName("LIFO order: 1,2,3 drains as 3,2,1")
    void lifoOrder() {
        MyStack<Integer> stack = new MyStack<>();
        stack.add(1);
        stack.add(2);
        stack.add(3);

        assertEquals(3, stack.size());
        assertEquals(List.of(3, 2, 1), drain(stack));
    }

    @Test
    @DisplayName("remove on empty stack throws NoSuchElementException")
    void removeOnEmptyThrows() {
        MyStack<Integer> stack = new MyStack<>();

        assertThrows(NoSuchElementException.class, stack::remove);
    }

    @Test
    @DisplayName("bulk add puts other's chain on top; other unchanged")
    void bulkAddOtherStack() {
        MyStack<Integer> own = new MyStack<>();
        own.add(10);
        MyStack<Integer> other = new MyStack<>();
        other.add(1);
        other.add(2);

        own.add(other);

        assertEquals(List.of(2, 1, 10), drain(own));
        assertEquals(List.of(2, 1), drain(other));
    }

    @Test
    @DisplayName("self bulk add doubles contents")
    void bulkAddSelfDoubles() {
        MyStack<Integer> stack = new MyStack<>();
        stack.add(1);
        stack.add(2);

        stack.add(stack);

        assertEquals(4, stack.size());
        assertEquals(List.of(2, 1, 2, 1), drain(stack));
    }
}
