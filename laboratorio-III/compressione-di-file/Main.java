import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.BlockingDeque;
import java.util.concurrent.BlockingQueue;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class Main {
  public static void main(String[] args) {

    List<FileWork> directories = new ArrayList<>();
    for (String arg : args) {
      File file = new File(arg);
      if (file.isDirectory()) {
        for (File f : file.listFiles()) {
          directories.add(new FileWork(f.getAbsolutePath()));
        }
      }
    }
    

    Handler handler = new Handler(directories);
    
    handler.workerQueueHandler();

  }
}

