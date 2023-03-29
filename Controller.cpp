#include "Controller.h"
#include <QQuickView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QApplication>
#include <QThread>
#include <Logger.h>
#include "WorkerThread.h"

Controller::Controller(MyImageModel *myImageModel, QQmlApplicationEngine *engine)
    : QObject(engine)
    , m_engine(engine)
    , m_totalImage(0)
    , m_completedImage(0)
    , m_radius(60)
    , m_myImageModel(myImageModel)
{
    m_engine->rootContext()->setContextProperty("myImage", m_myImageModel);
    m_engine->rootContext()->setContextProperty("controller", this);
}

Controller::~Controller()
{

}

void Controller::onFrameSwapped()
{
    _LOG() << "onFrameSwapped";

    save();
    m_myImageQueue.pop();
    update();
}

void Controller::open()
{
    _LOG() << "open " << QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

    QStringList fileNames = QFileDialog::getOpenFileNames(nullptr,
                                                          tr("Open Image"),
                                                          QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                          tr("Image Files (*.png *.jpg *.bmp)"));

    if(fileNames.isEmpty())
        return;

    m_totalImage = fileNames.size();
    m_myImageModel->setTotal(m_totalImage);

    calculateBlurSizeInAThread(fileNames);
}

void Controller::save()
{
    QString nameBlur = m_selectedFolder + "/" + QFileInfo(m_myImageQueue.front().source).baseName() + "_blur.png";

    if(QFile::exists(nameBlur))
    {
        _LOG() << "File exist";
        return;
    }

    _LOG() << "Starting save: " << nameBlur;

    bool result = m_imageWindow->grabWindow().save(nameBlur);
    if(result)
    {
        _LOG() << "Saved: " << nameBlur;
        ++m_completedImage;
        m_myImageModel->setCompleteTotal(m_completedImage);
    }
}

void Controller::save(int radius)
{
    if(m_myImageQueue.empty())
    {
        _LOG() << "empty !!!";
        return;
    }

    m_selectedFolder = QFileDialog::getExistingDirectory(nullptr, tr("Open Directory"),
                                                         QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    m_radius = radius;
    createImageWindow();
    m_myImageModel->update(m_myImageQueue.front().width
                           , m_myImageQueue.front().height
                           , "file:///" + m_myImageQueue.front().source);
}

void Controller::update()
{
    if(m_myImageQueue.empty())
    {
        _LOG() << "empty";
        return;
    }

    m_myImageModel->update(m_myImageQueue.front().width
                           , m_myImageQueue.front().height
                           , "file:///" + m_myImageQueue.front().source);
}

void Controller::onCalculateBlurSizeFinished()
{
    _LOG();
}

void Controller::createImageWindow()
{
    m_myImageModel->setRadius(m_radius);

    m_engine->load(QUrl("qrc:///BlurImage.qml"));
    m_imageWindow = dynamic_cast<QQuickWindow *>(m_engine->rootObjects()[1]);
    connect(m_imageWindow, &QQuickWindow::frameSwapped, this, &Controller::onFrameSwapped, Qt::QueuedConnection);
}

void Controller::calculateBlurSizeInAThread(const QStringList &fileNames)
{
    WorkerThread *workerThread = new WorkerThread(fileNames, &m_myImageQueue);
    connect(workerThread, &WorkerThread::calculateBlurSizeFinished, this, &Controller::onCalculateBlurSizeFinished);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}
