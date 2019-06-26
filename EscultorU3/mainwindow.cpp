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

    //atribuindo o valor inicial às variaveis de cor
    r = ui->Red->value()/255;
    g = ui->Green->value()/255;
    b = ui->Blue->value()/255;
    a = ui->Transparencia->value()/255;
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
            SIGNAL(posicaoGrade(std::vector<int>)),
            this,
            SLOT(criarObjeto(std::vector<int>)));

    connect(ui->botaoIr,
            SIGNAL(clicked()),
            this,
            SLOT(on_botaoIr_clicked()));

    connect(this,
            SIGNAL(tamanhograde(std::vector<std::vector<Voxel>>)),
            ui->widget,
            SLOT(mudarGrade(std::vector<std::vector<Voxel>>)));

    connect(this,
            SIGNAL(atualizagrade(std::vector<std::vector<Voxel>>)),
            ui->widget,
            SLOT(gradeAtualizada(std::vector<std::vector<Voxel>>)));

    //muda a cor na telinha
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
            this,
            SLOT(MudalayerX(int))); //Fazer algo a respeito do valor máximo do QSlider

    connect(ui->LayerY,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(MudalayerY(int))); //Fazer algo a respeito do valor máximo do QSlider

    connect(ui->LayerZ,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(MudalayerZ(int))); //Fazer algo a respeito do valor máximo do QSlider
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
    //Procurar o novo plano escolhido e atribuir isso ao pln
    //Mudar a matriz m para o novo plano na dimensão do referido plano /dimX, dimY ou dimZ
    switch(pln){
        case XY:
            pln = ZX;
            ui->label_19->setText("ZX");
            m = obj->readPln(dimY,pln);
        break;
        case YZ:
            pln = ZX;
            ui->label_19->setText("ZX");
            m = obj->readPln(dimY,pln);
        break;
        case ZX:
            pln = XY;
            ui->label_19->setText("XY");
            m = obj->readPln(dimZ,pln);
        break;
    }

    //Mandar a nova matriz m para o Draw
    emit atualizagrade(m);
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

void MainWindow::criarObjeto(std::vector<int> p)
{
    std::vector<int> pos;
    pos = p; //pos[0] é o X da grade e pos[1] é o Y da grade
    int xg = pos[0];
    int yg = pos[1]; //Vê se dá certo

    r = (float)(ui->Red->value())/255;
    g = (float)(ui->Green->value())/255;
    b = (float)(ui->Blue->value())/255;
    a = (float)(ui->Transparencia->value())/100;

    switch (Objeto) {
        case 1: //putVoxel
            switch(pln){
                case XY:
                    //cria objeto
                    obj->setColor(r,g,b,a);
                    obj->putVoxel(xg,yg,dimZ);

                    m = obj->readPln(dimZ,pln);
                    emit atualizagrade(m);
                break;
                case YZ:
                    //cria objeto
                    obj->setColor(r,g,b,a);
                    obj->putVoxel(dimX,yg,xg);

                    m = obj->readPln(dimX,pln);
                    emit atualizagrade(m);
                break;
                case ZX:
                    //cria objeto
                    obj->setColor(r,g,b,a);
                    obj->putVoxel(xg,dimY,yg);

                    m = obj->readPln(dimY,pln);
                    emit atualizagrade(m);
                break;
            }
        break;
        case 2: //putBox
            switch(pln){
                case XY:
                    //cria objeto
                    obj->setColor(r,g,b,a);
                    obj->putBox(xg, xg+ui->Box_tamX->value(), yg, yg+ui->Box_tamY->value(), dimZ, dimZ+ui->Box_tamZ->value());

                    m = obj->readPln(dimZ,pln);
                    emit atualizagrade(m);
                break;
                case YZ:
                    //cria objeto
                    obj->setColor(r,g,b,a);
                    obj->putBox(dimX, dimX+ui->Box_tamX->value(),yg, yg+ui->Box_tamY->value(), xg, xg+ui->Box_tamZ->value());
                    m = obj->readPln(dimX,pln);
                    emit atualizagrade(m);
                break;
                case ZX:
                    //cria objeto
                    obj->putBox(xg, xg+ui->Box_tamX->value(),dimY, dimY+ui->Box_tamY->value(), yg, yg+ui->Box_tamZ->value());

                    m = obj->readPln(dimY,pln);
                    emit atualizagrade(m);
                break;
            }
        break;
        case 3: //putSphere
            switch(pln){
                case XY:
                    //cria objeto


                break;
                case YZ:
                    //cria objeto


                break;
                case ZX:
                    //cria objeto


                break;
            }
        break;
        case 4://putEllipsoid
            switch(pln){
                case XY:
                    //cria objeto


                break;
                case YZ:
                    //cria objeto


                break;
                case ZX:
                    //cria objeto


                break;
            }
        break;
        case 5: //cutVoxel
            switch(pln){
                case XY:
                    //cria objeto


                break;
                case YZ:
                    //cria objeto


                break;
                case ZX:
                    //cria objeto


                break;
            }
        break;
        case 6: //cutBox
            switch(pln){
                case XY:
                    //cria objeto


                break;
                case YZ:
                    //cria objeto


                break;
                case ZX:
                    //cria objeto


                break;
            }
        break;
        case 7: //cutSphere
            switch(pln){
                case XY:
                    //cria objeto


                break;
                case YZ:
                    //cria objeto


                break;
                case ZX:
                    //cria objeto


                break;
            }
        break;
        case 8: //cutEllipsoid
            switch(pln){
                case XY:
                    //cria objeto


                break;
                case YZ:
                    //cria objeto


                break;
                case ZX:
                    //cria objeto


                break;
            }
        break;
    }


}

