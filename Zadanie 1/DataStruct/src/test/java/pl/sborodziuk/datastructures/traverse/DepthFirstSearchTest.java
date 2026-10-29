package pl.sborodziuk.datastructures.traverse;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import pl.sborodziuk.datastructures.core.MyStack;
import pl.sborodziuk.datastructures.tree.TreeNode;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

@DisplayName("DepthFirstSearch")
class DepthFirstSearchTest {

    private static final DepthFirstSearch<Integer> DFS = new DepthFirstSearch<>();

    private static List<Integer> values(MyStack<TreeNode<Integer>> history) {
        List<Integer> out = new ArrayList<>();
        while (!history.isEmpty()) {
            out.add(history.remove().value);
        }
        return out;
    }

    private static TreeNode<Integer> canonicalTree() {
        TreeNode<Integer> root = new TreeNode<>(8);
        TreeNode<Integer> three = new TreeNode<>(3);
        TreeNode<Integer> ten = new TreeNode<>(10);
        TreeNode<Integer> one = new TreeNode<>(1);
        TreeNode<Integer> six = new TreeNode<>(6);
        TreeNode<Integer> fourteen = new TreeNode<>(14);

        root.left = three;
        root.right = ten;
        three.left = one;
        three.right = six;
        ten.right = fourteen;
        return root;
    }

    @Test
    @DisplayName("null root yields empty history")
    void nullRootYieldsEmptyHistory() {
        MyStack<TreeNode<Integer>> history = DFS.traverse(null);

        assertNotNull(history);
        assertTrue(history.isEmpty());
        assertEquals(0, history.size());
    }

    @Test
    @DisplayName("full traversal drains in reversed preorder: 14,10,6,1,3,8")
    void fullTraversalPopOrder() {
        TreeNode<Integer> root = canonicalTree();

        assertEquals(List.of(14, 10, 6, 1, 3, 8), values(DFS.traverse(root)));
    }

    @Test
    @DisplayName("stop at 6: history size 4, match on top, rest drains as 1,3,8")
    void stopAtMatch() {
        TreeNode<Integer> root = canonicalTree();
        TreeNode<Integer> six = root.left.right;

        MyStack<TreeNode<Integer>> history = DFS.traverse(root, 6);

        assertEquals(4, history.size());
        TreeNode<Integer> top = history.remove();
        assertSame(six, top);
        assertEquals(6, top.value);
        assertEquals(List.of(1, 3, 8), values(history));
    }

    @Test
    @DisplayName("default search finds the matching node")
    void searchFound() {
        TreeNode<Integer> root = canonicalTree();
        TreeNode<Integer> six = root.left.right;

        TreeNode<Integer> found = DFS.search(root, 6);

        assertSame(six, found);
        assertEquals(6, found.value);
    }

    @Test
    @DisplayName("default search returns null on miss and on null root")
    void searchMissAndNullRoot() {
        TreeNode<Integer> root = canonicalTree();

        assertNull(DFS.search(root, 99));
        assertNull(DFS.search(null, 6));
    }
}
