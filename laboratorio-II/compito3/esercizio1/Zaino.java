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
            maxV += a.getVolume();
            maxP += a.getPeso();
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
            if (articolo.getTipo() == t)
                return true;
        }
        return false;
    }

    void riempi(Magazzino m) {
        List<Articolo> items = m.disponibili();
        items.sort(artComparator);

        for (Articolo articolo : items) {
            if (puo_contenere(articolo)) {
                try {
                    aggiungi(articolo);
                    m.prendi1(articolo);
                } catch (Exception e) {
                    continue;
                }
            }
        }
    }

    public static Comparator<Articolo> artComparator = new Comparator<Articolo>() {

        public int compare(Articolo s1, Articolo s2) {
            if (Articolo.getValore(s1) > Articolo.getValore(s2))
                return 1;
            else if (Articolo.getValore(s1) < Articolo.getValore(s2))
                return -1;
            else {
                if (s1.getPeso() > s2.getPeso())
                    return -1;
                else if (s1.getPeso() > s2.getPeso())
                    return 1;
                else {
                    if (s1.getVolume() > s2.getVolume())
                        return -1;
                    else if (s1.getVolume() < s2.getVolume())
                        return 1;
                    else
                        return 0;
                }
            }
        }
    };

}
