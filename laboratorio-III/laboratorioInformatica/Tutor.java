import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.concurrent.PriorityBlockingQueue;

public class Tutor extends Thread {
  private PriorityBlockingQueue<Utente> codaStudenti;
  private boolean open = true;

  public Tutor() {
    System.out.println(codaStudenti);
  }

  public void set_coda_studenti(ArrayList<Utente> utenti) {
    this.codaStudenti = new PriorityBlockingQueue<Utente>(utenti);
  }

  public void set_open(boolean open) {
    this.open = open;
  }
}
