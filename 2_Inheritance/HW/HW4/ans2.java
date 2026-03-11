class SuperMan{
    protected int a;
    protected SuperMan(int a){this.a = a;}
    protected SuperMan(){}
}

class SubMan extends SuperMan{
    public SubMan(int a){super(a);}
    public SubMan(){this.a = 5;}
} 

public class question {
    public static void main(String[] args) {
        SubMan s = new SubMan();
        System.out.println("OK");
    }
}