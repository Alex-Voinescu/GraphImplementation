#include "edge.h"

Edge::Edge() {}

Edge::Edge(Node* f, Node* s):m_first(f),m_second(s)
{}
Node* Edge::getFirst(){
    return m_first;
}
Node* Edge::getSecond(){
    return m_second;
}
