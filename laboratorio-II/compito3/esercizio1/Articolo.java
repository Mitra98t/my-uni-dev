import java.util.HashMap;
import java.util.Objects;

/**
 * Uso HashMap staticamente assicurandomi che venga instanziata una volta sola per legare il tipo al valore 
 */
public class Articolo {
    private String tipo;
    private int peso;
    private int volume;

    private static HashMap<String, Integer> articoliValues;

    /**
     * Crea un articolo
     * Mette la value di default a 1 se il tipo manca nella lista
     * 
     * @param t Tipo dell'articolo
     * @param p Peso dell'articolo
     * @param v Volume dell'articolo
     */
    Articolo(String t, int p, int v) {
        tipo = t;
        peso = p;
        volume = v;

        if (articoliValues == null)
            articoliValues = new HashMap<String, Integer>();

        articoliValues.putIfAbsent(t, 1);
    }

    /**
     * Assegna (sostituendo se già presente) il valore nella hashmap
     * 
     * @param tipo         tipo di cui settare il valore
     * @param nuovo_valore valore
     */
    static void assegna_valore(String tipo, int nuovo_valore) {
        if (articoliValues == null)
            articoliValues = new HashMap<String, Integer>();
        articoliValues.put(tipo, nuovo_valore);
    }

    /**
     * 
     * @return Tipo articolo
     */
    public String getTipo() {
        return tipo;
    }

    /**
     * 
     * @return Peso articolo
     */
    public int getPeso() {
        return peso;
    }

    /**
     * 
     * @return Volume articolo
     */
    public int getVolume() {
        return volume;
    }

    /**
     * 
     * @param a articolo di cui controllare il valore legato al tipo
     * @return Valore del tipo dell'articolo a
     */
    public static int getValore(Articolo a) {
        return articoliValues.get(a.getTipo());
    }

    public String toString() {
        return tipo + ", " + peso + ", " + volume + ", (" + articoliValues.get(tipo) + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Articolo)
            return equals((Articolo) o);

        return false;
    }

    public boolean equals(Articolo a) {
        return a.getTipo().compareTo(tipo) == 0 && a.getPeso() == peso && a.getVolume() == volume;
    }

    @Override
    public int hashCode() {
        return Objects.hash(tipo, peso, volume);
    }

}
