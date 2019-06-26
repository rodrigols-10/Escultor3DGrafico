#include "colordraw.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

ColorDraw::ColorDraw(QWidget *parent) : QWidget(parent)
{
    r = 0;
    g = 155;
    b = 255;
}

void ColorDraw::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    QBrush brush;

    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);

    p.setPen(pen);


    brush.setColor(QColor(r,g,b));
    brush.setStyle(Qt::SolidPattern);

    p.setBrush(brush);

    p.drawRect(0,0,width(),height());
}

void ColorDraw::changeRed(int _r)
{
    r = _r;
    repaint();
}

void ColorDraw::changeGreen(int _g)
{
    g = _g;
    repaint();
}

void ColorDraw::changeBlue(int _b)
{
    b = _b;
    repaint();
}
