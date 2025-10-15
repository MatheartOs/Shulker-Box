import java.util.*;

class InsufficientFundsException extends Exception{
    public InsufficientFundsException(String massage){
        super(massage);
    }
}

class InvalidAmountException extends Exception{
    public InvalidAmountException(String massage){
        super(massage);
    }
}

class BankAccount{
    private double balance;

    public BankAccount(double balance){
        this.balance = balance;
    }

    public void deposit(double amount) throws InvalidAmountException{
        if(amount < 0){
            throw new InvalidAmountException("存款金额不能为负数");
        }else{
            this.balance += amount;
        }
    }

    public void withdraw(double amount) throws InsufficientFundsException{
        if(balance < amount){
            throw new InsufficientFundsException("余额不足");
        }else{
            this.balance -= amount;
        }
    }

    public double getBalance(){
        return this.balance;
    }
}

// 测试类
public class BankTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        BankAccount account = new BankAccount(10000);
        while (true) {
            try{
            int opt = sc.nextInt();
            switch (opt) {
                case 1:
                    double amount1 = sc.nextDouble();
                    account.deposit(amount1);
                    break;
            
                case 2:
                    double amount2 = sc.nextDouble();
                    account.withdraw(amount2);
                    break;
            
                case 3:
                    System.out.println(account.getBalance());
                    break;
            
                default:
                    break;
                }
            }
            catch(InvalidAmountException e){
                System.out.println("发生异常: " + e.getMessage());
                break;
            }catch(InsufficientFundsException e){
                System.out.println("发生异常: " + e.getMessage());
                break;
            }
        }
    }
}