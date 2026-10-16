package pl.sborodziuk.datastructures.core;

public class MyStack<T> extends AbstractDataStruct<T, MyStack<T>> {
    ListNode<T> top;


    @Override
    protected void doAdd(T item) {
        top = new ListNode<>(item, top);
    }

    @Override
    protected void doAdd(MyStack<T> other) {
        ListNode<T> src = other.top;
        if (src == null) {
            return;
        }

        ListNode<T> first = new ListNode<>(src.value);
        ListNode<T> last = first;

        for (src = src.next; src != null; src = src.next) {
            last.next = new ListNode<>(src.value);
            last = last.next;
        }

        last.next = top;
        top = first;
    }

    @Override
    protected final T doRemove() {
        ListNode<T> node = top;
        top = node.next;
        node.next = null;
        return node.value;
    }
}
