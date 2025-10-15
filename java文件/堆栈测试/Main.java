public class Main {
    private static int depth = 0;

    public static void main(String[] args) {
        try {
            recursiveCall();
        } catch (StackOverflowError e) {
            System.out.println("最大堆栈深度: " + depth);
            System.out.println("StackOverflowError 异常捕获，程序停止");
        }
    }

    private static void recursiveCall() {
        depth++;
        recursiveCall();
    }
}