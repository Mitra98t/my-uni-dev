import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.InetAddress;

public class Main {
  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Usage: java Main <file_path>");
      return;
    }

    String filePath = args[0];
    try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
      String line;
      while ((line = br.readLine()) != null) {
        String[] parts = line.split(" - - ");

        // Convert IP address to host name
        String hostName = "";
        InetAddress address = InetAddress.getByName(parts[0]);
        hostName = address.getHostName();

        System.out.println(hostName + " - - " + parts[1]);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
    finally {
      System.out.println("\n\nDone");
    }
  }
}
