#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QColor>

struct DrawVoxel {
  float r,g,b; // Colors
  float a;
// Transparency
  bool isOn; // Included or not
};

class Draw : public QWidget
{
    Q_OBJECT
private:
    int linhas;
    int colunas;
    DrawVoxel **v;
    int r,g,b,a;
    QColor Preenchimento;
    int PosX;
    int PosY;
public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
  void clickX(int);
  void clickY(int);

public slots:
};

#endif // DRAW_H
