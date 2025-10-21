#include "node.h"



Node::Node(int index, QPoint p):m_index(index), m_coord(p)
{

}

void Node::setIndex(int index){
    m_index=index;
}
void Node::setCoords(QPoint p){
    m_coord=p;
}
int Node::getIndex(){
    return m_index;
}
QPoint Node::getCoords(){
    return m_coord;
}
int Node::getX(){
    return m_coord.x();
}
int Node::getY(){
    return m_coord.y();
}