void MainWindow::MudalayerX(int valor)
{
    dimX = (int) (m[0].size()-1)*valor/100;
    ui->lcdX->display(dimX);
    if(pln == YZ){
        m = obj->readPln(dimX,pln);
        emit atualizagrade(m);
    }
}

void MainWindow::MudalayerY(int valor)
{
    dimY = (int) (m[0].size()-1)*valor/100;
    ui->lcdY->display(dimY);
    if(pln == ZX){
        m = obj->readPln(dimY,pln);
        emit atualizagrade(m);
    }
}

void MainWindow::MudalayerZ(int valor)
{
    dimZ = (int) (m[0].size()-1)*valor/100;
    ui->lcdZ->display(dimZ);
    if(pln == XY){
        m = obj->readPln(dimZ,pln);
        emit atualizagrade(m);
    }
}

void MainWindow::on_left_clicked()
{
    //Procurar o novo plano escolhido e atribuir isso ao pln
    //Mudar a matriz m para o novo plano na dimensão do referido plano /dimX, dimY ou dimZ
    switch(pln){
        case XY:
            pln = YZ;
            ui->label_19->setText("YZ");
            m = obj->readPln(dimX,pln);
        break;
        case YZ:
            pln = XY;
            ui->label_19->setText("XY");
            m = obj->readPln(dimZ,pln);
        break;
        case ZX:
            pln = YZ;
            ui->label_19->setText("XY");
            m = obj->readPln(dimX,pln);
        break;
        ;
    }

    //Mandar a nova matriz m para o Draw
    emit atualizagrade(m);
}

void MainWindow::on_right_clicked()
{
    //Procurar o novo plano escolhido e atribuir isso ao pln
    //Mudar a matriz m para o novo plano na dimensão do referido plano /dimX, dimY ou dimZ
    switch(pln){
        case XY:
            pln = YZ;
            ui->label_19->setText("YZ");
            m = obj->readPln(dimX,pln);
        break;
        case YZ:
            pln = XY;
            ui->label_19->setText("XY");
            m = obj->readPln(dimZ,pln);
        break;
        case ZX:
            pln = YZ;
            ui->label_19->setText("XY");
            m = obj->readPln(dimX,pln);
        break;
        ;
    }

    //Mandar a nova matriz m para o Draw
    emit atualizagrade(m);
}

void MainWindow::on_down_clicked()
{
    //Procurar o novo plano escolhido e atribuir isso ao pln
    //Mudar a matriz m para o novo plano na dimensão do referido plano /dimX, dimY ou dimZ
    switch(pln){
        case XY:
            pln = ZX;
            ui->label_19->setText("ZX");
            m = obj->readPln(dimY,pln);
        break;
        case YZ:
            pln = ZX;
            ui->label_19->setText("ZX");
            m = obj->readPln(dimY,pln);
        break;
        case ZX:
            pln = XY;
            ui->label_19->setText("XY");
            m = obj->readPln(dimZ,pln);
        break;
        ;
    }

    //Mandar a nova matriz m para o Draw
    emit atualizagrade(m);
}
