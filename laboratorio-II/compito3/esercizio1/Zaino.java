import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Zaino {
    private int maxP;
    private int maxV;
    private int curP;
    private int curV;
    private List<Articolo> contains;

    Zaino(int p, int v) {
        maxP = p;
        maxV = v;
        curP = 0;
        curV = 0;
        contains = new ArrayList<>();
    }

    boolean puo_contenere(Articolo a) {
        return maxP - curP >= a.getPeso() && maxV - curV >= a.getVolume();
    }

    void aggiungi(Articolo a) throws NoWay {
        if (puo_contenere(a)) {
            contains.add(a);
            curV += a.getVolume();
            curP += a.getPeso();
        } else
            throw new NoWay();
    }

    void svuota() {
        contains.clear();
    }

    int peso() {
        int res = 0;
        for (Articolo articolo : contains) {
            res += articolo.getPeso();
        }
        return res;
    }

    int volume() {
        int res = 0;
        for (Articolo articolo : contains) {
            res += articolo.getVolume();
        }
        return res;
    }

    int valore() {
        int res = 0;
        for (Articolo articolo : contains) {
            res += Articolo.getValore(articolo);
        }
        return res;
    }

    boolean contiene_tipo(String t) {
        for (Articolo articolo : contains) {
            if (articolo.getTipo().compareTo(t) == 0)
                return true;
        }
        return false;
    }

    void riempi(Magazzino m) {
        boolean alreadyThere = false;
        List<Articolo> items = m.disponibili();
        items.sort(artComparator);

        System.out.println("\nLISTA ORDINATA PER ZAINO\n");
        for (Articolo articolo : items) {
            System.out.println(articolo);
        }
        System.out.println("\nLISTA ORDINATA PER ZAINO\n");

        for (Articolo articolo : items) {
            for (Articolo articolo2 : contains) {
                if (articolo2.getTipo().compareTo(articolo.getTipo()) == 0) {
                    alreadyThere = true;
                }
            }
            if (puo_contenere(articolo) && !alreadyThere) {
                try {
                    aggiungi(articolo);
                    m.prendi1(articolo);
                } catch (Exception e) {
                    continue;
                }
            }
            alreadyThere = false;
        }
    }

    public static Comparator<Articolo> artComparator = new Comparator<Articolo>() {

        public int compare(Articolo s1, Articolo s2) {
            if (Articolo.getValore(s1) > Articolo.getValore(s2))
                return -1;
            else if (Articolo.getValore(s1) < Articolo.getValore(s2))
                return 1;
            else {
                if (s1.getPeso() > s2.getPeso())
                    return 1;
                else if (s1.getPeso() < s2.getPeso())
                    return -1;
                else {
                    if (s1.getVolume() > s2.getVolume())
                        return 1;
                    else if (s1.getVolume() < s2.getVolume())
                        return -1;
                    else
                        return 0;
                }
            }
        }
    };

    public String toString() {
        String res = "";
        res += "Peso Max: " + maxP + "\n";
        res += "Volume Max: " + maxV + "\n";
        res += "Peso corrente: " + curP + "\n";
        res += "Volume corrente: " + curV + "\n";
        res += "Lista articoli: \n";
        for (Articolo articolo : contains) {
            res += articolo.toString() + "\n";
        }
        return res;
    }
}
