import java.io.BufferedReader;
import java.io.PrintWriter;

enum Colors {
  RED("\033[0;31m"),
  GREEN("\033[0;32m"),
  YELLOW("\033[0;33m"),
  BLUE("\033[0;34m"),
  PURPLE("\033[0;35m"),
  CYAN("\033[0;36m"),
  WHITE("\033[0;37m"),
  RESET("\033[0m");

  private String code;

  Colors(String code) {
    this.code = code;
  }

  public String getCode() {
    return code;
  }
}

public class CliHandlerServer {
  private PrintWriter out;
  private BufferedReader in;

  public CliHandlerServer(PrintWriter out, BufferedReader in) {
    this.out = out;
    this.in = in;
  }

  public void clearScreen() {
    out.print("\033[H\033[2J");
    out.flush();
  }

  public int selection(String[] options) {
    try {
      int selection = 0;
      boolean valid = false;
      while (!valid) {
        out.println("Please select an option:");
        for (int i = 0; i < options.length; i++) {
          out.println(this.colorizeString(i + 1 + "", Colors.CYAN) + ". " + options[i]);
        }
        out.println("select-now");
        selection = Integer.parseInt(in.readLine());
        if (selection > 0 && selection <= options.length) {
          valid = true;
        } else {
          out.println("Invalid selection, please try again.");
        }
      }
      return selection - 1;
    } catch (Exception e) {
      System.out.println(e);
      return 0;
    }
  }

  public String prompt(String message) {
    System.out.println(this.colorizeString(message, Colors.CYAN));
    System.out.println("Please respond:");
    return System.console().readLine();
  }

  public void pause() {
    System.out.println(this.colorizeString("Press enter to continue...", Colors.CYAN));
    System.console().readLine();
  }

  public String colorizeString(String message, Colors color) {
    return color.getCode() + message + Colors.RESET.getCode();
  }

}
