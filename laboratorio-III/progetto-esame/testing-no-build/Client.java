import java.io.*;
import java.net.Socket;

public class Client {
  public static void main(String[] args) throws IOException {
    Socket socket = new Socket("localhost", 6666);
    PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
    BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
    CliHandlerClient cliHandler = new CliHandlerClient(out);

    String serverMessage;
    do {
      serverMessage = in.readLine();
      cliHandler.interpret(serverMessage);
    } while (!serverMessage.equals("exit"));

    out.close();
    in.close();
    stdIn.close();
    socket.close();
  }
}