#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //criando a matriz com valor padrão de 10
    obj = new Sculptor(10,10,10);

    connect(ui->widget,
            SIGNAL(clickX(int)),
            ui->MouseX,
            SLOT(display(int)));

    connect(ui->widget,
            SIGNAL(clickY(int)),
            ui->MouseY,
            SLOT(display(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
