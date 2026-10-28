package pl.sborodziuk.datastructures.tree;

public class TreeNode<T> {
    public TreeNode<T> left, right;
    public T value;

    public TreeNode(T value) {
        this.value = value;
    }
}
