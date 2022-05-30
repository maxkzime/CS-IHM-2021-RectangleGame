#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <list>
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>

using std::list;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void reset();

private:
    list<QRect *> itsRectangles;
    int rectW = 40;
    int rectH = 10;
    bool horizontalRect = true;

    QColor basicRectColor = Qt::black;

    QPushButton * itsButton = new QPushButton(this);
    bool itsRectSelected = false;

    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent * event);

    QPoint offset;
};
#endif // WIDGET_H
