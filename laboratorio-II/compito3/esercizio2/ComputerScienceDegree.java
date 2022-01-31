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

    public void addStudent(Student s) {
        students.add(s);
    }

    public void load(String filename) throws IOException {
        try (BufferedReader bf = new BufferedReader(new FileReader(filename))) {
            String riga = "";
            String[] values;
            String[] votiScr;
            Student s;
            AbstractExam esame;
            while ((riga = bf.readLine()) != null) {
                values = riga.split(",");
                s = new Student(values[1], Integer.parseInt(values[0].trim()));
                for (int i = 2; i < values.length; i += 4) {
                    votiScr = values[i + 3].split(";");
                    if (votiScr.length > 1) {
                        esame = new ContinuousEvaluationExam(values[i], Integer.parseInt(values[i + 1].trim()));
                        esame.setOralGrade(Integer.parseInt(values[i + 2].trim()));
                        for (String string : votiScr) {
                            ((ContinuousEvaluationExam) esame)
                                    .addContinuousEvaluationGrade(Integer.parseInt(string.trim()));
                        }
                    } else {
                        esame = new WrittenAndOralExam(values[i], Integer.parseInt(values[i + 1].trim()));
                        esame.setOralGrade(Integer.parseInt(values[i + 2].trim()));
                        ((WrittenAndOralExam) esame).setWrittenGrade(Integer.parseInt(values[i + 3].trim()));
                    }
                    s.addExam(esame);
                }
                addStudent(s);
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw new IOException();
        }
    }

    public int getYearlyStudents(int year) throws IllegalArgumentException {
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

    public Student getTopStudentPerYear(int year) throws IllegalArgumentException {
        if (year > 0 && year < 4) {
            Student bestS = null;
            if (students.size() > 0) {
                for (Student student : students) {
                    if (student.getYear() == year)
                        bestS = student;
                }
                if (bestS != null)
                    for (int i = 0; i < students.size() - 1; i++) {
                        if (bestS.compareTo(students.get(i)) == 0) {
                            if (bestS.getStudentNumber() < students.get(i).getStudentNumber())
                                bestS = students.get(i);
                        } else if (bestS.compareTo(students.get(i)) < 0)
                            bestS = students.get(i);
                    }
            }
            return bestS;
        } else {
            throw new IllegalArgumentException();
        }
    }

}
