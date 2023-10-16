import java.util.NoSuchElementException;
import java.util.concurrent.PriorityBlockingQueue;

public class Tutor extends Thread {
  private final int n = 20;
  private boolean[] computer;
  private boolean disponibile;
  private Boolean libero;
  private int nUtenti;
  private PriorityBlockingQueue<Utente> queue;
  private boolean open;

  public Tutor() {
    this.open = true;
    this.computer = new boolean[n];
    this.disponibile = true;
    this.libero = true;
    this.nUtenti = 0;
    this.queue = new PriorityBlockingQueue<Utente>();
    for (int i = 0; i < n; i++) {
      computer[i] = true;
    }
  }

  public boolean richiesta(Utente user) {
    try {
      synchronized (this) {
        System.out.println("Richiesta uso laboratorio di: " + user);
        queue.add(user);
        notify();
      }

      synchronized (user) {
        try {
          if (!user.get_lab())
            user.wait();
        } catch (InterruptedException e) {
          // gestione dell'eccezione InterruptedException
          e.printStackTrace();
        } catch (Exception e) {
          // gestione di tutte le altre eccezioni
          e.printStackTrace();
        }
      }
      return true;
    } catch (IllegalMonitorStateException e) {
      System.err.println(e.getMessage());
      return false;
    }
  }

  public void rilascio(Utente user) {
    System.out.println(user + " rilascio posizione");
    user.set_lab(false);
    synchronized (this) {
      this.nUtenti--;
      if (user instanceof Studente || user instanceof Tesista)
        computer[user.get_pc()] = true;
      if (nUtenti == 0)
        this.libero = true;
      if (user instanceof Professore || nUtenti == n - 1)
        disponibile = true;
      notify();
    }
  }

  public void run() {
    Utente user;
    try {
      while (open) {
        synchronized (this) {
          while(queue.isEmpty() || !disponibile){
            if(!open) break;
            wait();
          }

          if(!open) break;

          user = queue.peek();

          if(user == null) System.exit(1);

          if(user instanceof Professore){
            while(!libero) wait();
            user = queue.remove();
          }
          else if((user instanceof Tesista && computer[user.get_pc()]) || user instanceof Studente)
            user = queue.remove();
          else{
            wait();
            continue;
          }
        }
        if(user instanceof Studente){
          synchronized(computer){
            for (int i = 0; i < n; i++) {
              if(computer[i]){
                user.set_pc(i);
                break;
              }
            }
          }
        }
        entra(user);
      }
    }
    catch(InterruptedException e){System.err.println(e.getMessage());}
    catch(NoSuchElementException e){System.err.println(e.getMessage());}
  }

  private void entra(Utente user) {
    if (user == null)
      System.exit(1);
    if (user instanceof Professore) {
      if (this.nUtenti != 0 || !disponibile || !libero)
        System.exit(2);
      this.nUtenti = 1;
      this.disponibile = this.libero = false;
    } else {
      int pc = user.get_pc();
      if (pc < 0 || pc > n)
        System.err.println("PC non valido");
      else {
        if (!computer[pc])
          System.exit(2);
        synchronized (this) {
          this.computer[pc] = false;
          this.nUtenti++;
          this.libero = false;
          this.disponibile = false;
        }
      }
    }
    synchronized (user) {
      user.set_lab(true);
      user.notifyAll();
    }
  }

  public synchronized void set_open(boolean b) {
    open = b;
    notify();
  }
}
