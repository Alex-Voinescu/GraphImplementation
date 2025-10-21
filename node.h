#ifndef NODE_H
#define NODE_H
#include <QPoint>

class Node
{
private:
    int m_index;
    QPoint m_coord;

public:
    Node(int index=0, QPoint p=QPoint(0,0));
    void setIndex(int index);
    void setCoords(QPoint p);
    int getIndex();
    QPoint getCoords();
    int getX();
    int getY();
};

#endif // NODE_H
