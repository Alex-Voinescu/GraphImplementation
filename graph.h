#ifndef GRAPH_H
#define GRAPH_H
#include "edge.h"
#include <vector>

class Graph
{
    std::vector<Node*> m_nodes;
    std::vector<Edge*> m_edges;
    bool m_oriented;

public:
    Graph();
    ~Graph();

    void addNode(QPoint p);
    void addEdge(Node* first, Node* second);

    std::vector<Node*> getNodes();
    std::vector<Edge*> getEdges();
    bool isOriented();

    void changeState();
    void saveMatrix();
};

#endif // GRAPH_H
