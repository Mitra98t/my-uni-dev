import java.io.File;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws Exception {
        ArrayList<MyFile> fileList = new ArrayList<>();
        for (String filePath : args) {
            File file = new File(filePath);
            if (file.exists() && file.isFile()) {
                fileList.add(new MyFile(file));
            }
        }

        Handler handler = new Handler(fileList);
        handler.handleRequest();
    }
}
