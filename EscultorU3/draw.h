#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QColor>
#include "sculptor.h"

class Draw : public QWidget
{
    Q_OBJECT
private:
    int linhas;
    int colunas;
    std::vector<std::vector<Voxel>> v;
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
  void posicaoGrade(std::vector<int> p);

public slots:
  void mudarGrade(std::vector<std::vector<Voxel>> m);
  void gradeAtualizada(std::vector<std::vector<Voxel>> m);
};

#endif // DRAW_H
