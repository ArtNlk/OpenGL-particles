#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glWidget = new RenderWidget(this);

    ui->glLayout->addWidget(glWidget);

    timer.setInterval(10);
    connect(&timer,&QTimer::timeout,this,&MainWindow::onTimer);

    mainScene = new Scene();
    glWidget->setScene(mainScene);
    mainScene->setCameraSpeed(0.1);
    //mainScene->moveCamera(QVector3D(0,5,0));
    //mainScene->rotateCamera(0,90.f);

    //Corners
    mainScene->addParticle(QVector3D(-1,-1,-1));
    mainScene->addParticle(QVector3D(-1,1,-1));
    mainScene->addParticle(QVector3D(1,-1,-1));
    mainScene->addParticle(QVector3D(1,1,-1));
    mainScene->addParticle(QVector3D(-1,-1,1));
    mainScene->addParticle(QVector3D(-1,1,1));
    mainScene->addParticle(QVector3D(1,-1,1));
    mainScene->addParticle(QVector3D(1,1,1));

    //Midpoints
    mainScene->addParticle(QVector3D(0,-1,-1));
    mainScene->addParticle(QVector3D(-1,-1,0));
    mainScene->addParticle(QVector3D(0,-1,1));
    mainScene->addParticle(QVector3D(1,-1,0));

    mainScene->addParticle(QVector3D(-1,0,-1));
    mainScene->addParticle(QVector3D(-1,0,1));
    mainScene->addParticle(QVector3D(1,0,1));
    mainScene->addParticle(QVector3D(1,0,-1));

    mainScene->addParticle(QVector3D(0,1,-1));
    mainScene->addParticle(QVector3D(-1,1,0));
    mainScene->addParticle(QVector3D(0,1,1));
    mainScene->addParticle(QVector3D(1,1,0));
//    for(int row = 0; row < 3; row++)
//    {
//        for(int col = 0; col < 3; col++)
//        {
//            mainScene->addParticle(QVector3D(row/3.0,0,col/3.0));
//        }
//    }
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimer()
{
    mainScene->step(qobject_cast<QTimer*>(QObject::sender())->interval());
    glWidget->update();
}

