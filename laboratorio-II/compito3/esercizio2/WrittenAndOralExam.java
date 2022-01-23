public class WrittenAndOralExam extends AbstractExam {
    private int writtenGrade;

    public WrittenAndOralExam(String esameName, int nCFU) {
        super(esameName, nCFU);
        super.setOralGrade(0);
    }

    public int getWrittenGrade() {
        return writtenGrade;
    }

    public void setWrittenGrade(int writtenGrade) throws IllegalArgumentException {
        if (writtenGrade >= 0 && writtenGrade <= 30)
            this.writtenGrade = writtenGrade;
        else
            throw new IllegalArgumentException();
    }

    @Override
    public int getGrade() {
        double exp = (double) (writtenGrade + super.getOralGrade()) / 2;
        return (int) Math.round(exp);
    }
}