import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Queue;

public class Graph implements Iterable<Integer> {
    ArrayList<Node> nodes;
    int eNum;

    public Graph() {
        nodes = new ArrayList<Node>();
        eNum = 0;
    }

    public ArrayList<Node> getNodes() {
        return nodes;
    }

    public int geteNum() {
        return eNum;
    }

    public void addNode(Node node) {
        nodes.add(node);
    }

    /**
     * inserisce un arco già instanziato
     * 
     * @param edge arco completo da inserire
     */
    public void addEdge(Edge edge) {
        for (Node node : nodes) {
            if (node.equals(edge.getN1()) || node.equals(edge.getN2()))
                node.addEdge(edge);
            eNum++;
        }
    }

    /**
     * instanzia e inserisce un arco
     * 
     * @param l1 nodo 1
     * @param l2 nodo 2
     * @param w  peso dell'arco
     */
    public void addEdge(int l1, int l2, double w) {
        Node n1 = null, n2 = null;
        for (Node node : nodes) {
            if (node.getLabel() == l1)
                n1 = node;
            if (node.getLabel() == l2)
                n2 = node;
        }
        eNum++;
        Edge newEdge = new Edge(n1, n2, w);
        n1.addEdge(newEdge);
        n2.addEdge(newEdge);
    }

    public void reset() {
        for (Node node : nodes) {
            node.unvisit();
        }
    }

    @Override
    public Iterator<Integer> iterator() {
        return new BFSIterator();
    }

    private class BFSIterator implements Iterator<Integer> {
        Queue<Node> nodeq;
        int visitedCount;

        public BFSIterator() {
            nodeq = new ArrayDeque<Node>();
            nodeq.offer(nodes.get(0));
            this.visitedCount = 0;
        }

        @Override
        public boolean hasNext() {
            return visitedCount < nodes.size();
        }

        @Override
        public Integer next() {
            boolean ok = false;

            // true se finisco la componente connessa o la coda è vuota
            if (nodeq.isEmpty()) {
                for (Node node : nodes) {
                    if (!node.isVisited()) {
                        // ci sono altre componenti connesse
                        ok = true;
                        nodeq.offer(node);
                        break;
                    }
                }
                if (!ok) // qui ho finito tutte le componenti connesse
                    throw new NoSuchElementException();
            }

            while (nodeq.peek().isVisited())
                nodeq.poll(); // rimuovo gli elementi in cima già visitati

            Node n = nodeq.poll(); // sicuramente non è visitato
            n.visit(); // visito elemento n
            // aggiungo vicini nella coda
            for (Node m : n.getNeigh()) {
                if (!m.isVisited())
                    nodeq.offer(m);

            }
            visitedCount++;

            return n.getLabel();
        }

    }

}
