#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , processor(this)
{
    ui->setupUi(this);

    connect(&processor, SIGNAL(inDisplay(QPixmap)),
            ui->inVideo, SLOT(setPixmap(QPixmap)));

    connect(&processor, SIGNAL(outDisplay(QPixmap)),
            ui->outVideo, SLOT(setPixmap(QPixmap)));

#ifdef USE_QTHREAD
    processor.start();
#else
    processor.thread()->start();
#endif /* USE_QTHREAD */
}

MainWindow::~MainWindow()
{
#ifdef USE_QTHREAD
    processor.requestInterruption();
    processor.wait();
#else
    processor.stopVideo();
    processor.thread()->quit();
    processor.thread()->wait();
#endif /* USE_QTHREAD */

    delete ui;
}
