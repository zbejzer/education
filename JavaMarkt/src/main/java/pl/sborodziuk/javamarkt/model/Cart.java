package pl.sborodziuk.javamarkt.model;

import static java.util.Arrays.copyOf;

public class Cart {
    private CartItem[] items;
    private int size;

    public Cart() {
        this.items = new CartItem[0];
        this.size = 0;
    }

    public CartItem[] getAllItems() {
        return items;
    }

    public void addProduct(Product product) {
        items = copyOf(items, size + 1);
        items[size] = new CartItem(product);
        size++;
        recalculate();
    }

    public Product removeProduct(String code) {
        if (code == null || code.isBlank()) {
            throw new IllegalArgumentException("Product code cannot be blank.");
        }

        for (int i = 0; i < size; i++) {
            if (!items[i].getCode().equals(code)) {
                continue;
            }
            Product removed = items[i].getProduct();
            CartItem[] updated = copyOf(items, size - 1);
            System.arraycopy(items, i + 1, updated, i, size - i - 1);
            items = updated;
            size--;
            recalculate();
            return removed;
        }
        return null;
    }

    public int getSize() {
        return size;
    }

    public void recalculate() {
        for (CartItem p : items) {
            p.setDiscountPrice(p.getPrice());
        }
    }
}
