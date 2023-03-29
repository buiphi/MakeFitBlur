#include "WorkerThread.h"
#include <Logger.h>
#include <QImage>


WorkerThread::WorkerThread(const QStringList &fileNames, std::queue<MyImage> *myImageQueue, QObject *parent)
    : QThread(parent)
    , m_fileNames(fileNames)
    , m_myImageQueue(myImageQueue)
{

}

void WorkerThread::run() {
    _LOG();
    for(QString fileName : m_fileNames){
        QImage image;
        int width = 0;
        int height = 0;
        if(image.load(fileName))
        {
            width = image.width();
            height = image.height();

            qDebug() << "Before >>> Image " << fileName << ", width: " << width << ", height: " << height;

            if((float)image.width() / image.height() == (float)16/9)
                qDebug() << "good";
            else
            {
                qDebug() << "not good";
                width *= (float)16 / 9;
                height *= (float)16 / 9;
            }
            qDebug() << "After >>> Image " << fileName << ", width: " << width << ", height: " << height;
        }
        MyImage myImage{width, height, fileName};
        m_myImageQueue->push(myImage);
    }

    emit calculateBlurSizeFinished();
}
