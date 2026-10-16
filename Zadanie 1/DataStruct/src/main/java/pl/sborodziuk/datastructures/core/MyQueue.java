package pl.sborodziuk.datastructures.core;

public class MyQueue<T> extends AbstractDataStruct<T, MyQueue<T>> {
    ListNode<T> head;
    ListNode<T> tail;

    @Override
    protected void doAdd(T item) {
        ListNode<T> node = new ListNode<>(item);
        if (tail == null) {
            head = node;
        } else {
            tail.next = node;
        }
        tail = node;
    }

    @Override
    protected void doAdd(MyQueue<T> other) {
        ListNode<T> stop = other.tail;
        for (ListNode<T> n = other.head; n != null; n = n.next) {
            doAdd(n.value);
            if (n == stop) {
                break;
            }
        }
    }

    @Override
    protected final T doRemove() {
        ListNode<T> node = head;
        head = node.next;
        if (head == null) {
            tail = null;
        }
        node.next = null;
        return node.value;
    }
}
