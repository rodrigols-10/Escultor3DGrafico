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

    // preparando a caneta
    // R, G, B
    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);
    // entregando a caneta ao pintor
    p.setPen(pen);

    // preparando o pincel
    brush.setColor(QColor(r,g,b));
    brush.setStyle(Qt::SolidPattern);
    // entregando o pincel ao pintor
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
