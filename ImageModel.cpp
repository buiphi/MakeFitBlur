#include "ImageModel.h"

ImageModel::ImageModel(QObject *parent)
    : QObject(parent)
    , m_width(0)
    , m_height(0)
    , m_source("")
    , m_radius(60)
    , m_total(0)
    , m_completeTotal(0)
{

}

int ImageModel::width() const
{
    return m_width;
}

int ImageModel::height() const
{
    return m_height;
}

QUrl ImageModel::source() const
{
    return m_source;
}

int ImageModel::radius() const
{
    return m_radius;
}

int ImageModel::total() const
{
    return m_total;
}

int ImageModel::completeTotal() const
{
    return m_completeTotal;
}

void ImageModel::update(int width, int height, const QUrl &source)
{
    setWidth(width);
    setHeight(height);
    setSource(source);
}

void ImageModel::setWidth(int width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(m_width);
}

void ImageModel::setHeight(int height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged(m_height);
}

void ImageModel::setSource(const QUrl &source)
{
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged(m_source);
}

void ImageModel::setRadius(int radius)
{
    if (m_radius == radius)
        return;

    m_radius = radius;
    emit radiusChanged(m_radius);
}

void ImageModel::setTotal(int total)
{
    if (m_total == total)
        return;

    m_total = total;
    emit totalChanged(m_total);
}

void ImageModel::setCompleteTotal(int completeTotal)
{
    if (m_completeTotal == completeTotal)
        return;

    m_completeTotal = completeTotal;
    emit completeTotalChanged(m_completeTotal);
}
