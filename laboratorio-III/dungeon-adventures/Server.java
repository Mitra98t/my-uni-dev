import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server {
  public static void main(String[] args) {
    try (ServerSocket server = new ServerSocket(6666)) {
      System.out.println("Server started");
      while (true) {
        Socket socket = server.accept();
        
        Thread thread = new Thread(new ServerHandler(socket));
        thread.start();
      }
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}
