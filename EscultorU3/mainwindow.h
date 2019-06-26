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
    int Objeto = 0;
    float r,g,b,a;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void tamanhograde(std::vector<std::vector<Voxel>> m);
    void atualizagrade(std::vector<std::vector<Voxel>> m);

private slots:
    void on_botaoIr_clicked();

    void criarObjeto(std::vector<int> p);

    void MudalayerX(int);
    void MudalayerY(int);
    void MudalayerZ(int);

    void on_putVoxelButton_clicked();

    void on_putBoxButton_clicked();

    void on_putSphereButton_clicked();

    void on_putEllipsoidButton_clicked();

    void on_cutVoxelButton_clicked();

    void on_cutBoxButton_clicked();

    void on_cutSphereButton_clicked();

    void on_cutEllipsoidButton_clicked();

    void on_up_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_down_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<Voxel>> m;
    Sculptor *obj;
};

#endif // MAINWINDOW_H
