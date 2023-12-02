import java.io.*;
import java.net.Socket;

public class Client {
  public static void main(String[] args) throws IOException {
    Socket socket = new Socket("localhost", 6666);
    PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
    BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

    String userInput;
    while (true) {
      // clear screen
      String serverMessage = in.readLine();
      if (serverMessage.equals("player-choose-now")) {
        System.out.println("What do you want to do?");
        userInput = stdIn.readLine();
        out.println(userInput);
        System.out.print("\033[H\033[2J");
      } else if (serverMessage.equals("player-lost")) {
        System.out.println("You lost");
        break;
      } else {
        System.out.println(serverMessage);
      }
    }

    out.close();
    in.close();
    stdIn.close();
    socket.close();
  }
}