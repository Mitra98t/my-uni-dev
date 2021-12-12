import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * main
 */
public class main {
    public static void main(String[] args) {
        FileHandler file;
        BufferedReader sin = new BufferedReader(new InputStreamReader(System.in));
        String word = "";
        System.out.print("parola da cercare: ");
        
        try {
            file = new FileHandler("./test.txt");
            word = sin.readLine();
            System.out.println(file.contains(word) ? ("Il file contiene la parola " + word) : ("Il file non contiene la parola " + word));
        } catch (Exception e) {
            System.out.println(e);
        }
        
    }
}