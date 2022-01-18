import java.util.HashMap;
import java.util.Map;

public class Magazzino {
    private HashMap<String, Integer> quantita;

    Magazzino() {
        quantita = new HashMap<String, Integer>();
    }

    int aggiungi(Articolo a, int q) {
        String key = getArticleName(a);
        int oldQ = 0;

        if (quantita.containsKey(key))
            oldQ = quantita.get(key);

        quantita.put(key, oldQ + q);
        return oldQ + q;
    }

    void rifornisci(String filename) {
    }

    boolean disponibile(Articolo a) {
        return quantita.containsKey(getArticleName(a))
                && quantita.get(getArticleName(a)) > 1;
    }

    int prendi1(Articolo a) throws OutOfStock {
        String key = getArticleName(a);
        if (quantita.containsKey(key)) {
            int oldQ = 0;
            oldQ = quantita.get(key);
            if (oldQ == 0)
                throw new OutOfStock();

            quantita.put(key, oldQ - 1);
            return oldQ - 1;
        }
        throw new OutOfStock();
    }

    int volume_tot() {
        int totalVolume = 0;
        for (Map.Entry<String, Integer> set : quantita.entrySet()) {
            totalVolume += set.getValue() * Integer.parseInt(
                    set.getKey().subSequence(set.getKey().lastIndexOf(','), set.getKey().length()).toString());
        }
        return totalVolume;
    }

    private String getArticleName(Articolo a) {
        return a.getTipo() + "," + a.getPeso() + "," + a.getVolume();
    }
}
