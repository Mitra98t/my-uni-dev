import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class CliHandlerClient {
  private BufferedReader stdIn;
  private PrintWriter out;

  public CliHandlerClient(PrintWriter out) {
    this.stdIn = new BufferedReader(new InputStreamReader(System.in));
    this.out = out;
  }

  public void interpret(String message) {
    String userInput = "";
    if (message.equals("select-now")) {
      try {
        userInput = this.stdIn.readLine();
        this.out.println(userInput);
      } catch (Exception e) {
        System.out.println(e);
      }
    } else if (message.equals("vote-now")) {
      try {
        userInput = this.stdIn.readLine();
        this.out.println(userInput);
      } catch (Exception e) {
        System.out.println(e);
      }
    } else if (message.equals("prompt-now")) {
      try {
        userInput = this.stdIn.readLine();
        this.out.println(userInput);
      } catch (Exception e) {
        System.out.println(e);
      }
    } else if (message.equals("pause-now")) {
      try {
        userInput = this.stdIn.readLine();
        this.out.println("unpause-now");
      } catch (Exception e) {
        System.out.println(e);
      }
    } else if (message.equals("exit-now")) {
      System.out.println("\nServer closed connection.");
      // code
    } else {
      System.out.println(message);
    }
  }
}
