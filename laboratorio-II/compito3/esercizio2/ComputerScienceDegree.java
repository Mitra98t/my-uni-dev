import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ComputerScienceDegree {
    private List<Student> students;

    public ComputerScienceDegree() {
        students = new ArrayList<>();
    }

    void addStudent(Student s) {
        students.add(s);
    }

    void load(String filename) throws IOException {
        try (BufferedReader bf = new BufferedReader(new FileReader(filename))) {
            String riga = bf.readLine();
            while (riga != null) {
                System.out.println(riga);
                riga = bf.readLine();
            }

            // while (riga != null) {
            //     System.out.println(riga);
            //     String[] values = riga.split(",");
            //     Student toAdd = new Student(values[1], Integer.parseInt(values[0]));
            //     System.out.println("RIGA nome: " + values[1]);
            //     if (values.length > 2) {
            //         for (int i = 2; i < values.length; i += 4) {
            //             String[] votiScritti = values[i + 3].split(";");
            //             if (votiScritti.length > 1) {
            //                 ContinuousEvaluationExam exam = new ContinuousEvaluationExam(values[i],
            //                         Integer.parseInt(values[i + 1]));
            //                 exam.setOralGrade(Integer.parseInt(values[i + 2]));
            //                 for (String string : votiScritti) {
            //                     exam.addContinuousEvaluationGrade(Integer.parseInt(string));
            //                 }
            //                 toAdd.addExam(exam);
            //             } else {
            //                 WrittenAndOralExam exam = new WrittenAndOralExam(values[i],
            //                         Integer.parseInt(values[i + 1]));
            //                 exam.setOralGrade(Integer.parseInt(values[i + 2]));
            //                 exam.setWrittenGrade(Integer.parseInt(values[i + 3]));
            //                 toAdd.addExam(exam);
            //             }
            //         }
            //     }
            //     System.out.println(toAdd);
            //     addStudent(toAdd);
            //     riga = bf.readLine();
            // }
        } catch (Exception e) {
            throw new IOException();
        }
    }

    int getYearlyStudents(int year) throws IllegalArgumentException {
        if (year > 0 && year < 4) {
            int res = 0;
            for (Student student : students) {
                res += student.getYear() == year ? 1 : 0;
            }
            return res;
        } else {
            throw new IllegalArgumentException();
        }
    }

    Student getTopStudentPerYear(int year) throws IllegalArgumentException {
        if (year > 0 && year < 4) {
            Student bestS = null;
            if (students.size() > 0)
                for (int i = 0; i < students.size() - 1; i++) {
                    if (students.get(i).compareTo(students.get(i + 1)) == 0) {
                        if (students.get(i).getStudentNumber() > students.get(i + 1).getStudentNumber())
                            bestS = students.get(i);
                        else
                            bestS = students.get(i + 1);
                    }
                    bestS = students.get(i).compareTo(students.get(i + 1)) < 0 ? students.get(i + 1) : students.get(i);
                }
            return bestS;
        } else {
            throw new IllegalArgumentException();
        }
    }

    @Override
    public String toString() {
        String res = "";
        for (Student student : students) {
            res += "S name: " + student.getName() + "\n";
            res += "S matr: " + student.getStudentNumber() + "\n";
            for (AbstractExam exam : student.getExams()) {
                if (exam instanceof WrittenAndOralExam w) {
                    res += "wo name: " + w.getExamName() + "\n";
                    res += "wo Wgra: " + w.getWrittenGrade() + "\n";
                    res += "wo Ogra: " + w.getOralGrade() + "\n";
                    res += "credit: " + w.getCredits() + "\n";
                } else if (exam instanceof ContinuousEvaluationExam w) {
                    res += "co name: " + w.getExamName() + "\n";
                    for (Integer grades : w.getContinuousEvaluationGrades()) {
                        res += "co Cgra: " + grades + "\n";
                    }
                    res += "co Ogra: " + w.getOralGrade() + "\n";
                    res += "credit: " + w.getCredits() + "\n";
                }
            }
            res += "\n";
        }
        return res;
    }
}
