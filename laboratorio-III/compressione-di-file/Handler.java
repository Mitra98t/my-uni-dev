import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class Handler {
  private BlockingQueue<FileWork> files = new LinkedBlockingQueue<>(10);
  private ExecutorService executorService = Executors.newFixedThreadPool(3);

  public Handler(List<FileWork> directories) {
    for (FileWork directory : directories) {
      this.files.add(directory);
    }
  }

  public synchronized void consumeFile(Worker w) {
    if (files.size() == 0) {
      return;
    }
    try {
      w.setFile(files.take());
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public void workerQueueHandler() {
    try {
      while (files.size() > 0) {
        executorService.submit(new Worker(this));
      }
      executorService.shutdown();
      while (!executorService.isTerminated()) {
      }
      System.out.println("Finished all threads");
    } catch (Exception e) {
      // TODO: handle exception
    }
  }
}
