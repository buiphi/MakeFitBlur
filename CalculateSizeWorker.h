#ifndef CalculateSizeWorker_H
#define CalculateSizeWorker_H

#include <QThread>
#include <ImageModel.h>
#include <queue>
#include <QUrl>

class CalculateSizeWorker : public QThread
{
    Q_OBJECT
public:
    CalculateSizeWorker(const QList<QUrl> &fileUrls, std::queue<Image> *imageQueue, QObject *parent = nullptr);

    void run() override;

signals:
    void calculateBlurSizeFinished();

private:
    QList<QUrl>   m_fileUrls;
    std::queue<Image> *m_imageQueue;
};

#endif // CalculateSizeWorker_H
