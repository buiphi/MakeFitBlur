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

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(ImageModel *ImageModel,QQmlApplicationEngine *engine);

    ~Controller();

signals:
    void calculateBlurSize(const QStringList &fileNames);

public slots:
    void onFrameSwapped();
    void open(const QList<QUrl> &fileUrls);
    void save();
    void save(const QUrl &folder);

    void update();
    void onCalculateBlurSizeFinished();

private:
    QQuickWindow *m_imageWindow;
    QQmlApplicationEngine *m_engine;

    int m_totalImage;
    int m_completedImage;
    QString m_selectedFolder;
    int m_radius;

    std::queue<Image> m_imageQueue;
    ImageModel *m_imageModel;
private:
    void createImageWindow();
    void calculateBlurSizeInAThread(const QList<QUrl> &fileUrls);

};

#endif // CONTROLLER_H
