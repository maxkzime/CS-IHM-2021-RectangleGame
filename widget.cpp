#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("CS IHM 2021");
    setGeometry(200, 200, 300, 400);

    itsButton->setText("Effacer");
    connect(itsButton, &QAbstractButton::clicked, this, &Widget::reset);
}


void Widget::reset()
{
    itsRectSelected = false;
    itsRectangles.clear();
    repaint();
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        QRect * r;

        if(horizontalRect)
            r = new QRect(event->pos().x()-rectW/2, event->pos().y()-rectH, rectW, rectH);
        else
            r = new QRect(event->pos().x(), event->pos().y()-rectH, rectH, rectW);

        itsRectangles.push_back(r);
        repaint();
    }

    if (event->button() == Qt::LeftButton)
    {
        list<QRect *>::iterator it;
        if (!itsRectangles.empty())
        {
            it = itsRectangles.begin();
            if ((*it)->contains(event->pos()))
            {
                itsRectSelected = true;
                offset = event->pos() - (*it)->topLeft();
            }
        }
    }

    QWidget::mousePressEvent(event);
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
        horizontalRect = horizontalRect ? false : true;

    QWidget::keyPressEvent(event);
}


void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    itsRectSelected = false;

    basicRectColor = Qt::black;
    repaint();

    QWidget::mouseReleaseEvent(event);
}


void Widget::mouseMoveEvent(QMouseEvent *event)
{
    std::list<QRect *>::iterator it;
    if (!itsRectangles.empty())
    {
        if (itsRectSelected)
        {
            it = itsRectangles.begin();
            (*it)->moveTo(event->pos()-offset);
            repaint();


            for (QRect * rect : itsRectangles ) {
                if((*it) != rect && (*it)->intersects(*rect))
                    basicRectColor = Qt::red;
            }
        }
    }
}


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    QBrush b;
    b.setColor(Qt::blue);
    b.setStyle(Qt::SolidPattern);
    painter.setBrush(b);

    for (QRect * r : itsRectangles)
    {
        painter.drawRect(*r);
        painter.setPen(basicRectColor);
        b.setColor(basicRectColor);
        painter.setBrush(b);
    }

    QWidget::paintEvent(event);
}


Widget::~Widget()
{}

