import java.util.ArrayList;

public class Main {
  public static void main(String[] args) {
    // Your code here
    int nStudenti = 10, nProfessori = 10, nTesisti = 10;

    if (args.length != 3) {
      System.err.println("Parametri errati");
      System.exit(4);
    }

    nProfessori = Integer.parseInt(args[0]);
    nTesisti = Integer.parseInt(args[1]);
    nStudenti = Integer.parseInt(args[2]);

    Tutor tutor = new Tutor();

    tutor.start();

    ArrayList<Utente> utenti = new ArrayList<Utente>();
    for (int i = 0; i < nProfessori; i++) {
      utenti.add(new Professore(tutor));
    }
    for (int i = 0; i < nTesisti; i++) {
      utenti.add(new Tesista(tutor));
    }
    for (int i = 0; i < nStudenti; i++) {
      utenti.add(new Studente(tutor));
    }

    utenti.forEach(t -> t.start());

    utenti.forEach((t) -> {
      try {
        t.join();
      } catch (InterruptedException e) {
        System.err.println(e.getMessage());
      }
    });
    System.out.println("Main: Chiudo il laboratorio");
    tutor.set_open(false);

    try {
      tutor.join();
    } catch (InterruptedException e) {
      System.err.println(e.getMessage());
    }
  }
}
