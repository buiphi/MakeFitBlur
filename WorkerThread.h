#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <ImageModel.h>
#include <queue>
#include <QUrl>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(const QList<QUrl> &fileUrls, std::queue<Image> *imageQueue, QObject *parent = nullptr);

    void run() override;

signals:
    void calculateBlurSizeFinished();

private:
    QList<QUrl>   m_fileUrls;
    std::queue<Image> *m_imageQueue;
};

#endif // WORKERTHREAD_H
