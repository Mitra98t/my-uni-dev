import java.io.File;

public class FileWork {
  public File file;
  public String path;

  public FileWork(String path) {
    this.file = new File(path);
    this.path = file.getParentFile().getPath();
  }

  @Override
  public String toString() {
    return this.path;
  }
}
