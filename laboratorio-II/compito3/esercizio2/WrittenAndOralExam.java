public class WrittenAndOralExam extends AbstractExam {
    private int writtenGrade;

    public WrittenAndOralExam(String esameName, int nCFU) {
        super(esameName, nCFU);
        super.setOralGrade(0);
    }

    public int getWrittenGrade() {
        return writtenGrade;
    }

    public void setWrittenGrade(int oralGrade) throws IllegalArgumentException {
        if (writtenGrade >= 0 && writtenGrade <= 30)
            this.writtenGrade = writtenGrade;
        else
            throw new IllegalArgumentException();
    }

    @Override
    public int getGrade() {
        return Math.round((writtenGrade+super.getOralGrade())/2);
    }
}

// getter e setter per writtenGrade. Il setter controlla che il voto sia tra 0 e
// 30 e lancia IllegalArgumentException se non è nell’intervallo giusto.