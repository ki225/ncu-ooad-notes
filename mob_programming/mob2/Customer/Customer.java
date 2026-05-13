package Customer;

public class Customer {
    private String name;
    // 原本在想要不要在這邊存 totalPoint，但想想覺得用 system function 直接計算就好，不用存兩次

    public Customer(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
