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

    float r,g,b,a; //cores capturadas dos QSliders
    //criando a matriz com valor padrão de 10
    obj = new Sculptor(10,10,10);

    //atribuindo o valor inicial às variaveis de cor
    r = ui->Red->value();
    g = ui->Green->value();
    b = ui->Blue->value();
    a = ui->Transparencia->value();
    //mandando pro Sculptor
    obj->setColor(r,g,b,a);

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

    connect(ui->widget,
            SIGNAL(posicaoGrade(int)), //erro: não há sinal. Suspeita do vetor que é retornado
            this,
            SLOT(criarObjeto(int)));

    connect(ui->botaoIr,
            SIGNAL(clicked()),
            this,
            SLOT(on_botaoIr_clicked()));

    connect(this,
            SIGNAL(tamanhograde(std::vector<std::vector<Voxel>>)),
            ui->widget,
            SLOT(mudarGrade(std::vector<std::vector<Voxel>>)));

    connect(ui->up,
            SIGNAL(clicked()),
            this,
            SLOT(on_up_clicked()));

    //muda a cor do azul na telinha
    connect(ui->Red,
            SIGNAL(valueChanged(int)),
            ui->Color,
            SLOT(changeRed(int)));

    connect(ui->Green,
            SIGNAL(valueChanged(int)),
            ui->Color,
            SLOT(changeGreen(int)));

    connect(ui->Blue,
            SIGNAL(valueChanged(int)),
            ui->Color,
            SLOT(changeBlue(int)));

    //Mostra o valor dos QSliders das cores nos displayers
    connect(ui->Red,
            SIGNAL(valueChanged(int)),
            ui->lcdRed,
            SLOT(display(int)));

    connect(ui->Green,
            SIGNAL(valueChanged(int)),
            ui->lcdGreen,
            SLOT(display(int)));

    connect(ui->Blue,
            SIGNAL(valueChanged(int)),
            ui->lcdBlue,
            SLOT(display(int)));

    connect(ui->Transparencia,
            SIGNAL(valueChanged(int)),
            ui->lcdTransparencia,
            SLOT(display(int)));

    //Mostrar o valor dos QSliders dos Layers nos Displayers
    connect(ui->LayerX,
            SIGNAL(valueChanged(int)),
            ui->lcdX,
            SLOT(display(int)));

    connect(ui->LayerY,
            SIGNAL(valueChanged(int)),
            ui->lcdY,
            SLOT(display(int)));

    connect(ui->LayerZ,
            SIGNAL(valueChanged(int)),
            ui->lcdZ,
            SLOT(display(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_botaoIr_clicked()
{
    int tamgrade = ui->TamGrade->value();
    //TENHO QUE MUDAR O TAMANHO DO SCULPTOR E USAR O MÉTODO ReadPln() PRA AJEITAR O m
    obj->redimensionarMatriz(tamgrade);

    //matriz Sculptor *s deve ser redimensionada/ apagada e refeita com a nova dimensão
    //matriz m deve ser deletada e refeita com a nova dimensão, camada atual, plano atual (ela deve ser inicializada no construtor)
    int t = m[0].size();
    for(int i=0; i<t;i++){
        m[i].clear();
    }
    m.clear();
    //Refazendo matriz m com novas dimensões --- Será substituido por m = ReadPln(); --- Isso vai redimensionar o m no plano que ele estiver
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

void MainWindow::on_up_clicked()
{
    QString s;
    s = ui->label_19->text();

    //Procurar o novo plano escolhido e atribuir isso ao pln
    //Mudar a matriz m para o novo plano na dimensão do referido plano /dimX, dimY ou dimZ
    if(s == "XY"){
        pln = ZX;
        s = "ZX";

        m = obj->readPln(dimY,pln);
    }else{
        if(s == "YZ"){
            pln = ZX;
            s = "ZX";

            m = obj->readPln(dimY,pln);
        }else{
            if(s == "ZX"){
                pln = XY;
                s = "XY";
                m = obj->readPln(dimZ,pln);
            }
        }
    }
    //Mandar a nova matriz m para o Draw

    //mudei o texto em s, agora mando pro label
    ui->label_19->setText(s);
}

void MainWindow::on_putVoxelButton_clicked()
{
    Objeto = 1;
}

void MainWindow::on_putBoxButton_clicked()
{
    Objeto = 2;
}

void MainWindow::on_putSphereButton_clicked()
{
    Objeto = 3;
}

void MainWindow::on_putEllipsoidButton_clicked()
{
    Objeto = 4;
}

void MainWindow::on_cutVoxelButton_clicked()
{
    Objeto = 5;
}

void MainWindow::on_cutBoxButton_clicked()
{
    Objeto = 6;
}

void MainWindow::on_cutSphereButton_clicked()
{
    Objeto = 7;
}

void MainWindow::on_cutEllipsoidButton_clicked()
{
    Objeto = 8;
}

void MainWindow::criarObjeto(int p[])
{
    int pos[2];
    pos[0] = p[0];
    pos[1] = p[1];
}
