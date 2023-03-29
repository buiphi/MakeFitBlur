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
    Controller(MyImageModel *myImageModel,QQmlApplicationEngine *engine);

    ~Controller();

signals:
    void calculateBlurSize(const QStringList &fileNames);

public slots:
    void onFrameSwapped();
    void open();
    void save();
    void save(int radius);

    void update();
    void onCalculateBlurSizeFinished();

private:
    QQuickWindow *m_imageWindow;
    QQmlApplicationEngine *m_engine;

    int m_totalImage;
    int m_completedImage;
    QString m_selectedFolder;
    int m_radius;

    std::queue<MyImage> m_myImageQueue;
    MyImageModel *m_myImageModel;
private:
    void createImageWindow();
    void calculateBlurSizeInAThread(const QStringList &fileNames);

};

#endif // CONTROLLER_H
