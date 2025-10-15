import java.util.*;
public class Main {
    public static void main(String[] args) {
        Outer ot = new Outer();
        Outer.method().show();
    }
}

class Outer{
    public static Inter method(){
        return new Inter(){
            @Override
            public void show(){
                System.out.println("hello");
            }
        };
    }
}

class Inter{
    void show(){};
}
