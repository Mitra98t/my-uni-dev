import java.io.File;
import java.nio.file.Files;

public class MyFile {
  private File file;

  public MyFile(File file) {
    this.file = file;
  }

  public char[] getCharArray() {
    try {
      String content = new String(Files.readAllBytes(file.toPath()));
      char[] chars = content.toCharArray();
      return chars;
    } catch (Exception e) {
      e.printStackTrace();
      return null;
    }
  }

  public String toString() {
    return file.getName();
  }

}
