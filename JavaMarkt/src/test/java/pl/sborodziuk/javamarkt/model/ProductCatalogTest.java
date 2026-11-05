package pl.sborodziuk.javamarkt.model;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class ProductCatalogTest {

    @Test
    void getInstanceReturnsSameInstanceOnEveryCall() {
        ProductCatalog first = ProductCatalog.getInstance();
        ProductCatalog second = ProductCatalog.getInstance();

        assertSame(first, second);
    }

    @Test
    void addProductRejectsDuplicateCodeRegardlessOfOtherFields() {
        ProductCatalog catalog = ProductCatalog.getInstance();
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
        ProductCatalog catalog = ProductCatalog.getInstance();

        catalog.addProduct(new Product("PCA1", "Same product", 42.0));
        catalog.addProduct(new Product("PCA2", "Same product", 42.0));

        assertAll(
                () -> assertEquals("Same product", catalog.findByCode("PCA1").getName()),
                () -> assertEquals("Same product", catalog.findByCode("PCA2").getName()));
    }

    @Test
    void addProductRejectsNullProduct() {
        ProductCatalog catalog = ProductCatalog.getInstance();

        assertThrows(IllegalArgumentException.class, () -> catalog.addProduct(null));
    }

    @Test
    void removeProductRemovesProductByCode() {
        ProductCatalog catalog = ProductCatalog.getInstance();
        catalog.addProduct(new Product("PCR1", "Removable", 5.0));

        assertTrue(catalog.removeProduct("PCR1"));
        assertNull(catalog.findByCode("PCR1"));
    }

    @Test
    void removeProductReturnsFalseForUnknownCode() {
        ProductCatalog catalog = ProductCatalog.getInstance();

        assertFalse(catalog.removeProduct("PCX999"));
    }

    @Test
    void removeProductRejectsBlankCode() {
        ProductCatalog catalog = ProductCatalog.getInstance();

        assertAll(
                () -> assertThrows(IllegalArgumentException.class, () -> catalog.removeProduct("")),
                () -> assertThrows(IllegalArgumentException.class, () -> catalog.removeProduct("   ")),
                () -> assertThrows(IllegalArgumentException.class, () -> catalog.removeProduct(null)));
    }

    @Test
    void findByCodeIgnoresSurroundingWhitespace() {
        ProductCatalog catalog = ProductCatalog.getInstance();
        catalog.addProduct(new Product("PCW1", "Whitespace test", 1.0));

        assertEquals("PCW1", catalog.findByCode("  PCW1  ").getCode());
    }

    @Test
    void iterationYieldsProductsSortedByCode() {
        ProductCatalog catalog = ProductCatalog.getInstance();
        catalog.addProduct(new Product("PCT3", "Third", 3.0));
        catalog.addProduct(new Product("PCT1", "First", 1.0));
        catalog.addProduct(new Product("PCT2", "Second", 2.0));

        List<String> codes = new ArrayList<>();
        for (Product product : catalog) {
            codes.add(product.getCode());
        }

        List<String> sortedTestCodes = codes.stream()
                .filter(code -> code.startsWith("PCT"))
                .toList();
        assertEquals(List.of("PCT1", "PCT2", "PCT3"), sortedTestCodes);
    }
}
