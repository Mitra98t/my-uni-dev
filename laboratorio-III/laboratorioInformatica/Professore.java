public class Professore extends Utente {

  public Professore(Tutor t) {
    super(t);
  }

  @Override
  public int compareTo(Utente o) {
    if (o instanceof Professore)
      return 1;
    else
      return -1;

  }

  @Override
  public String toString() {
    return "Professore " + id;
  }

}
