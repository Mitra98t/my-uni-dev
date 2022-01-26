/**
 * main
 */
public class main {
    public static void main(String[] args) {
        ContinuousEvaluationExam esame = new ContinuousEvaluationExam("ciao", 6);

        esame.setOralGrade(19);
        esame.addContinuousEvaluationGrade(19);
        esame.addContinuousEvaluationGrade(19);
        esame.addContinuousEvaluationGrade(19);

        System.out.println("Voto primo esame: " + esame.getGrade());

        WrittenAndOralExam esame2 = new WrittenAndOralExam("ciao2", 6);

        esame2.setOralGrade(15);
        esame2.setWrittenGrade(15);

        System.out.println("Voto secondo esame: " + esame2.getGrade());

        WrittenAndOralExam esame3 = new WrittenAndOralExam("ciao3", 12);

        esame3.setOralGrade(30);
        esame3.setWrittenGrade(30);

        System.out.println("Voto terzo esame: " + esame3.getGrade());

        Student s = new Student("luca", 2);

        s.addExam(esame);
        s.addExam(esame2);
        s.addExam(esame3);

        System.out.println("Media pesata calcolata su esami precedenti: " + s.getECTSAverage());

    }
}