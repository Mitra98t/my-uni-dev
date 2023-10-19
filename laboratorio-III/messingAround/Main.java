import java.util.ArrayList;
import java.util.Collections;

public class Main {
  public static void main(String[] args) {
    final int professors, students, thesisWorkers;

    try{
      professors = Integer.parseInt(args[0]);
      students = Integer.parseInt(args[2]);
      thesisWorkers = Integer.parseInt(args[1]);

      Tutor tutor = new Tutor();

      ArrayList<User> users = new ArrayList<User>();

      for(int i = 0; i < professors; i++){
        users.add(new Professor(tutor));
      }

      for(int i = 0; i < students; i++){
        users.add(new Student(tutor));
      }

      for(int i = 0; i < thesisWorkers; i++){
        users.add(new ThesisWorker(tutor));
      }

      Collections.shuffle(users);

      users.forEach( (user) -> new Thread(user).start());

    } catch (Exception e) {
      Util.printStackTrace(e);
      return;
    }
  }
}
