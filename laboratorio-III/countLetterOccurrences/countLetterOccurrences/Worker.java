public class Worker implements Runnable{

  private MyFile file;
  private Handler handler;

  public Worker(MyFile file, Handler handler) {
    this.file = file;
    this.handler = handler;
  }

  @Override
  public void run() {
    System.out.println("Worker running on file " + file.toString());
    char[] chars = file.getCharArray();
    for (char c : chars) {
      handler.addChar(c);
    }
  }
  
}
