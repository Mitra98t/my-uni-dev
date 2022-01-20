import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Comparator;

public class Magazzino {
    private List<List<Articolo>> quantita;

    Magazzino() {
        quantita = new ArrayList<>();
    }

    int aggiungi(Articolo a, int q) {
        for (int i = 0; i < quantita.size(); i++) {
            if (!quantita.get(i).isEmpty() && quantita.get(i).get(0).compareArt(a)) {
                for (int j = 0; j < q; j++)
                    quantita.get(i).add(a);
                return quantita.get(i).size();
            }

        }

        List<Articolo> temp = new ArrayList<>();
        for (int i = 0; i < q; i++)
            temp.add(a);
        quantita.add(temp);
        return temp.size();
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
        for (List<Articolo> list : quantita) {
            if (!list.isEmpty() && list.get(0).compareArt(a))
                return true;

        }
        return false;
    }

    int prendi1(Articolo a) throws OutOfStock {
        for (int i = 0; i < quantita.size(); i++) {
            if (!quantita.get(i).isEmpty() && quantita.get(i).get(0).compareArt(a)) {
                if (quantita.get(i).size() == 1) {
                    quantita.remove(i);
                    return 0;
                } else {
                    quantita.get(i).remove(quantita.size() - 1);
                    return quantita.get(i).size();
                }
            }
        }
        throw new OutOfStock();
    }

    int volume_tot() {
        int totalVolume = 0;
        for (int i = 0; i < quantita.size(); i++)
            if (!quantita.get(i).isEmpty())
                totalVolume += quantita.get(i).get(0).getVolume() * quantita.get(i).size();

        return totalVolume;
    }

    List<Articolo> disponibili() {
        List<Articolo> res = new ArrayList<>();
        for (List<Articolo> list : quantita) {
            if (!list.isEmpty())
                res.add(new Articolo(list.get(0).getTipo(), list.get(0).getPeso(), list.get(0).getVolume()));
        }
        res.sort(artComparator);
        return res;
    }

    public static Comparator<Articolo> artComparator = new Comparator<Articolo>() {
        public int compare(Articolo a1, Articolo a2) {
            int res = a1.getTipo().compareTo(a2.getTipo());
            if (res > 0) {
                return 1;
            } else if (res < 0) {
                return -1;
            } else {
                if (a1.getPeso() > a2.getPeso()) {
                    return 1;
                } else if (a1.getPeso() < a2.getPeso()) {
                    return -1;
                } else {
                    if (a1.getVolume() > a2.getVolume()) {
                        return 1;
                    } else if (a1.getVolume() < a2.getVolume()) {
                        return -1;
                    } else {
                        return 0;
                    }
                }

            }
        }
    };

    static String getArticleName(Articolo a) {
        return a.getTipo() + "," + a.getPeso() + "," + a.getVolume();
    }
}
