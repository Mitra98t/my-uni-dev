public interface ModString{
    /**
     returns string dimenson

     @return string dimension
     */
    public int size();

    /**
     Cambia carattere nella stringa

     @param c carattere nuovo
     @param num posizione del carattere da cambiare (>= 0 e < size)
     @throws IndexOutOfBoundException se num non rispetta vincoli
     */
    public void update(char c, int num) throws IndexOutOfBoundsException;

    /**
     rimuove carattere alla posizione data

     @param num posizione del carattere da cambiare (>= 0 e < size)
     @throws IndexOutOfBoundException se num non rispetta vincoli
     */
    public void remove(int num) throws IndexOutOfBoundsException;
}