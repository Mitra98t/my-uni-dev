class Main {
    public static void main(String[] args) {
        Graph g = new Graph();

        for (int i = 1; i <= 6; i++) {
            Node n = new Node(i);
            g.addNode(n);
        }

        double[][] edges = { { 1, 2, 2 }, { 1, 3, 1 }, { 2, 3, 3 }, { 2, 4, 4 }, { 2, 5, 5 }, { 3, 5, 6 }, { 4, 5, 6 },
                { 4, 6, 7 }, { 5, 6, 8 } };

        for (int i = 0; i < edges.length; i++) {
            g.addEdge((int) edges[i][0], (int) edges[i][1], edges[i][2]);
        }

        for (int n : g) {
            System.out.println(n);
        }
    }
}
