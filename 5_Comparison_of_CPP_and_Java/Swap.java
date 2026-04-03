class IntClass {
    int value;
    IntClass(int value) {
        this.value = value;
    }
}

public class Swap {
    public static void main(String[] args) {
        IntClass a = new IntClass(10);
        IntClass b = new IntClass(20);
        swap(a, b);
        System.out.println("a = " + a.value + ", b = " + b.value); 
    }

    public static void swap(IntClass a, IntClass b) {
        int temp = a.value;
        a.value = b.value;
        b.value = temp;
    }
}