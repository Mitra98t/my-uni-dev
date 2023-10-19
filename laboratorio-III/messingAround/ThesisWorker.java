public class ThesisWorker extends User {

  private static int thesisWorkerId = 1;
  private final int position = Util.getRandomInt(0, 19);

  public int getPosition() {
    return position;
  }

  public static int getThesisWorkerId() {
    return thesisWorkerId;
  }

  public static void incrementThesisWorkerId() {
    ThesisWorker.thesisWorkerId++;
  }

  public ThesisWorker(Tutor tutor) {
    super(tutor);
    setUserType(Type.ThesisWorker);
    setName("The-" + ThesisWorker.getThesisWorkerId());
    ThesisWorker.incrementThesisWorkerId();
  }

  @Override
  public void run() {
    for(int i =0; i < requests; i++){
      tutor.request(this, position);
      Util.threadRandomSleep();
      tutor.free(this, position);
      Util.threadRandomSleep();
    }
  }

  @Override
  public String toString() {
    return getName();
  }

}
