import java.util.*;
public class Main {
    public static void main(String[] args) {
        PersonDemo pd = new PersonDemo();
        pd.method(
            new Person(){
                public void show(){
                    System.out.println("ahasdsabuifbqufbqubef");
                }
            }
        );
    }
}

abstract class Person{
    public abstract void show();
}

class PersonDemo{
    public void method(Person p){
        p.show();
    }
}
