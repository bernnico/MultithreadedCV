#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// #define USE_QTHREAD

#ifdef USE_QTHREAD
#include "videoprocessorthread.h"
#else
#include "videoprocessor.h"
#endif /* USE_QTHREAD */




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

#ifdef USE_QTHREAD
    VideoProcessorThread processor;
#else
    VideoProcessor *processor;
#endif /* USE_QTHREAD */
};
#endif // MAINWINDOW_H
