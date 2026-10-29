package pl.sborodziuk.datastructures.traverse;

import pl.sborodziuk.datastructures.core.MyStack;
import pl.sborodziuk.datastructures.tree.TreeNode;

public interface TraverseStrategy<T extends Comparable<T>> {
    MyStack<TreeNode<T>> traverse(TreeNode<T> root, T stopValue);

    default MyStack<TreeNode<T>> traverse(TreeNode<T> root) {
        return traverse(root, null); // null = full traversal
    }

    default TreeNode<T> search(TreeNode<T> root, T value) {
        MyStack<TreeNode<T>> history = traverse(root, value);
        if (history.isEmpty()) {
            return null;
        }
        TreeNode<T> node = history.remove();
        return node.value.compareTo(value) == 0 ? node : null;
    }
}