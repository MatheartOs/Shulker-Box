import java.util.*;

public class Main {
    public static void main(String[] args) {
        Runnable task = new Runnable() {
            @Override
            public void run(){
                System.out.println("Hello, Anonymous Inner Class!");
            }
        };

        Thread thread = new Thread(task);
        thread.start();
        try {
            thread.join(); // 等待线程执行完成
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Thread has finished execution.");
        
    }
}
