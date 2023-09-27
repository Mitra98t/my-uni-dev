public class Conta implements Runnable {
  public void run() {
    int start = 1;
    int end = 10_000_000;
    int primeCounter = 0;

    for (int i = start; i <= end; i++) {
      if (isPrime(i))
        primeCounter++;
    }

    // System.out.println("sono stati trovati " + primeCounter + " numeri primi.");

  }

  public static boolean isPrime(int n) {
    if (n <= 1) {
      return false;
    }

    if (n <= 3) {
      return true;
    }

    for (int i = 4; i <= Math.sqrt(n); i++) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;
  }

}