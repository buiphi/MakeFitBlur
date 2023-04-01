#include "SaveImageWorker.h"
#include "Logger.h"
#include <QImage>

SaveImageWorker::SaveImageWorker(const QString &name, const QImage &image)
    : m_name(name)
    , m_image(image)
{
    _LOG() << "constructor";
}

SaveImageWorker::~SaveImageWorker()
{
    _LOG() << "destructor";
}

void SaveImageWorker::run()
{
    _LOG() << "Starting save image to disk";
    m_image.save(m_name);
    _LOG() << "Save done" ;
    emit saveFinished();
}
