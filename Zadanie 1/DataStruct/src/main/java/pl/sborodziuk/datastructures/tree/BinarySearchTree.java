package pl.sborodziuk.datastructures.tree;

import pl.sborodziuk.datastructures.core.MyStack;
import pl.sborodziuk.datastructures.traverse.DepthFirstSearch;
import pl.sborodziuk.datastructures.traverse.TraverseStrategy;

import java.util.NoSuchElementException;

public class BinarySearchTree<T extends Comparable<T>> {
    TreeNode<T> root = null;
    int size = 0;

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public MyStack<TreeNode<T>> traverse(TraverseStrategy<T> strategy) {
        return strategy.traverse(root);
    }

    public TreeNode<T> search(T value, TraverseStrategy<T> strategy) {
        return strategy.search(root, value);
    }

    public void insert(T value) {
        TreeNode<T> current = null;
        TreeNode<T> next = root;

        if (root == null) {
            root = new TreeNode<>(value);
            size++;
            return;
        }

        while (next != null) {
            current = next;
            if (value.compareTo(next.value) < 0) {
                next = next.left;
            } else {
                next = next.right;
            }
        }

        if (value.compareTo(current.value) < 0) {
            current.left = new TreeNode<>(value);
        } else {
            current.right = new TreeNode<>(value);
        }
        size++;
    }

    public void delete(T value) {
        TreeNode<T> next = root;
        TreeNode<T> current = null;

        while (next != null && next.value.compareTo(value) != 0) {
            current = next;
            if (value.compareTo(next.value) < 0) {
                next = next.left;
            } else {
                next = next.right;
            }
        }

        if (next == null) {
            throw new NoSuchElementException(getClass().getSimpleName() + " has no element with value " + value);
        }

        DepthFirstSearch<T> traverseStrategy = new DepthFirstSearch<>();
        MyStack<TreeNode<T>> toInsert = traverseStrategy.traverse(next);

        if (next == root) {
            root = null;
        } else if (current.left == next) {
            current.left = null;
        } else {
            current.right = null;

        }

        next.left = null;
        next.right = null;

        size--;

        while (toInsert.size() > 1) {
            TreeNode<T> element = toInsert.remove();
            element.left = null;
            element.right = null;
            size--;

            this.insert(element.value);
        }
    }

}
