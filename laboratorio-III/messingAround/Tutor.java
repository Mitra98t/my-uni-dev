import java.time.Instant;
import java.util.Comparator;
import java.util.PriorityQueue;


public class Tutor {
  private Computer[] labComputers = new Computer[20];
  PriorityQueue<User> reqQueue = new PriorityQueue<>(new UserComparator());

  public Tutor() {
    for (int i = 0; i < labComputers.length; i++) {
      labComputers[i] = new Computer();
    }
  }

  public synchronized void request(User user) {
    switch (user.getUserType()) {
      case Professor:
        professorRequest((Professor) user);
        break;
      case Student:
        studentRequest((Student) user);
        break;
      case ThesisWorker:
        break;
      case User:
        break;
    }
    notifyAll();
  }

  public synchronized void request(ThesisWorker t, int position) {
    t.requestTime = Instant.now();
    reqQueue.add(t);
    System.out.println(t.toString() + " requested a computer at " + t.requestTime + " at position " + (position + 1));
    while (reqQueue.peek() != null && !reqQueue.peek().toString().equals(t.toString())
        || checkInUse(labComputers[position])) {
      try {
        wait();
      } catch (InterruptedException e) {
        Util.printStackTrace(e);
      }
    }
    labComputers[position].occupy(t.toString());
    System.out.println("Served: " + reqQueue.poll().toString() + " at " + Instant.now());
    notifyAll();
  }

  private void professorRequest(Professor p) {
    p.requestTime = Instant.now();
    reqQueue.add(p);
    System.out.println(p.toString() + " requested the laboratory at " + p.requestTime);
    for (Computer c : labComputers) {
      while (reqQueue.peek() != null && !reqQueue.peek().toString().equals(p.toString())
          || checkInUse(c)) {
        try {
          wait();
        } catch (InterruptedException e) {
          Util.printStackTrace(e);
        }
      }
      c.occupy(p.toString());
    }
    System.out.println("Served: " + reqQueue.poll().toString() + " at " + Instant.now());
  }

  private void studentRequest(Student s) {
    int freeComputerPos = -1;
    for (int i = 0; i < labComputers.length; i++) {
      if (!checkInUse(labComputers[i])) {
        freeComputerPos = i;
        break;
      }
    }
    s.requestTime = Instant.now();
    reqQueue.add(s);
    System.out.println(s.toString() + " requested a computer at " + s.requestTime);
    while (reqQueue.peek() != null || checkInUse(labComputers[freeComputerPos])) {
      try {
        wait();
      } catch (InterruptedException e) {
        Util.printStackTrace(e);
      }
    }
    labComputers[freeComputerPos].occupy(s.toString());
    System.out.println("Served: " + reqQueue.poll().toString() + " at " + Instant.now());
  }

  public synchronized void free(User user) {
    switch (user.getUserType()) {
      case Professor:
        professorFree((Professor) user);
        break;
      case Student:
        studentFree((Student) user);
        break;
      case ThesisWorker:
        break;
      case User:
        break;
    }
    notifyAll();
  }

  public synchronized void free(ThesisWorker t, int position) {
    if(t.toString().equals(labComputers[position].getUser()) && checkInUse(labComputers[position])) {
      labComputers[position].free();
      System.out.println(t + " freed computer " + position + 1 + " at " + Instant.now());
    }
    else {
      System.out.println("Computer not occupied by " + t.toString());
    }
    notifyAll();
  }

  private void professorFree(Professor p) {
    for (Computer c : labComputers) {
      if (c.getUser().equals(p.toString()) && checkInUse(c)) {
        c.free();
      }
    }
    System.out.println(p.toString() + " freed the laboratory at " + Instant.now());
  }

  private void studentFree(Student s) {
    for (Computer c : labComputers) {
      if (c.getUser().equals(s.toString()) && checkInUse(c)) {
        c.free();
      }
    }
    System.out.println(s.toString() + " freed a computer at " + Instant.now());
  }
  
  private boolean checkInUse(Computer c) {
    return c.isInUse();
  }

  class UserComparator implements Comparator<User> {
    @Override
    public int compare(User u1, User u2) {
      int res = u1.getUserType().compareTo(u2.getUserType());
      return res != 0 ? res : u1.getRequestTime().compareTo(u2.getRequestTime());
    }
  }
}
