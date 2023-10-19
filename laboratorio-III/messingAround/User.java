import java.time.Instant;

public class User extends Thread{
  public static enum Type {
    Professor, ThesisWorker, Student, User
  }

  private Type userType;


  protected Tutor tutor;
  protected Instant requestTime;
  protected int requests;

  public User(Tutor tutor){
    requests = Util.getRandomInt(1, 5);
    this.tutor = tutor;
    this.userType = Type.User;
  }

  @Override
  public void run() {
    for(int i = 0; i < requests; i++){
      tutor.request(this);
      Util.threadRandomSleep();
      tutor.free(this);
      Util.threadRandomSleep();
    }
  }

  public Type getUserType(){
    return userType;
  }

  public Instant getRequestTime(){
    return requestTime;
  }

  public void setUserType(Type userType) {
    this.userType = userType;
  }


}
