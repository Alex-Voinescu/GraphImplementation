#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>


const int RAZA=10;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    if(m->button() == Qt::RightButton && m_isDragged) {
        m_isDragged = false;
        m_draggedNode = nullptr;
        update();
        return;
    }
    if(m->button()==Qt::RightButton){
        std::vector<Node*> nodes=m_graph.getNodes();
        for(auto& n:nodes){
            if(abs(m->pos().x()-n->getX())<RAZA*2 &&
                abs(m->pos().y()-n->getY())< RAZA*2){
                return;
            }
        }
        m_graph.addNode(m->pos());
        m_graph.saveMatrix();
        update();

    }
    else if(m->button()==Qt::LeftButton){
        std::vector<Node*> nodes=m_graph.getNodes();
        Node* selected=nullptr;
        for(auto& n:nodes){
            if(abs(m->pos().x()-n->getX())<RAZA &&
                abs(m->pos().y()-n->getY())< RAZA){
                selected=n;
                break;
            }
        }
        if(selected!=nullptr){
                if(m_firstNode!=nullptr){
                    if(m_firstNode!=selected){
                        m_graph.addEdge(m_firstNode,selected);
                    }
                    m_firstNode=nullptr;
                    m_graph.saveMatrix();
                    update();
                }
                else
                    m_firstNode=selected;
            }
    }

}

void MainWindow::drawArrow(QPainter &p,QPoint first, QPoint second){

    double dx = second.x() - first.x();
    double dy = second.y() - first.y();

    double angle = std::atan2(dy, dx);

    QPointF startEdge = first + QPointF(std::cos(angle) * RAZA, std::sin(angle) * RAZA);
    QPointF endEdge   = second   - QPointF(std::cos(angle) * RAZA, std::sin(angle) * RAZA);

    p.drawLine(startEdge, endEdge);


    if (m_graph.isOriented()) {
        const double arrowSize = 10.0;
        double gradesToRad=25.0*M_PI/180.0;

        QPointF arrowP1 = endEdge - QPointF(arrowSize * std::cos(angle - gradesToRad),
                                            arrowSize * std::sin(angle - gradesToRad));
        QPointF arrowP2 = endEdge - QPointF(arrowSize * std::cos(angle + gradesToRad),
                                            arrowSize * std::sin(angle + gradesToRad));

        p.drawLine(endEdge, arrowP1);
        p.drawLine(endEdge, arrowP2);
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    std::vector<Node*> nodes=m_graph.getNodes();
    for(auto& n:nodes){
        QRect r(n->getX()-RAZA,n->getY()-RAZA,RAZA*2,RAZA*2);
        p.drawEllipse(r);
        QString s=QString::number(n->getIndex());
        p.drawText(r,Qt::AlignCenter,s);
    }

    std::vector<Edge*> edges=m_graph.getEdges();
    for(auto& ed:edges){
        drawArrow(p,ed->getFirst()->getCoords(),ed->getSecond()->getCoords());
    }
}

void MainWindow::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    m_graph.changeState();
    m_graph.saveMatrix();
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        for (auto n : m_graph.getNodes()) {
            if (std::abs(event->pos().x() - n->getX()) < RAZA &&
                std::abs(event->pos().y() - n->getY()) < RAZA) {
                m_draggedNode = n;
                m_isDragged = true;
                break;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragged && m_draggedNode) {
        m_draggedNode->setCoords(event->pos());
        update();
    }
}
