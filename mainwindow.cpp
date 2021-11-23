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
    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            mainScene->addParticle(QVector3D(row,0,col));
        }
    }
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


void MainWindow::on_sunlightDirXSlider_sliderMoved(int position)
{
    QVector3D currentSunDir = mainScene->getSunDir();
    currentSunDir.setX(position);
    mainScene->setSunDir(currentSunDir);
}


void MainWindow::on_sunlightDirYSlider_sliderMoved(int position)
{
    QVector3D currentSunDir = mainScene->getSunDir();
    currentSunDir.setY(position);
    mainScene->setSunDir(currentSunDir);
}


void MainWindow::on_sunlightDirZSlider_sliderMoved(int position)
{
    QVector3D currentSunDir = mainScene->getSunDir();
    currentSunDir.setZ(position);
    mainScene->setSunDir(currentSunDir);
}

