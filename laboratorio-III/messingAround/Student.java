public class Student extends User {
  public Student(Tutor tutor) {
    super(tutor);
    setUserType(Type.Student);
    setName("Stu-" + Student.getStudentId());
    Student.incrementStudentId();
  }

  private static int studentId = 1;

  public static int getStudentId() {
    return Student.studentId;
  }

  private static void incrementStudentId() {
    Student.studentId++;
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
