#include "draw.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QColorDialog>
#include <QMessageBox>
#include <QString>
#include <QColor>


Draw::Draw(QWidget *parent) : QWidget(parent)
{
    linhas = 10; //receberá o tamanho X da matriz quando ela existir.
    colunas = 10; // " Y "
    r = 0;
    g = 255;
    b = 0;
    a = 1;
    PosX=-1;
    PosY=-1;

    vector<Voxel> l;
    l.resize(10);
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            l[j].isOn = false;
            l[j].r = 1.0;
            l[j].g = 1.0;
            l[j].b = 1.0;
            l[j].a = 1.0;
        }
        v.push_back(l);
    }
    l.clear();
}

void Draw::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  QPen pen;
  QBrush brush;

  // habilita algoritmos de anti-serrilhamento
  //p.setRenderHint(QPainter::Antialiasing);

  // preparando a caneta
  // R, G, B
  pen.setColor(QColor(0,0,0));
  pen.setWidth(2);
  // entregando a caneta ao pintor
  p.setPen(pen);

  // preparando o pincel
  brush.setColor(QColor(255,255,255));
  brush.setStyle(Qt::SolidPattern);
  // entregando o pincel ao pintor
  //p.setBrush(brush); //tá pitando o fundo todo

  p.drawRect(0,0,width(),height());

  //Começa a desenhar os retangulos

  pen.setStyle(Qt::SolidLine);
  p.setPen(pen);

  int px, py;
  int txy;

  px= 0;
  py= 0;
  txy=0;
  if(width()<height()){
      txy = (int) width()/linhas;
  } else {
      txy = (int) height()/colunas;
  }
  p.setBrush(brush);
  for(int i=0; i<linhas; i++){
      for(int j=0; j<colunas; j++){
          if(v[i][j].isOn){
              r = (int) 255*v[i][j].r;
              g = (int) 255*v[i][j].g;
              b = (int) 255*v[i][j].b;
              brush.setColor(QColor(r,g,b));
              p.drawRect(px,py,txy,txy);
              py = py + txy;
          } else{
              brush.setColor(QColor(255,255,255));
              p.drawRect(px,py,txy,txy);
              py = py + txy;
          }
      }
      px = px + txy;
      py = 0;
  }

}

void Draw::mousePressEvent(QMouseEvent *event){
    std::vector<int> Pos;
  if(event->button() == Qt::LeftButton ){
    PosX = (int) event->x()/(width()/linhas);
    PosY = (int) event->y()/(height()/colunas);
    Pos.push_back(PosX);
    Pos.push_back(PosY);

    //emitindo posição
    emit clickX(PosX);
    emit clickY(PosY);
    emit posicaoGrade(Pos);

    repaint();
  }
}

void Draw::mudarGrade(std::vector<std::vector<Voxel>> m)
{
    linhas = m.size();
    colunas = m[0].size();
    v = m;
    repaint();
}

void Draw::gradeAtualizada(std::vector<std::vector<Voxel> > m)
{
    v = m;
    repaint();
}
