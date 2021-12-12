public class Edge {
    private Node n1, n2;
    private double weight;

    public Edge(Node n1, Node n2, double w) {
        this.n1 = n1;
        this.n2 = n2;
        weight = w >= 0 ? w : 0;
    }

    public Node getN1() {
        return n1;
    }

    public Node getN2() {
        return n2;
    }

    public double getWeight() {
        return weight;
    }

}
