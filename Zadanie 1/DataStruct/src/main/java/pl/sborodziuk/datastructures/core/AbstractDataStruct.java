package pl.sborodziuk.datastructures.core;

import java.util.NoSuchElementException;

public abstract class AbstractDataStruct<T, S extends AbstractDataStruct<T, S>> {
    protected int size;

    protected abstract void doAdd(T item);

    protected abstract void doAdd(S other);

    protected abstract T doRemove();

    public final void add(T item) {
        doAdd(item);
        size++;

    }

    public final void add(S other) {
        doAdd(other);
        size += other.size();
    }

    public final T remove() {
        if (isEmpty()) {
            throw new NoSuchElementException(getClass().getSimpleName() + " is empty");
        }

        T item = doRemove();
        size--;
        return item;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }
}
