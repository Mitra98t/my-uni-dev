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

  public void sendClearScreen() {
    out.print("\033[H\033[2J");
    out.flush();
  }

  public void send(String message) {
    out.println(message);
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
        String lineInput = in.readLine();
        try {
          selection = Integer.parseInt(lineInput);
        } catch (Exception e) {
          out.println("Invalid selection, please try again.");
          continue;
        }
        if (!lineInput.equals("") && selection > 0 && selection <= options.length) {
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
    try {
      String lineInput = "";
      do {
        out.println(this.colorizeString(message, Colors.CYAN));
        out.println("prompt-now");
        lineInput = in.readLine();
        if (lineInput.equals("")) {
          out.println("Invalid input, please try again.");
        }
      } while (lineInput.equals(""));
      return lineInput;
    } catch (Exception e) {
      System.out.println(e);
      return null;
    }
  }

  public String passwordPrompt(String message) {
    try {
      String lineInput = "";
      do {
        out.println(this.colorizeString(message, Colors.CYAN));
        out.println("password-now");
        lineInput = in.readLine();
        if (lineInput.equals("")) {
          out.println("Invalid input, please try again.");
        }
      } while (lineInput.equals(""));
      return lineInput;
    } catch (Exception e) {
      System.out.println(e);
      return null;
    }
  }

  public double voting(String message) {
    boolean valid = false;
    double vote = 0;
    try {
      while (!valid) {
        out.println(message);
        out.println(this.colorizeString("Please vote from 1 to 5:", Colors.CYAN));
        out.println("vote-now");
        String lineInput = in.readLine();
        try {
          vote = Double.parseDouble(lineInput);
        } catch (Exception e) {
          out.println("Invalid selection, please try again.");
          continue;
        }
        if (vote > 0 && vote <= 5) {
          valid = true;
        } else {
          out.println("Invalid selection, please try again.");
        }
      }
      return vote;
    } catch (Exception e) {
      System.out.println(e);
      return 1;
    }
  }

  public void pause() {
    out.println(this.colorizeString("Press enter to continue...", Colors.CYAN));
    out.println("pause-now");
    try {
      in.readLine();
    } catch (Exception e) {
      System.out.println(e);
    }
  }

  public String colorizeString(String message, Colors color) {
    return color.getCode() + message + Colors.RESET.getCode();
  }

}
