import java.util.concurrent.ThreadLocalRandom;

public class Util {

  public static void printStackTrace(Exception e){
    System.out.println("String: " + e.toString());
    System.out.println("Message: " + e.getMessage());
    System.out.println("Stack Trace: ");
    e.printStackTrace();
  }
  
  public static int getRandomInt(int origin, int bound){
    return ThreadLocalRandom.current().nextInt(origin, ++bound);
  }

  public static void threadRandomSleep(){
    try{
      Thread.sleep(Util.getRandomInt(1,10)*1000);
    } catch (InterruptedException e){
      Util.printStackTrace(e);
    }
  }
}
