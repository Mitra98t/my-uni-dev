import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class HandlerThreads {
  private ExecutorService executorService;

  public HandlerThreads() {
    // Initialize executor service with 4-6 threads
    executorService = new ThreadPoolExecutor(4, 6, 500, TimeUnit.MILLISECONDS, new LinkedBlockingQueue<Runnable>());
  }

  public void handle(String line) {
    executorService.submit(new Runnable() {
      @Override
      public void run() {
        String[] parts = line.split(" - - ");

        // Convert IP address to host name
        String hostName = "";
        try {
          InetAddress address = InetAddress.getByName(parts[0]);
          hostName = address.getHostName();
        } catch (UnknownHostException e) {
          e.printStackTrace();
        }

        System.out.println(hostName + " - - " + parts[1]);
      }
    });
  }
}
