import java.util.Queue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Ufficio {
  public void apriSportelli(Queue<Persona> personeAttesa) {
    ExecutorService codaInterna = Executors.newFixedThreadPool(4);
    while (!personeAttesa.isEmpty()) {
      codaInterna.execute(personeAttesa.poll());
    }
    codaInterna.shutdown();
    while (!codaInterna.isTerminated()) {
    }
    System.out.println("Tutti gli sportelli sono chiusi.");
  }
}