#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <renderwidget.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onTimer();

private slots:
    void on_sunlightDirXSlider_sliderMoved(int position);

    void on_sunlightDirYSlider_sliderMoved(int position);

    void on_sunlightDirZSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;

    RenderWidget* glWidget;
    Scene* mainScene;
    QTimer timer;

    void updateSunDir();
};
#endif // MAINWINDOW_H
