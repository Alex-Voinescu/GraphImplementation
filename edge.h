#ifndef EDGE_H
#define EDGE_H
#include "node.h"

class Edge
{
    Node *m_first,*m_second;
public:
    Edge();
    Edge(Node *f, Node *s);
    Node* getFirst();
    Node* getSecond();

};

#endif // EDGE_H
