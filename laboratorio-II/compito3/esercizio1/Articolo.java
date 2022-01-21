import java.util.HashMap;
import java.util.Objects;

public class Articolo {
    private String tipo;
    private int peso;
    private int volume;

    private static HashMap<String, Integer> articoliValues;

    Articolo(String t, int p, int v) {
        tipo = t;
        peso = p;
        volume = v;

        if (articoliValues == null)
            articoliValues = new HashMap<String, Integer>();

        articoliValues.putIfAbsent(t, 1);
    }

    static void assegna_valore(String tipo, int nuovo_valore) {
        if (articoliValues == null)
            articoliValues = new HashMap<String, Integer>();
        articoliValues.put(tipo, nuovo_valore);
    }

    public String getTipo() {
        return tipo;
    }

    public int getPeso() {
        return peso;
    }

    public int getVolume() {
        return volume;
    }

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
