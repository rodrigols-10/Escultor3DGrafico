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

    v = new DrawVoxel*[10];
    for(int i=0; i<10; i++){
        v[i] = new DrawVoxel[10];
    }

    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            v[i][j].r = 255;
            v[i][j].g = 255;
            v[i][j].b = 255;
            v[i][j].a = 1;
            v[i][j].isOn = false;
     }
    }
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
              brush.setColor(QColor(v[i][j].r,v[i][j].g,v[i][j].g));
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
  //Temporário
  if(PosX!=-1){
  brush.setColor(QColor(r,g,b));
  p.setBrush(brush);
  p.drawRect(PosX*txy,PosY*txy,txy,txy);
  }
  //----------
}

void Draw::mousePressEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton ){
    PosX = (int) event->x()/(width()/linhas);
    PosY = (int) event->y()/(height()/colunas);
    emit clickX(PosX);
    emit clickY(PosY);

    repaint();
  }
}
