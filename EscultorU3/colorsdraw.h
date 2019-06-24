// Desculpe-me seu sou um péssimo pai...

#ifndef COLORSDRAW_H
#define COLORSDRAW_H


#include <QWidget>
#include <QAction>
#include <QColor>

class ColorsDraw : public QWidget
{
  Q_OBJECT

private:

  float ampl, freq, vel;
  float teta;
  int timerId;
  QColor lineColor;
  int cor;
  QAction *actionMudaCor;

public:
  explicit ColorsDraw(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void contextMenuEvent(QContextMenuEvent *event);

signals:
  void moveX(int);
  void moveY(int);
  void clickX(int);
  void clickY(int);

public slots:
  void mudaCor();
};


#endif // COLORSDRAW_H
