package pl.sborodziuk.javamarkt.model;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

class ProductCatalogTest {

    @Test
    void addProductRejectsDuplicateCodeRegardlessOfOtherFields() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCD1", "Original name", 10.0));

        assertThrows(IllegalArgumentException.class,
                () -> catalog.addProduct(new Product("PCD1", "Different name", 99.0)));

        Product kept = catalog.findByCode("PCD1");
        assertAll(
                () -> assertEquals("Original name", kept.getName()),
                () -> assertEquals(10.0, kept.getPrice()));
    }

    @Test
    void addProductAcceptsSameNameAndPriceWithDifferentCode() {
        ProductCatalog catalog = new ProductCatalog();

        catalog.addProduct(new Product("PCA1", "Same product", 42.0));
        catalog.addProduct(new Product("PCA2", "Same product", 42.0));

        assertAll(
                () -> assertEquals("Same product", catalog.findByCode("PCA1").getName()),
                () -> assertEquals("Same product", catalog.findByCode("PCA2").getName()));
    }

    @Test
    void addProductRejectsNullProduct() {
        ProductCatalog catalog = new ProductCatalog();

        assertThrows(IllegalArgumentException.class, () -> catalog.addProduct(null));
    }

    @Test
    void updateProductReplacesExistingProduct() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCU1", "Original", 10.0));

        catalog.updateProduct(new Product("PCU1", "Updated", 25.0));

        Product updated = catalog.findByCode("PCU1");
        assertAll(
                () -> assertEquals("Updated", updated.getName()),
                () -> assertEquals(25.0, updated.getPrice()),
                () -> assertEquals(1, catalog.getSize()));
    }

    @Test
    void updateProductRejectsUnknownCode() {
        ProductCatalog catalog = new ProductCatalog();

        assertThrows(IllegalArgumentException.class,
                () -> catalog.updateProduct(new Product("PCU999", "Ghost", 1.0)));
        assertNull(catalog.findByCode("PCU999"));
    }

    @Test
    void updateProductRejectsNullProduct() {
        ProductCatalog catalog = new ProductCatalog();

        assertThrows(IllegalArgumentException.class, () -> catalog.updateProduct(null));
    }

    @Test
    void removeProductRemovesProductByCode() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCR1", "Removable", 5.0));

        assertTrue(catalog.removeProduct("PCR1"));
        assertNull(catalog.findByCode("PCR1"));
    }

    @Test
    void removeProductReturnsFalseForUnknownCode() {
        ProductCatalog catalog = new ProductCatalog();

        assertFalse(catalog.removeProduct("PCX999"));
    }

    @Test
    void removeProductRejectsBlankCode() {
        ProductCatalog catalog = new ProductCatalog();

        assertAll(
                () -> assertThrows(IllegalArgumentException.class, () -> catalog.removeProduct("")),
                () -> assertThrows(IllegalArgumentException.class, () -> catalog.removeProduct("   ")),
                () -> assertThrows(IllegalArgumentException.class, () -> catalog.removeProduct(null)));
    }

    @Test
    void findByCodeUsesExactKey() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCW1", "Whitespace test", 1.0));

        assertAll(
                () -> assertEquals("PCW1", catalog.findByCode("PCW1").getCode()),
                () -> assertNull(catalog.findByCode("  PCW1  ")));
    }

    @Test
    void getAllProductsReturnsEveryRegisteredProduct() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCT3", "Third", 3.0));
        catalog.addProduct(new Product("PCT1", "First", 1.0));
        catalog.addProduct(new Product("PCT2", "Second", 2.0));

        Product[] all = catalog.getAllProducts();
        List<String> codes = new ArrayList<>();
        for (Product product : all) {
            codes.add(product.getCode());
        }

        assertAll(
                () -> assertEquals(3, all.length),
                () -> assertEquals(Set.of("PCT1", "PCT2", "PCT3"), new HashSet<>(codes)));
    }

    @Test
    void iterationYieldsExactlyTheAddedProducts() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCT3", "Third", 3.0));
        catalog.addProduct(new Product("PCT1", "First", 1.0));
        catalog.addProduct(new Product("PCT2", "Second", 2.0));

        List<String> codes = new ArrayList<>();
        for (Product product : catalog) {
            codes.add(product.getCode());
        }

        assertAll(
                () -> assertEquals(3, codes.size()),
                () -> assertEquals(Set.of("PCT1", "PCT2", "PCT3"), new HashSet<>(codes)));
    }

    @Test
    void isEmptyAndGetSizeReflectCatalogContent() {
        ProductCatalog catalog = new ProductCatalog();

        assertTrue(catalog.isEmpty());
        assertEquals(0, catalog.getSize());

        catalog.addProduct(new Product("PCS1", "Single", 1.0));

        assertFalse(catalog.isEmpty());
        assertEquals(1, catalog.getSize());
    }
}
