import java.util.ArrayList;

public class Node {
    int label;
    ArrayList<Edge> edges;
    boolean visited;

    public Node(int l){
        label = l;
        edges = new ArrayList<Edge>();
        visited = false;
    }

    public ArrayList<Node> getNeigh() {
        ArrayList<Node> neigh = new ArrayList<Node>();
        edges.forEach((e) -> neigh.add(e.getN1().getLabel() == label ? e.getN2() : e.getN1()));
        return neigh;
    }

    public int getLabel() {
        return label;
    }

    public ArrayList<Edge> getEdges() {
        return edges;
    }

    public boolean isVisited() {
        return visited;
    }

    public void addEdge (Edge e){
        edges.add(e);
    }

    public void visit (){
        visited = true;
    }

    public void unvisit (){
        visited = false;
    }
}
