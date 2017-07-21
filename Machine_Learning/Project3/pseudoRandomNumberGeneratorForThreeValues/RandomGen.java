import java.util.Random;

public class RandomGen {
  public static void main(String[] args) {
   
    Random randSeedGen = new Random();
  
    for(int i = 0; i < 3; i++) {

      Random randNumGen = new Random(randSeedGen.nextInt());
      int num = randNumGen.nextInt(100);
      System.out.println("randomly chose: " + num);

    }

  }
}

