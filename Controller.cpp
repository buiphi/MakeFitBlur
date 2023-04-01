#include "Controller.h"
#include <QStandardPaths>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "Logger.h"
#include "CalculateSizeWorker.h"

Controller::Controller(ImageModel *imageModel, QQmlApplicationEngine *engine)
    : QObject(engine)
    , m_imageWindow(nullptr)
    , m_engine(engine)
    , m_totalImage(0)
    , m_completedImage(0)
    , m_radius(60)
    , m_imageModel(imageModel)
{
    m_engine->rootContext()->setContextProperty("imageModel", m_imageModel);
    m_engine->rootContext()->setContextProperty("controller", this);
}

Controller::~Controller()
{

}

void Controller::onFrameSwapped()
{
    _LOG() << "onFrameSwapped";

    if(m_imageQueue.empty())
    {
        _LOG() << "empty !!!";
        return;
    }

    save();
    m_imageQueue.pop();
    update();
}

void Controller::open(const QList<QUrl> &fileUrls)
{
    if(fileUrls.isEmpty())
        return;

    m_totalImage = fileUrls.size();
    m_imageModel->setTotal(m_totalImage);
    m_imageModel->setCompleteTotal(0);

    calculateBlurSize(fileUrls);
}

void Controller::save()
{
    if(m_imageQueue.empty())
    {
        _LOG() << "empty !!!";
        return;
    }

    QString nameBlur = m_selectedFolder + "/" + QFileInfo(m_imageQueue.front()->source.toString()).baseName() + ".png";

//    if(QFile::exists(nameBlur))
//    {
//        _LOG() << "File exist";
//        return;
//    }

    _LOG() << "Starting save: " << nameBlur;

    bool result = m_imageWindow->grabWindow().save(nameBlur);
    if(result)
    {
        _LOG() << "Saved";
        ++m_completedImage;
        m_imageModel->setCompleteTotal(m_completedImage);
    }
}

void Controller::save(const QUrl &folder)
{
    if(m_imageQueue.empty())
    {
        _LOG() << "empty !!!";
        return;
    }

    m_selectedFolder = folder.toLocalFile();
    createImageWindow();
    update();
}

void Controller::update()
{
    if(m_imageQueue.empty())
    {
        _LOG() << "empty";
        return;
    }

    m_imageModel->update(m_imageQueue.front()->width
                         , m_imageQueue.front()->height
                         , m_imageQueue.front()->source);
}

void Controller::onCalculateBlurSizeFinished()
{
    _LOG();
}

void Controller::createImageWindow()
{
    if(m_imageWindow == nullptr)
    {
        m_engine->load(QUrl("qrc:///BlurImage.qml"));
        m_imageWindow = dynamic_cast<QQuickWindow *>(m_engine->rootObjects()[1]);
        connect(m_imageWindow, &QQuickWindow::frameSwapped, this, &Controller::onFrameSwapped, Qt::QueuedConnection);
        connect(m_imageWindow, &QObject::destroyed, [&]{
            _LOG() << "destroyed";
        });
        connect(m_imageWindow, &QQuickWindow::visibleChanged , [&]{
            _LOG() << "visibleChanged";
        });
    }
    else
        m_imageWindow->setVisible(true);
}

void Controller::calculateBlurSize(const QList<QUrl> &fileUrls)
{
    CalculateSizeWorker *workerThread = new CalculateSizeWorker(fileUrls, &m_imageQueue);
    connect(workerThread, &CalculateSizeWorker::calculateBlurSizeFinished, this, &Controller::onCalculateBlurSizeFinished);
    connect(workerThread, &CalculateSizeWorker::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}
