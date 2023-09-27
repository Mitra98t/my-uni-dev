public class Main {
  public static void main(String[] args) {

    Conta c = new Conta();
    int threadNumber = Integer.parseInt(args[0]);
    Thread[] threads = new Thread[threadNumber];

    long startTime = System.currentTimeMillis();

    for (int i = 0; i < threads.length; i++) {
      threads[i] = new Thread(c);
      threads[i].start();
    }

    for (Thread thread : threads) {
      try {
        thread.join();
      } catch (Exception e) {
        System.out.println(e.getMessage());
      }
    }

    long endTime = System.currentTimeMillis();
    long elapsedTime = endTime - startTime;
    System.out.println("Tempo impiegato: " + elapsedTime + "ms");
  }
}
