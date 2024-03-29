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
    /* Tava dando erro, já que não tinha nada além disso
    void changeXY();
    void changeYZ();
    void changeZX();
    void putVoxel();
    void cutVoxel();
    void putBox();
    void cutBox();
    void putSphere();
    void cutSphere();
    void putEllipsoide();
    void cutEllipsoide();
    void selectPlane();
*/

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<Voxel>> m;
    Sculptor *obj;
};

#endif // MAINWINDOW_H
