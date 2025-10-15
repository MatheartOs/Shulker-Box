import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.*;
public class Main {

    static Queue<BigDecimal> q = new LinkedList<>();
 public static void main(String[] args) {
        double s=0;
        Scanner sc=new Scanner(System.in);
        double r1,r2;
        r1=sc.nextDouble();
        r2=sc.nextDouble();
        Circle c1=new Circle(r1);
        Circle c2=new Circle(r2);
        try{
        s = c1.area();
        System.out.println(s);
        s = c2.area();
        System.out.println(s);
        }
        catch (CircleException e){
            e.print();
        }
   }
}

class Circle{
    static double PI = 3.14d;
    public double r;
    public Circle(double r){
        this.r = r;
    }
    public double area() throws CircleException{
        if(this.r <0){
            throw new CircleException(this.r);
        }else{
            return PI * this.r * this.r;
        }
    }
}

class CircleException extends Exception{
    double r;
    public CircleException(double r){
        this.r = r;
    }
    public void print(){
        System.out.println("圆半径为"+r+"不合理");
    }
}