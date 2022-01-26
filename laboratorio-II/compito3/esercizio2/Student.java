import java.util.ArrayList;
import java.util.List;

public class Student {
    private String name;
    private int studentNumber;
    private List<AbstractExam> exams;

    public Student(String nome, int mat) {
        name = nome;
        studentNumber = mat;
        exams = new ArrayList<>();
    }

    public List<AbstractExam> getExams() {
        return exams;
    }

    public String getName() {
        return name;
    }

    public int getStudentNumber() {
        return studentNumber;
    }

    public void addExam(AbstractExam examA) {
        for (AbstractExam abstractExam : exams) {
            if (abstractExam.getExamName().equals(examA.getExamName())) {
                exams.remove(abstractExam);
            }
        }
        exams.add(examA);
    }

    public int getYear() {
        int sum = 0;
        for (AbstractExam abstractExam : exams) {
            if (abstractExam.getGrade() >= 18) {
                sum += abstractExam.getCredits();
            }
        }

        if (sum < 60)
            return 1;
        else if (sum < 120)
            return 2;
        else
            return 3;
    }

    public double getECTSAverage() {
        int cfuSum = 0;
        int votSum = 0;
        for (AbstractExam abstractExam : exams) {
            if (abstractExam.getGrade() > 17) {
                System.out.println("Credits: " + abstractExam.getCredits());
                System.out.println("Grade: " + abstractExam.getGrade());
                cfuSum += abstractExam.getCredits();
                votSum += abstractExam.getGrade() * abstractExam.getCredits();
            }
        }

        System.out.println("cfuSum: " + cfuSum);
        System.out.println("votSum: " + votSum);

        if (cfuSum == 0)
            return 0;
        return ((double) votSum / cfuSum);

        // return (((double) votSum) / cfuSum);
    }

    public int compareTo(Student s) {
        return getECTSAverage() - s.getECTSAverage() < 0 ? -1 : getECTSAverage() - s.getECTSAverage() > 0 ? 1 : 0;
    }

    @Override
    public String toString() {
        return name + " " + studentNumber;
    }
}
