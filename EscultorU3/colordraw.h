#ifndef COLORDRAW_H
#define COLORDRAW_H

#include <QWidget>

class ColorDraw : public QWidget
{
    Q_OBJECT

private:
    int r,g,b;
public:
    explicit ColorDraw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void changeRed(int _r);
    void changeGreen(int _g);
    void changeBlue(int _b);
};

#endif // COLORDRAW_H
