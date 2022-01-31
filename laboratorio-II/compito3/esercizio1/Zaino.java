import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Zaino {
    private int maxP;
    private int maxV;
    private int curP;
    private int curV;
    private List<Articolo> contains;

    public Zaino(int p, int v) {
        maxP = p;
        maxV = v;
        curP = 0;
        curV = 0;
        contains = new ArrayList<>();
    }

    public boolean puo_contenere(Articolo a) {
        return maxP - curP >= a.getPeso() && maxV - curV >= a.getVolume();
    }

    public void aggiungi(Articolo a) throws NoWay {
        if (puo_contenere(a)) {
            contains.add(a);
            curV += a.getVolume();
            curP += a.getPeso();
        } else
            throw new NoWay();
    }

    public void svuota() {
        contains.clear();
    }

    public int peso() {
        int res = 0;
        for (Articolo articolo : contains) {
            res += articolo.getPeso();
        }
        return res;
    }

    public int volume() {
        int res = 0;
        for (Articolo articolo : contains) {
            res += articolo.getVolume();
        }
        return res;
    }

    public int valore() {
        int res = 0;
        for (Articolo articolo : contains) {
            res += Articolo.getValore(articolo);
        }
        return res;
    }

    public boolean contiene_tipo(String t) {
        for (Articolo articolo : contains) {
            if (articolo.getTipo().compareTo(t) == 0)
                return true;
        }
        return false;
    }

    public void riempi(Magazzino m) {
        boolean alreadyThere = false;
        List<Articolo> items = m.disponibili();
        items.sort((Articolo i1, Articolo i2) -> {
            if (Articolo.getValore(i1) != Articolo.getValore(i2))
                return Articolo.getValore(i2) - Articolo.getValore(i1);
            else if (i1.getPeso() != i2.getPeso())
                return i1.getPeso() - i2.getPeso();
            else if (i1.getVolume() != i2.getVolume())
                return i1.getVolume() - i2.getVolume();

            return 0;
        });

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
