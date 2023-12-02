import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ServerCycle implements Runnable {
  private Socket clientSocket;
  private PrintWriter out;
  private BufferedReader in;

  public ServerCycle(Socket socket) {
    this.clientSocket = socket;
  }

  @Override
  public void run() {
    try {
      out = new PrintWriter(clientSocket.getOutputStream(), true);
      in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
      CliHandlerServer cliHandler = new CliHandlerServer(out, in);

      // usage loop
      cliHandler.clearScreen();
      String[] options = { "Start Game", "Exit" };
      int selection = cliHandler.selection(options);
      

      in.close();
      out.close();
      clientSocket.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
