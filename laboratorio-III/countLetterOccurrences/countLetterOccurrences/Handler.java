import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class Handler {
  private ExecutorService executor = Executors.newFixedThreadPool(10);
  private BlockingQueue<MyFile> fileQueue = new LinkedBlockingQueue<MyFile>();
  private ConcurrentHashMap<String, Integer> map = new ConcurrentHashMap<String, Integer>();
  public Handler(List<MyFile> fileList) {
    for (MyFile file : fileList) {
      fileQueue.add(file);
    }
  }
  
  public void handleRequest() {
    try {
      while (fileQueue.size() > 0) {
        executor.execute(new Worker(fileQueue.take(), this));
      }

      executor.shutdown();
      while (!executor.isTerminated()) {
      }
      if (executor.isTerminated()) {
        System.out.println("Char count: " + map.toString());
        System.out.println("All tasks finished");
      }
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }

  public synchronized void addChar(char c) {
    String key = String.valueOf(c);
    if (map.containsKey(key)) {
      map.put(key, map.get(key) + 1);
    } else {
      map.put(key, 1);
    }
  }


}
