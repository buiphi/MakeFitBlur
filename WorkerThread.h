#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <ImageModel.h>
#include <queue>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(const QStringList &fileNames, std::queue<MyImage> *myImageQueue, QObject *parent = nullptr);

    void run() override;

signals:
    void calculateBlurSizeFinished();

private:
    QStringList   m_fileNames;
    std::queue<MyImage> *m_myImageQueue;
};

#endif // WORKERTHREAD_H
