import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Classe Magazzino
 * Uso HashMap per gestire la quantità di un articolo contenuto nel magazzino.
 */
public class Magazzino {
    private HashMap<Articolo, Integer> quantita;

    public Magazzino() {
        quantita = new HashMap<Articolo, Integer>();
    }

    public int aggiungi(Articolo a, int q) {
        int oldQ = 0;

        if (quantita.containsKey(a))
            oldQ = quantita.get(a);

        quantita.put(a, oldQ + q);
        return oldQ + q;
    }

    public void rifornisci(String filename) {
        try (BufferedReader bf = new BufferedReader(new FileReader(filename))) {
            String riga;
            while ((riga = bf.readLine()) != null) {
                String[] values = riga.split(",");
                Articolo toAdd = new Articolo(values[0], Integer.parseInt(values[1]), Integer.parseInt(values[2]));
                if (Integer.parseInt(values[3]) > 0) {
                    aggiungi(toAdd, Integer.parseInt(values[3]));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public boolean disponibile(Articolo a) {
        return quantita.containsKey(a) && quantita.get(a) >= 1;
    }

    public int prendi1(Articolo a) throws OutOfStock {
        if (quantita.containsKey(a)) {
            int oldQ = 0;
            oldQ = quantita.get(a);
            if (oldQ - 1 == 0)
                quantita.remove(a);
            else
                quantita.put(a, oldQ - 1);
            return oldQ - 1;
        }
        throw new OutOfStock();
    }

    public int volume_tot() {
        int totalVolume = 0;
        for (Map.Entry<Articolo, Integer> set : quantita.entrySet()) {
            totalVolume += set.getValue() * set.getKey().getVolume();
        }
        return totalVolume;
    }

    public List<Articolo> disponibili() {
        List<Articolo> res = new ArrayList<>();
        for (Map.Entry<Articolo, Integer> set : quantita.entrySet()) {
            if (set.getValue() > 0) {
                res.add(new Articolo(set.getKey().getTipo(), set.getKey().getPeso(), set.getKey().getVolume()));
            }
        }
        res.sort((Articolo a1, Articolo a2) -> {
            if (a1.getTipo().compareTo(a2.getTipo()) != 0)
                return a1.getTipo().compareTo(a2.getTipo());
            else if (a1.getPeso() - a2.getPeso() != 0)
                return a1.getPeso() - a2.getPeso();
            else
                return a1.getVolume() - a2.getVolume();
        });
        return res;
    }

    public String toString() {
        String res = "";
        for (Map.Entry<Articolo, Integer> set : quantita.entrySet()) {
            res += set.getKey() + " quantità: ";
            res += set.getValue() + "\n";
        }
        return res;
    }

}