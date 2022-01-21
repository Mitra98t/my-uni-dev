import java.util.ArrayList;
import java.util.List;

public class ContinuousEvaluationExam extends AbstractExam {
    private List<Integer> continuousEvaluationGrades;

    public ContinuousEvaluationExam(String esameName, int nCFU) {
        super(esameName, nCFU);
        continuousEvaluationGrades = new ArrayList<>();
    }

    void addContinuousEvaluationGrade(int g) throws IllegalArgumentException {
        if (g >= 0 && g <= 30)
            continuousEvaluationGrades.add(g);
        else
            throw new IllegalArgumentException();
    }

    @Override
    public int getGrade() {
        int sum = 0;
        for (Integer integer : continuousEvaluationGrades) {
            sum += integer;
        }

        sum += super.getOralGrade();
        return sum / (continuousEvaluationGrades.size() + 1);
    }
}
