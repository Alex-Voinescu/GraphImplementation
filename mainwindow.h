#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include <QMouseEvent>
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseReleaseEvent(QMouseEvent* m) override;
    void paintEvent(QPaintEvent* e) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::MainWindow *ui;
    Graph m_graph;
    Node* m_firstNode=nullptr;
    Node* m_draggedNode=nullptr;
    bool m_isDragged=false;
    void drawArrow(QPainter &p, QPoint first, QPoint second);
};
#endif // MAINWINDOW_H
