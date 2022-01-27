import java.io.IOException;

/**
 * main
 */
public class main {
    public static void main(String[] args) {
        ComputerScienceDegree cs = new ComputerScienceDegree();
        try {
            cs.load("./students.csv");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        System.out.println(cs);
    }
}