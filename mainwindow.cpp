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
    updateSunDir();
}


void MainWindow::on_sunlightDirYSlider_sliderMoved(int position)
{
    updateSunDir();
}


void MainWindow::on_sunlightDirZSlider_sliderMoved(int position)
{
    updateSunDir();
}

void MainWindow::updateSunDir()
{
    QVector3D newDir = QVector3D(0,0,-1);
    QMatrix4x4 m;
    m.setToIdentity();
    m.rotate(ui->sunlightDirXSlider->value(),1,0,0);
    m.rotate(ui->sunlightDirYSlider->value(),0,1,0);
    m.rotate(ui->sunlightDirZSlider->value(),0,0,1);
    mainScene->setSunDir(newDir*m);
}

