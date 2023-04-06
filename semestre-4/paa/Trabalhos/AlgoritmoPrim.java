import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Prim {

    // Classe que representa um grafo
    public static class Graph {
        private Map<Integer, Map<Integer, Integer>> graph = new HashMap<>();

        public Graph() {

        }

        // Insere uma aresta dentro do grafo
        public void addEdge(Integer fromNode, Integer toNode, Integer cost) {
            if (!graph.containsKey(fromNode)) {
                Map<Integer, Integer> paths = new HashMap<>();
                paths.put(toNode, cost);
                graph.put(fromNode, paths);
            } else {
                graph.get(fromNode).put(toNode, cost);
            }
        }

        // Nós não visitados são aqueles que ainda estão dentro da lista de prioridades
        public List<Integer> getNotVisitedNeighbors(Integer node, Map<Integer, Integer> priorities) {
            List<Integer> notVisitedNeighbors = new ArrayList<>();

            for (Object key : graph.get(node).keySet()) {
                if (priorities.containsKey((Integer) key)) {
                    notVisitedNeighbors.add((Integer) key);
                }
            }
            return notVisitedNeighbors;
        }

        public void printGraph() {
            System.out.println("Graph: ");
            for (Object key : graph.keySet().toArray()) {
                System.out.print(key + ": ");
                for (Object neighbor : graph.get(key).keySet()) {
                    System.out.print(neighbor + " ");
                }
                System.out.println();
            }
        }

        public Object[] getKeySet() {
            return this.graph.keySet().toArray();
        }

        public Integer getEdgeCost(Integer fromNode, Integer toNode) {
            return graph.get(fromNode).get(toNode);
        }
    }

    // Cria a lista de prioridades, começando todos os valores como infinito (Integer.MAX_VALUE)
    public static Map<Integer, Integer> getPriorityList(Graph g) {
        Object[] keyset = g.getKeySet();
        Map<Integer, Integer> priority = new HashMap<>();
        for (Object key : keyset) {
            priority.put((Integer) key, Integer.MAX_VALUE);
        }
        return priority;
    }

    // Cria o HashMap de predecessores
    public static Map<Integer, Integer> getPredecessors(Graph g) {
        Object[] keyset = g.getKeySet();
        Map<Integer, Integer> predecessors = new HashMap<>();
        for (Object key : keyset) {
            predecessors.put((Integer) key, -1);
        }
        return predecessors;
    }

    public static Integer getMinKey(Map<Integer, Integer> priorities) {
        Integer minKeyCost = Integer.MAX_VALUE;
        Integer minKey = null;
        for (Object key : priorities.keySet()) {
            if (minKey == null) {
                minKey = (Integer) key;
                minKeyCost = priorities.get(key);
            } else if (priorities.get(key) < minKeyCost) {
                minKey = (Integer) key;
                minKeyCost = priorities.get(key);
            }
        }
        return minKey;
    }


    public static void main(String[] args) {

        Graph g = new Graph();
        g.addEdge(1, 2, 4);
        g.addEdge(1, 8, 8);

        g.addEdge(2, 1, 4);
        g.addEdge(2, 3, 8);
        g.addEdge(2, 8, 11);

        g.addEdge(3, 2, 8);
        g.addEdge(3, 4, 7);
        g.addEdge(3, 6, 4);
        g.addEdge(3, 9, 2);

        g.addEdge(4, 3, 7);
        g.addEdge(4, 5, 9);
        g.addEdge(4, 6, 14);

        g.addEdge(5, 4, 9);
        g.addEdge(5, 6, 10);

        g.addEdge(6, 3, 4);
        g.addEdge(6, 4, 14);
        g.addEdge(6, 5, 10);
        g.addEdge(6, 7, 2);

        g.addEdge(7, 6, 2);
        g.addEdge(7, 8, 1);
        g.addEdge(7, 9, 6);

        g.addEdge(8, 1, 8);
        g.addEdge(8, 2, 11);
        g.addEdge(8, 7, 1);
        g.addEdge(8, 9, 7);

        g.addEdge(9, 3, 2);
        g.addEdge(9, 8, 6);
        g.addEdge(9, 7, 7);

        g.printGraph();

        // Lista de prioridades
        Map<Integer, Integer> priorities = getPriorityList(g);
        // Lista de predecessores
        Map<Integer, Integer> predecessors = getPredecessors(g);

        // Aplicando o algoritmo de prim
        while (priorities.size() > 0) {
            Integer minKey = getMinKey(priorities);
            priorities.remove(minKey);

            System.out.println("\nMinKey: " + minKey);
            for (Integer neighbor : g.getNotVisitedNeighbors(minKey, priorities)) {
                System.out.println("Priorities: " + priorities);
                Integer newNeighborCost = Math.min(priorities.get(neighbor), g.getEdgeCost(minKey, neighbor));
                priorities.replace(neighbor, newNeighborCost);
                predecessors.replace(neighbor, minKey);
                System.out.println("Priorities updated: " + priorities);
            }
            System.out.println();
        }

        // Imprimido o resultado final dos predecessores dos nós do grafo
        System.out.println("Predecessors: ");
        for (Object node : predecessors.keySet()) {
            System.out.println("Node: " + node + ", predecessor: " + predecessors.get(node));
        }
    }
}