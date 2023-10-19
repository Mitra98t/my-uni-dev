public class Computer {
  private static int computerId = 1;
  private final int id;
  public int getId() {
    return id;
  }

  private boolean inUse;
  private String user;

  public String getUser() {
    return user;
  }

  private static void incrementComputerId() {
    Computer.computerId++;
  }

  public boolean isInUse() {
    return this.inUse;
  }

  private void setUser(String user) {
    this.user = user;
  }

  public Computer() {
    this.inUse = false;
    this.user = "N/A";
    this.id = Computer.computerId;
    Computer.incrementComputerId();
  }

  public void occupy(String user) {
    this.inUse = true;
    this.setUser(user);
    System.out.println("Computer " + getId() + " is now in use by " + this.user);
  }

  public void free() {
    this.inUse = false;
    this.setUser("N/A");
    System.out.println("Computer " + getId() + " is now free");
  }
}
