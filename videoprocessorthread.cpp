#include "videoprocessorthread.h"

#include "opencv2/opencv.hpp"

#include <QDebug>

VideoProcessorThread::VideoProcessorThread(QObject *parent)
    : QThread{parent}
{
    qDebug() << "An object of type QThread";
}

void VideoProcessorThread::run()
{
    using namespace cv;

    VideoCapture camera(0);
    Mat inFrame, outFrame;

    while(camera.isOpened() && !isInterruptionRequested())
    {
        camera >> inFrame;
        if(inFrame.empty())
            continue;

        bitwise_not(inFrame, outFrame);

        emit inDisplay(
            QPixmap::fromImage(
                QImage(
                    inFrame.data,
                    inFrame.cols,
                    inFrame.rows,
                    inFrame.step,
                    QImage::Format_RGB888)
                    .rgbSwapped()));

        emit outDisplay(
            QPixmap::fromImage(
                QImage(
                    outFrame.data,
                    outFrame.cols,
                    outFrame.rows,
                    outFrame.step,
                    QImage::Format_RGB888)
                    .rgbSwapped()));
    }
}
