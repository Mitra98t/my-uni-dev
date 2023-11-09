import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {
  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Usage: java Main <file_path>");
      return;
    }
    HandlerThreads handler = new HandlerThreads();

    String filePath = args[0];
    try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
      String line;
      while ((line = br.readLine()) != null) {
        handler.handle(line);
      }
    } catch (IOException e) {
      e.printStackTrace();
    } finally {
      System.out.println("\n\nDone");
    }

  }
}
