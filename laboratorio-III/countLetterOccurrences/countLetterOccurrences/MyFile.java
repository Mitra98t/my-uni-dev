import java.io.File;
import java.nio.file.Files;

public class MyFile {
  private File file;

  public MyFile(File file) {
    this.file = file;
  }

  public void printContent() {
    try {
      String content = new String(Files.readAllBytes(file.toPath()));
      System.out.println("File content: \n" + content);
      char[] chars = content.toCharArray();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
