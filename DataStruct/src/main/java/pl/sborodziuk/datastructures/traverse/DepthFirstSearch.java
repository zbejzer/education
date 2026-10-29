package pl.sborodziuk.datastructures.traverse;

import pl.sborodziuk.datastructures.core.MyStack;
import pl.sborodziuk.datastructures.tree.TreeNode;

public class DepthFirstSearch<T extends Comparable<T>> implements TraverseStrategy<T> {

    @Override
    public MyStack<TreeNode<T>> traverse(TreeNode<T> root, T stopValue) {
        MyStack<TreeNode<T>> toTraverse = new MyStack<>();
        MyStack<TreeNode<T>> history = new MyStack<>();
        TreeNode<T> current;

        if (root != null) {
            toTraverse.add(root);
        }

        while (!toTraverse.isEmpty()) {
            current = toTraverse.remove();

            history.add(current);

            if (stopValue != null && current.value.compareTo(stopValue) == 0) {
                break;
            }

            if (current.right != null) {
                toTraverse.add(current.right);
            }

            if (current.left != null) {
                toTraverse.add(current.left);
            }
        }

        return history;
    }
}
