package pl.sborodziuk.datastructures.tree;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import pl.sborodziuk.datastructures.core.MyStack;
import pl.sborodziuk.datastructures.traverse.BreadthFirstSearch;
import pl.sborodziuk.datastructures.traverse.DepthFirstSearch;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

@DisplayName("BinarySearchTree")
class BinarySearchTreeTest {

    private static final DepthFirstSearch<Integer> DFS = new DepthFirstSearch<>();
    private static final BreadthFirstSearch<Integer> BFS = new BreadthFirstSearch<>();

    private BinarySearchTree<Integer> bst;

    private static List<Integer> values(MyStack<TreeNode<Integer>> history) {
        List<Integer> out = new ArrayList<>();
        while (!history.isEmpty()) {
            out.add(history.remove().value);
        }
        return out;
    }

    private static List<Integer> sortedValues(BinarySearchTree<Integer> tree) {
        List<Integer> out = values(tree.traverse(DFS));
        out.sort(null);
        return out;
    }

    private static void insertAll(BinarySearchTree<Integer> tree, Integer... values) {
        for (Integer v : values) {
            tree.insert(v);
        }
    }

    @BeforeEach
    void setUp() {
        bst = new BinarySearchTree<>();
    }

    @Test
    @DisplayName("canonical insert 8,3,10,1,6,14: size 6, root 8")
    void insertAndSize() {
        insertAll(bst, 8, 3, 10, 1, 6, 14);

        assertEquals(6, bst.size());
        assertFalse(bst.isEmpty());
        assertEquals(8, bst.root.value);
    }

    @Test
    @DisplayName("search finds 6 and misses on 99 (DFS)")
    void searchFoundAndMiss() {
        insertAll(bst, 8, 3, 10, 1, 6, 14);

        TreeNode<Integer> found = bst.search(6, DFS);
        assertEquals(6, found.value);
        assertNull(bst.search(99, DFS));
    }

    @Test
    @DisplayName("DFS traversal drains in reversed preorder: 14,10,6,1,3,8")
    void traverseDfsOrder() {
        insertAll(bst, 8, 3, 10, 1, 6, 14);

        assertEquals(List.of(14, 10, 6, 1, 3, 8), values(bst.traverse(DFS)));
    }

    @Test
    @DisplayName("BFS traversal drains in reversed level order: 14,6,1,10,3,8")
    void traverseBfsOrder() {
        insertAll(bst, 8, 3, 10, 1, 6, 14);

        assertEquals(List.of(14, 6, 1, 10, 3, 8), values(bst.traverse(BFS)));
    }

    @Test
    @DisplayName("delete(6) then delete(3): size drops to 4, both gone for both strategies, rest intact")
    void deleteRemovesElementAndDecrementsSize() {
        insertAll(bst, 8, 3, 10, 1, 6, 14);

        bst.delete(6);
        assertEquals(5, bst.size());

        bst.delete(3);
        assertEquals(4, bst.size());

        assertNull(bst.search(3, DFS));
        assertNull(bst.search(3, BFS));
        assertNull(bst.search(6, DFS));
        assertNull(bst.search(6, BFS));
        assertEquals(List.of(1, 8, 10, 14), sortedValues(bst));
    }

    @Test
    @DisplayName("delete of missing value on non-empty tree throws and keeps size")
    void deleteMissingThrows() {
        insertAll(bst, 8, 3, 10);

        assertThrows(NoSuchElementException.class, () -> bst.delete(99));
        assertEquals(3, bst.size());
    }

    @Test
    @DisplayName("delete on empty tree throws NoSuchElementException")
    void deleteOnEmptyThrows() {
        assertThrows(NoSuchElementException.class, () -> bst.delete(1));
    }

    @Test
    @DisplayName("empty tree: isEmpty true, size 0, search null for both strategies")
    void emptyTreeBehavior() {
        assertTrue(bst.isEmpty());
        assertEquals(0, bst.size());
        assertNull(bst.search(1, DFS));
        assertNull(bst.search(1, BFS));
    }
}
