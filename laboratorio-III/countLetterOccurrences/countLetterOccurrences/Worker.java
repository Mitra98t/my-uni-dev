public class Worker implements Runnable{

  private MyFile file;

  public Worker(MyFile file) {
    this.file = file;
  }

  @Override
  public void run() {
    file.printContent();
    System.out.println("Worker running");
  }
  
}
