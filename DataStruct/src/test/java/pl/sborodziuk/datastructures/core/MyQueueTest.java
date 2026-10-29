package pl.sborodziuk.datastructures.core;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

@DisplayName("MyQueue")
class MyQueueTest {

    private static <T> List<T> drain(MyQueue<T> queue) {
        List<T> out = new ArrayList<>();
        while (!queue.isEmpty()) {
            out.add(queue.remove());
        }
        return out;
    }

    @Test
    @DisplayName("new queue is empty with size 0")
    void newQueueIsEmpty() {
        MyQueue<Integer> queue = new MyQueue<>();

        assertEquals(0, queue.size());
        assertTrue(queue.isEmpty());
    }

    @Test
    @DisplayName("FIFO order: 1,2,3 drains as 1,2,3")
    void fifoOrder() {
        MyQueue<Integer> queue = new MyQueue<>();
        queue.add(1);
        queue.add(2);
        queue.add(3);

        assertEquals(3, queue.size());
        assertEquals(List.of(1, 2, 3), drain(queue));
    }

    @Test
    @DisplayName("remove on empty queue throws NoSuchElementException")
    void removeOnEmptyThrows() {
        MyQueue<Integer> queue = new MyQueue<>();

        assertThrows(NoSuchElementException.class, queue::remove);
    }

    @Test
    @DisplayName("bulk add appends other queue after own elements, other unchanged")
    void bulkAddOtherQueue() {
        MyQueue<Integer> own = new MyQueue<>();
        own.add(1);
        own.add(2);
        MyQueue<Integer> other = new MyQueue<>();
        other.add(3);
        other.add(4);

        own.add(other);

        assertEquals(List.of(1, 2, 3, 4), drain(own));
        assertEquals(List.of(3, 4), drain(other));
    }

    @Test
    @DisplayName("self bulk add doubles contents in order")
    void bulkAddSelfDoubles() {
        MyQueue<Integer> queue = new MyQueue<>();
        queue.add(1);
        queue.add(2);

        queue.add(queue);

        assertEquals(4, queue.size());
        assertEquals(List.of(1, 2, 1, 2), drain(queue));
    }
}
