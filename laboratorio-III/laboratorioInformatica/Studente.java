public class Studente extends Utente {

  public Studente(Tutor t) {
    super(t);
  }

  @Override
  public String toString() {
    return "Studente " + id;
  }

  @Override
  public int compareTo(Utente o) {
    return 1;
  }
}
