#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sculptor.h"
#include "vector"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void changeXY();
    void changeYZ();
    void changeZX();
    void putVoxel();
    void cutVoxel();
    void putBox();
    void cutBox();
    void putShpere();
    void cutShpere();
    void putEllipsoide();
    void cutEllipsoide();
    void selectPlane();

protected:
    Ui::MainWindow *ui;
    std::vector<std::vector<Voxel>> m;
};

#endif // MAINWINDOW_H
