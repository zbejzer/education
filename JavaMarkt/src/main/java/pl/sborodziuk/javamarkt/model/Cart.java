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

    public int getSize() {
        return size;
    }

    public void recalculate() {
        for (CartItem p : items) {
            p.setDiscountPrice(p.getPrice());
        }
    }
}
