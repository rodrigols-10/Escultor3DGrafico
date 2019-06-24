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
    //Inicializando M
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
        m.push_back(l);
    }
    l.clear();

    connect(ui->widget,
            SIGNAL(clickX(int)),
            ui->MouseX,
            SLOT(display(int)));

    connect(ui->widget,
            SIGNAL(clickY(int)),
            ui->MouseY,
            SLOT(display(int)));

    connect(ui->botaoIr,
            SIGNAL(clicked()),
            this,
            SLOT(on_botaoIr_clicked()));

    connect(this,
            SIGNAL(tamanhograde(std::vector<std::vector<Voxel>>)),
            ui->widget,
            SLOT(mudarGrade(std::vector<std::vector<Voxel>>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_botaoIr_clicked()
{
    //matriz Sculptor *s deve ser redimensionada/ apagada e refeita com a nova dimensão
    //matriz *m deve ser deletada e refeita com a nova dimensão, camada atual, plano atual (ela deve ser inicializada no construtor)
    int t = m[0].size();
    for(int i=0; i<t;i++){
        m[i].clear();
    }
    m.clear();
    int tamgrade = ui->TamGrade->value();
    vector<Voxel> l;
    l.resize(tamgrade);
    for(int i = 0; i<tamgrade; i++){
        for(int j = 0; j<tamgrade; j++){
            l[j].isOn = false;
            l[j].r = 1.0;
            l[j].g = 1.0;
            l[j].b = 1.0;
            l[j].a = 1.0;
        }
        m.push_back(l);
    }
    l.clear();


    emit tamanhograde(m);
}
