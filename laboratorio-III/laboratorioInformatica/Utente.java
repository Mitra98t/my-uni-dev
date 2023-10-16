import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicInteger;

public abstract class Utente extends Thread implements Comparable<Utente> {
  private static AtomicInteger n = new AtomicInteger(1);
  public final int id;
  private int k;
  private final Tutor labTutor;
  private boolean lab = false;
  public int pc;

  public Utente(Tutor t) {
    id = n.getAndIncrement();
    k = ThreadLocalRandom.current().nextInt(9) + 1;
    labTutor = t;
    lab = false;
  }

  public abstract String toString();

  public void run() {
    try {
      for (int i = 0; i < k; i++) {
        Thread.sleep(ThreadLocalRandom.current().nextInt(1000) + 1);
        scegli_pc();
        if (this.labTutor.richiesta(this)) {
          while (lab) {
            int n = ThreadLocalRandom.current().nextInt(1000) + 1;
            System.out.println("Uso laboratorio per " + n + "ms");
            Thread.sleep(n);
            this.labTutor.rilascio(this);
          }
        }
      }
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }

  public void set_lab(boolean b) {
    this.lab = b;
  }

  public boolean get_lab() {
    return this.lab;
  }

  public int get_pc() {
    return pc;
  }

  public void set_pc(int pc) {
    this.pc = pc;
  }

  protected void scegli_pc() {
  }
}
