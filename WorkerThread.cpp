#include "WorkerThread.h"
#include <Logger.h>
#include <QImageReader>
//#include <QElapsedTimer>


WorkerThread::WorkerThread(const QList<QUrl> &fileUrls, std::queue<Image> *imageQueue, QObject *parent)
    : QThread(parent)
    , m_fileUrls(fileUrls)
    , m_imageQueue(imageQueue)
{

}

void WorkerThread::run() {
    //    QElapsedTimer timer;
    //    timer.start();
    for(QUrl source : m_fileUrls){
        QImageReader imageReader(source.toLocalFile());
        int width = imageReader.size().width();
        int height = imageReader.size().height();

        _LOG() << "Before >>> Image " << source.toLocalFile() << ", width: " << width << ", height: " << height;

        if((float)width / height == (float)16/9)
            _LOG() << "good";
        else
        {
            _LOG() << "not good";
            width = height * (float)16 / 9;
            height *= (float) width / imageReader.size().width();
        }

        _LOG() << "After >>> Image " << source.toLocalFile()<< ", width: " << width << ", height: " << height;
        m_imageQueue->push(Image{width, height, source});
    }
    //    _LOG() << "The slow operation took" << timer.elapsed();
    emit calculateBlurSizeFinished();
}
