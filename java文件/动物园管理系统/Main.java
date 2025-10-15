import java.util.*;
public class Main {
    public static void main(String[] args) {
        Zoo zoo = new Zoo();
        
        // 添加狮子
        zoo.addAnimal(new Lion("Simba", 5));
        
        // 添加大象
        zoo.addAnimal(new Elephant("Dumbo", 10));
        
        // 添加匿名内部类实现的临时动物
        zoo.addTemporaryAnimal();
        
        // 展示所有动物行为
        zoo.showAllAnimals();
        
        // 多态演示
        Animal animal1 = new Lion("Leo", 4);
        Animal animal2 = new Elephant("Jumbo", 8);
        
        animal1.makeSound();
        animal2.makeSound();
    }
}

abstract class Animal{
    protected String name;
    protected int age;

    public Animal(String name, int age){
        this.name = name;
        this.age = age;
    }

    abstract public void makeSound();

    public void eat(){
        System.out.println(name + "正在吃东西");
    }
}

interface SpecialAbility{
    public void performTrick();
}

class Lion extends Animal implements SpecialAbility{
    public Lion(String name, int age){
        super(name,age);
    }

    @Override
    public void performTrick(){
        System.out.println("狮子 " + name + " 正在跳火圈");
    }

    @Override
    public void makeSound(){
        System.out.println("狮子 " + name + " 正在叫");
    }
}

class Elephant extends Animal implements SpecialAbility{
    public Elephant(String name, int age){
        super(name,age);
    }

    @Override
    public void makeSound(){
        System.out.println("大象 " + name + " 正在叫");
    }

    @Override
    public void performTrick(){
        System.out.println("大象 " + name + " 表演了踩踩背");
    }

    public class Memory {
        public void remember(double number){
            System.out.println("大象 " + name + " 的记忆里特别好，它记住了你给出的数字：" + number);
        }
    }
}

class Zoo{
    private List<Animal> animals = new ArrayList<>();

    public void addAnimal(Animal animal){
        animals.add(animal);
    }

    public void showAllAnimals(){
        for(Animal animal : animals){
            System.out.println("--- " + animal.name + " ---");
            animal.makeSound();
            animal.eat();

            if(animal instanceof SpecialAbility){
                ((SpecialAbility)animal).performTrick();
            }

            if(animal instanceof Elephant){
                ((Elephant)animal).new Memory().remember(animal.age);
            }
        }
    }

    public void addTemporaryAnimal(){
        Animal tempAnimal = new Animal("???", 1){
            @Override
            public void makeSound() {
                System.out.println("临时动物 " + name + " 发出了诡异的叫声");
            }
        };
        animals.add(tempAnimal);
    }
}