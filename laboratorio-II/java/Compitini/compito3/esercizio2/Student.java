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
        int index = -1;
        for (int i = 0; i < exams.size(); i++) {
            if (exams.get(i).getExamName().equals(examA.getExamName()))
                index = i;
        }
        if (index == -1)
            exams.add(examA);
        else
            exams.set(index, examA);
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
                cfuSum += abstractExam.getCredits();
                votSum += abstractExam.getGrade() * abstractExam.getCredits();
            }
        }

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
