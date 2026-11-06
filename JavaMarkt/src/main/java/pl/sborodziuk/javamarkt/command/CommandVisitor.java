package pl.sborodziuk.javamarkt.command;

public interface CommandVisitor<T> {
    T visitAddProduct(AddProductCommand command);

    T visitRegisterProduct(RegisterProductCommand command);

    T visitUnregisterProduct(UnregisterProductCommand command);
}
