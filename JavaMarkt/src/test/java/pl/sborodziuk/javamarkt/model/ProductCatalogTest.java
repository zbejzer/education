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
    void removeProductRemovesProductByCode() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCR1", "Removable", 5.0));

        assertTrue(catalog.removeProduct("PCR1"));
        assertNull(catalog.findByCode("PCR1"));
    }

    @Test
    void removeProductRemovesOnlyTargetProduct() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCR2", "Removable", 5.0));
        catalog.addProduct(new Product("PCR3", "Kept", 7.0));

        assertTrue(catalog.removeProduct("PCR2"));

        assertAll(
                () -> assertNull(catalog.findByCode("PCR2")),
                () -> assertEquals("Kept", catalog.findByCode("PCR3").getName()),
                () -> assertEquals(1, catalog.getSize()));
    }

    @Test
    void addProductAllowsReAddingCodeAfterRemoval() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCR4", "Original", 5.0));

        catalog.removeProduct("PCR4");
        catalog.addProduct(new Product("PCR4", "Replacement", 9.0));

        Product reAdded = catalog.findByCode("PCR4");
        assertAll(
                () -> assertEquals("Replacement", reAdded.getName()),
                () -> assertEquals(9.0, reAdded.getPrice()),
                () -> assertEquals(1, catalog.getSize()));
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
                () -> assertNull(catalog.findByCode("  PCW1  ")),
                () -> assertNull(catalog.findByCode("pcw1")));
    }

    @Test
    void findByCodeReturnsNullForNullOrBlankCode() {
        ProductCatalog catalog = new ProductCatalog();

        assertAll(
                () -> assertNull(catalog.findByCode(null)),
                () -> assertNull(catalog.findByCode("")),
                () -> assertNull(catalog.findByCode("   ")));
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
    void getAllProductsReturnsSnapshotUnaffectedByLaterChanges() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCT4", "Fourth", 4.0));

        Product[] snapshot = catalog.getAllProducts();
        catalog.addProduct(new Product("PCT5", "Fifth", 5.0));

        assertAll(
                () -> assertEquals(1, snapshot.length),
                () -> assertEquals(2, catalog.getSize()),
                () -> assertEquals(2, catalog.getAllProducts().length));
    }

    @Test
    void iterationReflectsRemoval() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCT6", "Sixth", 6.0));
        catalog.addProduct(new Product("PCT7", "Seventh", 7.0));
        catalog.removeProduct("PCT6");

        List<String> codes = new ArrayList<>();
        for (Product product : catalog) {
            codes.add(product.getCode());
        }

        assertEquals(List.of("PCT7"), codes);
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
    void isEmptyAndGetSizeReflectRemoval() {
        ProductCatalog catalog = new ProductCatalog();
        catalog.addProduct(new Product("PCS2", "Transient", 2.0));

        catalog.removeProduct("PCS2");

        assertAll(
                () -> assertTrue(catalog.isEmpty()),
                () -> assertEquals(0, catalog.getSize()));
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
