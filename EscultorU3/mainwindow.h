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

private:
    int dimX = 0;
    int dimY = 0;
    int dimZ = 0;
    int pln = XY;
    int Objeto;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void tamanhograde(std::vector<std::vector<Voxel>> mm);
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

private slots:
    void on_botaoIr_clicked();

    void on_up_clicked();

    void on_putVoxelButton_clicked();

    void on_putBoxButton_clicked();

    void on_putSphereButton_clicked();

    void on_putEllipsoidButton_clicked();

    void on_cutVoxelButton_clicked();

    void on_cutBoxButton_clicked();

    void on_cutSphereButton_clicked();

    void on_cutEllipsoidButton_clicked();

    void criarObjeto(int p[]);
private:
    Ui::MainWindow *ui;

    std::vector<std::vector<Voxel>> m;
    Sculptor *obj;
};

#endif // MAINWINDOW_H
