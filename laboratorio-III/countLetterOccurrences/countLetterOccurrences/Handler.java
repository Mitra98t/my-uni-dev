import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class Handler {
  private ExecutorService executor = Executors.newFixedThreadPool(10);
  private BlockingQueue<MyFile> fileQueue = new LinkedBlockingQueue<MyFile>();

  public Handler(List<MyFile> fileList) {
    for (MyFile file : fileList) {
      fileQueue.add(file);
    }
  }
  
  public void handleRequest() {
    try {
      while (fileQueue.size() > 0) {
        executor.execute(new Worker(fileQueue.take()));
      }

      executor.shutdown();

      if (executor.isTerminated()) {
        System.out.println("All tasks finished");
      }
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }


}
