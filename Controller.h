#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QQuickWindow>
#include <QQuickView>
#include <stack>
#include <QTimer>
#include <QQmlApplicationEngine>
#include <queue>
#include "ImageModel.h"
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(ImageModel *ImageModel,QQmlApplicationEngine *engine);
    ~Controller();

signals:
    void calculateBlurSize(const QStringList &fileNames);
    void saveToDisk(const QString &name, const QImage &image);

public slots:
    void onFrameSwapped();

    void onCalculateBlurSizeFinished();
    void saveFinished();

public:
    Q_INVOKABLE void open(const QList<QUrl> &fileUrls);
    Q_INVOKABLE void save(const QUrl &folder);

    void save();
    void updateModel();

private:
    QQuickWindow *m_imageWindow;
    QQmlApplicationEngine *m_engine;

    QThread m_workerThread;

    int m_totalImage;
    int m_completedImage;
    QString m_selectedFolder;
    int m_radius;

    std::queue<Image> m_imageQueue;
    ImageModel *m_imageModel;

private:
    void createImageWindow();
    void calculateBlurSize(const QList<QUrl> &fileUrls);

};

#endif // CONTROLLER_H
