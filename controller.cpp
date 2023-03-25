#include "controller.h"
#include <QQuickView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QApplication>

Controller::Controller(QQmlApplicationEngine *engine)
    : QObject(engine)
    , m_engine(engine)
    , m_totalImage(0)
    , m_completedImage(0)
    , m_radius(60)
{
    m_engine->rootContext()->setContextProperty("myImageSource", QVariant(""));
    m_engine->rootContext()->setContextProperty("myImageWidth", QVariant(0));
    m_engine->rootContext()->setContextProperty("myImageHeight", QVariant(0));
    m_engine->rootContext()->setContextProperty("myTotal", QVariant(0));
    m_engine->rootContext()->setContextProperty("myCompleted", QVariant(0));
    m_engine->rootContext()->setContextProperty("controller", this);

}

Controller::~Controller()
{

}

void Controller::onFrameSwapped()
{
    qDebug() << "onFrameSwapped";

    save();
}

void Controller::open()
{
    qDebug() << "open " << QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

    QStringList fileNames = QFileDialog::getOpenFileNames(nullptr,
                                                          tr("Open Image"),
                                                          QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                          tr("Image Files (*.png *.jpg *.bmp)"));

    if(fileNames.isEmpty())
        return;

    m_totalImage = fileNames.size();
    m_engine->rootContext()->setContextProperty("myTotal", QVariant(m_totalImage));

    for(QString fileName : fileNames){

        qDebug() << fileName;

        QImage image;
        float width = 0;
        float height = 0;
        if(image.load(fileName))
        {
            qDebug() << "load image unsuccess " << image.width() << " : " << image.height();
            width = image.width();
            height = image.height();

            if((float)image.width() / (float)image.height() == (float)16/9)
                qDebug() << "good";
            else
            {
                qDebug() << "not good";
                width = (float)image.width() * 16 / 9;
                height = (float)image.height() * 16 / 9;

            }
        }

        MyImage myImage{fileName, width, height};
        m_myImageQueue.push(myImage);
    }
}

void Controller::save()
{
    QString nameBlur = m_selectedFolder + "/" + QFileInfo(m_myImageQueue.front().imageSource).baseName() + "_blur.png";
    qDebug() << "save " << nameBlur;

    QQuickWindow * wd = qobject_cast<QQuickWindow *>(m_imageWindow);
    bool ret = wd->grabWindow().save(nameBlur);
    if(ret)
    {
        qDebug() << "save success " << nameBlur;
        ++m_completedImage;
        m_engine->rootContext()->setContextProperty("myCompleted", QVariant(m_completedImage));
    }
    m_myImageQueue.pop();

    if(m_myImageQueue.empty())
    {
        qDebug() << "empty";
        return;
    }
    m_engine->rootContext()->setContextProperty("myImageSource", "file:///" + m_myImageQueue.front().imageSource);
    m_engine->rootContext()->setContextProperty("myImageWidth", m_myImageQueue.front().imageWidth);
    m_engine->rootContext()->setContextProperty("myImageHeight", m_myImageQueue.front().imageHeight);
}

void Controller::save(int radius)
{
    qDebug() << "save, radius: " << radius;
    if(m_myImageQueue.empty())
    {
        qDebug() << "empty !!!";
        return;
    }

    m_selectedFolder = QFileDialog::getExistingDirectory(nullptr, tr("Open Directory"),
                                                 QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    m_radius = radius;

    createImageWindow();


    m_engine->rootContext()->setContextProperty("myImageSource", "file:///" + m_myImageQueue.front().imageSource);
    m_engine->rootContext()->setContextProperty("myImageWidth", m_myImageQueue.front().imageWidth);
    m_engine->rootContext()->setContextProperty("myImageHeight", m_myImageQueue.front().imageHeight);
}

void Controller::createImageWindow()
{
    m_engine->rootContext()->setContextProperty("myRadius", m_radius);

    m_engine->load(QUrl("qrc:///blurimage.qml"));
    m_imageWindow = m_engine->rootObjects()[1];
    m_imageWindow->setParent(m_engine->rootObjects()[0]);

    QQuickWindow * wd = qobject_cast<QQuickWindow *>(m_imageWindow);

    connect(wd, &QQuickWindow::frameSwapped, this, &Controller::onFrameSwapped, Qt::QueuedConnection);
}

void Controller::attachNewImage()
{

}
