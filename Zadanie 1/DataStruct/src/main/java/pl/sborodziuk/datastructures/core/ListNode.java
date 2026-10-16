package pl.sborodziuk.datastructures.core;

class ListNode<T> {
    final T value;
    ListNode<T> next;

    ListNode(T value) {
        this.value = value;
        this.next = null;
    }

    ListNode(T value, ListNode<T> next) {
        this.value = value;
        this.next = next;
    }
}
