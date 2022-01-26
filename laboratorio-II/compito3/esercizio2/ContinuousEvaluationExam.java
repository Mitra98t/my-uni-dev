import java.util.ArrayList;
import java.util.List;

public class ContinuousEvaluationExam extends AbstractExam {
    private List<Integer> continuousEvaluationGrades;

    public ContinuousEvaluationExam(String esameName, int nCFU) {
        super(esameName, nCFU);
        continuousEvaluationGrades = new ArrayList<>();
    }

    // TODO: rimuovere questo metodo
    public List<Integer> getContinuousEvaluationGrades() {
        return continuousEvaluationGrades;
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
        int mediaItinere = (int) Math.round((double) sum / continuousEvaluationGrades.size());
        return (int) Math.round(((double) (mediaItinere + super.getOralGrade())) / 2);
    }
}
