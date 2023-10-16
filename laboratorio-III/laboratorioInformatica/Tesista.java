import java.util.concurrent.ThreadLocalRandom;

public class Tesista extends Utente {

  public Tesista(Tutor t) {
    super(t);
  }

  @Override
  public int compareTo(Utente o) {

    if (o instanceof Professore)
      return 1;
    if (o instanceof Tesista)
      return 1;
    else
      return -1;
  }

  @Override
  public String toString() {
    return "Tesista " + id + " (pc: " + pc + ")";
  }

  @Override
  protected void scegli_pc() {
    this.pc = ThreadLocalRandom.current().nextInt(20);
  }
}
