import java.util.HashMap;

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

    public boolean compareArt(Articolo a) {
        return a.getTipo() == tipo && a.getPeso() == peso && a.getVolume() == volume;
    }

    public static int getValore(Articolo a) {
        return articoliValues.get(a.getTipo());
    }

    public String toString() {
        return tipo + ", " + peso + ", " + volume + ", (" + articoliValues.get(tipo) + ")";
    }
}
