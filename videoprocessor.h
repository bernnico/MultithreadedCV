#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QThread>
#include <QPixmap>

class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent);

signals:
    void inDisplay(QPixmap pixmap);
    void outDisplay(QPixmap pixmap);

public slots:
    void startVideo();
    void stopVideo();

private:
    bool stopped;

};

#endif // VIDEOPROCESSOR_H
