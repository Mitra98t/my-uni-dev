public class Professor extends User {
  private static int professorId = 1;

  public static int getProfessorId() {
    return professorId;
  }

  public static void incrementProfessorId() {
    Professor.professorId++;
  }

  public Professor(Tutor tutor) {
    super(tutor);
    setUserType(Type.Professor);
    setName("Pro-" + Professor.getProfessorId());
    Professor.incrementProfessorId();
  }

  @Override
  public void run() {
    super.run();
  }

  @Override
  public String toString() {
    return getName();
  }
}
