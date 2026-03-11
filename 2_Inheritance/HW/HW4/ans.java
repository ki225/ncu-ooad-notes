class SuperMan {
    private int a;

    protected SuperMan(int a) {
        this.a = a;
    }
}

class SubMan extends SuperMan {
    public SubMan(int a) {
        super(a);
    }

    public SubMan() {
        super(5);
    }
}

public class ans {
    public static void main(String[] args) {
        SubMan s = new SubMan();
        System.out.println("OK");
    }
}