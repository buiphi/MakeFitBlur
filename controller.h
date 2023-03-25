#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QQuickWindow>
#include <QQuickView>
#include <stack>
#include <QTimer>
#include <QQmlApplicationEngine>
#include <queue>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QQmlApplicationEngine *engine);

    ~Controller();

public slots:
    void onFrameSwapped();
    void open();
    void save();
    void save(int radius);


private:
    QObject *m_imageWindow;
    QQmlApplicationEngine *m_engine;

    int m_totalImage;
    int m_completedImage;
    QString m_selectedFolder;
    int m_radius;

    struct MyImage{
        QString imageSource;
        float imageWidth;
        float imageHeight;
    };
    std::queue<MyImage> m_myImageQueue;

private:
    void createImageWindow();
    void attachNewImage();
};

#endif // CONTROLLER_H
