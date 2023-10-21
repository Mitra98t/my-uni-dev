import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class Worker implements Runnable {
  private FileWork file;
  private Handler handler;
  private FileOutputStream fos;
  private ZipOutputStream zipOut;

  public Worker(Handler handler) {
    this.handler = handler;
  }

  @Override
  public void run() {
    try {
      handler.consumeFile(this);
      System.out.println("Consumed: " + file);
      if (file == null) {
        return;
      }
      zipDirFile(file);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public void setFile(FileWork file) {
    this.file = file;
  }

  public void zipDirFile(FileWork f) {
    // zip the file
    try {
      File targetFile = new File(f.path, f.file.getName() + ".zip");
      this.fos = new FileOutputStream(targetFile);
      this.zipOut = new ZipOutputStream(fos);

      zipFile(f.file, f.file.getName(), this.zipOut);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  private void zipFile(File fileToZip, String fileName, ZipOutputStream zipOut) throws IOException {
    System.out.println("Zipping " + fileName);
    FileInputStream fis = new FileInputStream(fileToZip);
    ZipEntry zipEntry = new ZipEntry(fileName);
    zipOut.putNextEntry(zipEntry);

    byte[] bytes = new byte[1024];
    int length;
    while ((length = fis.read(bytes)) >= 0) {
      zipOut.write(bytes, 0, length);
    }
    zipOut.close();
    fis.close();
    fos.close();
  }

}
