/**
 * main
 */
public class main {
    public static void main(String[] args) {
        ComputerScienceDegree cs = new ComputerScienceDegree();

        try {
            cs.load("./students.csv");
        } catch (Exception e) {
            // TODO: handle exception
        }

        System.out.println(cs.getTopStudentPerYear(1));
        System.out.println(cs.getTopStudentPerYear(2));
        System.out.println(cs.getTopStudentPerYear(3));
        
        // System.out.println(cs.toString());
    }
}