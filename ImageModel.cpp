#include "ImageModel.h"

MyImageModel::MyImageModel(QObject *parent)
    : QObject(parent)
    , m_width(0)
    , m_height(0)
    , m_source("")
    , m_radius(60)
    , m_total(0)
    , m_completeTotal(0)
{

}

int MyImageModel::width() const
{
    return m_width;
}

int MyImageModel::height() const
{
    return m_height;
}

QString MyImageModel::source() const
{
    return m_source;
}

int MyImageModel::radius() const
{
    return m_radius;
}

int MyImageModel::total() const
{
    return m_total;
}

int MyImageModel::completeTotal() const
{
    return m_completeTotal;
}

void MyImageModel::update(int width, int height, const QString &source)
{
    setWidth(width);
    setHeight(height);
    setSource(source);
}

void MyImageModel::setWidth(int width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(m_width);
}

void MyImageModel::setHeight(int height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged(m_height);
}

void MyImageModel::setSource(QString source)
{
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged(m_source);
}

void MyImageModel::setRadius(int radius)
{
    if (m_radius == radius)
        return;

    m_radius = radius;
    emit radiusChanged(m_radius);
}

void MyImageModel::setTotal(int total)
{
    if (m_total == total)
        return;

    m_total = total;
    emit totalChanged(m_total);
}

void MyImageModel::setCompleteTotal(int completeTotal)
{
    if (m_completeTotal == completeTotal)
        return;

    m_completeTotal = completeTotal;
    emit completeTotalChanged(m_completeTotal);
}
