import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class FileHandler {
    private String filename = "";
    private BufferedReader buffer;

    public FileHandler(String fn) throws FileNotFoundException {
        filename = fn;
        buffer = new BufferedReader(new FileReader(filename));
    }

    public boolean contains(String word) throws IOException {
        String line = "";
        while ((line = buffer.readLine()) != null) {
            if (line.contains(word))
                return true;
        }
        return false;
    }
}
