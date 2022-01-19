import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Comparator;

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
        try (BufferedReader bf = new BufferedReader(new FileReader(filename))) {
            String riga = bf.readLine();
            while (riga != null) {
                String[] values = riga.split(",");
                Articolo toAdd = new Articolo(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
                aggiungi(toAdd, Integer.parseInt(values[3]));
                riga = bf.readLine();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
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

    List<Articolo> disponibili() {
        List<Articolo> res = new ArrayList<>();
        for (Map.Entry<String, Integer> set : quantita.entrySet()) {
            if (set.getValue() > 0) {
                String[] values = set.getKey().split(",");
                Articolo toAdd = new Articolo(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
                res.add(toAdd);
            }
        }
        res.sort(artComparator);
        return res;
    }

    public static Comparator<Articolo> artComparator = new Comparator<Articolo>() {

        public int compare(Articolo s1, Articolo s2) {
            return getArticleName(s1).compareTo(getArticleName(s2));
        }
    };

    static String getArticleName(Articolo a) {
        return a.getTipo() + "," + a.getPeso() + "," + a.getVolume();
    }
}
