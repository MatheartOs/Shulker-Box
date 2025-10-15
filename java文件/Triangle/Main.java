import java.util.Scanner;

public class Main{
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        while (n > 0) {
            int a = input.nextInt();
            int b = input.nextInt();
            int c = input.nextInt();
            try {
                Triangle t1 = new Triangle(a, b, c);
                System.out.println(t1.getPerimeter());

            } catch (IllegalTriangleException ex) {
                System.out.println(ex);
            }
            n--;
        }
    }
} 

class Triangle{
    private int a;
    private int b;
    private int c;

    public Triangle(int a, int b, int c) throws IllegalTriangleException{
        if(a<0||b<0||c<0||a+b<=c||a+c<=b||b+c<=a){
            throw new IllegalTriangleException(a, b, c);
        }else{
        this.a = a;
        this.b = b;
        this.c = c;
        }
    }

    public int getPerimeter(){
        return this.a+this.b+this.c;
    }
}

class IllegalTriangleException extends Exception{
    int a;
    int b;
    int c;
    public IllegalTriangleException(int side1, int side2, int side3){
        this.a = side1;
        this.b = side2;
        this.c = side3;
    }
    @Override
    public String toString(){
        return "IllegalTriangleException: The sum of any two sides must greater than the other side and the sides must greater than zero,"+a+","+b+","+c+" can not contruct a triangle";
    }
}