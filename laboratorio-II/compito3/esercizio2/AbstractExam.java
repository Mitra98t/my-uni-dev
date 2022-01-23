public abstract class AbstractExam implements IExam {
    private int credits;
    private String examName;
    private int oralGrade;

    public AbstractExam(String esameName, int nCFU) {
        examName = esameName;
        credits = nCFU;
    }

    public int getCredits() {
        return credits;
    }

    public String getExamName() {
        return examName;
    }

    public int getOralGrade() {
        return oralGrade;
    }

    public void setOralGrade(int oralGrade) throws IllegalArgumentException {
        if (oralGrade >= 0 && oralGrade <= 30)
            this.oralGrade = oralGrade;
        else
            throw new IllegalArgumentException();
    }

}
