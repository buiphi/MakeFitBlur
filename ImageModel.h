#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QUrl>
#include <QObject>

struct Image{
    int width;
    int height;
    QUrl source;
};

class ImageModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)

    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int total READ total WRITE setTotal NOTIFY totalChanged)
    Q_PROPERTY(int completeTotal READ completeTotal WRITE setCompleteTotal NOTIFY completeTotalChanged)

    explicit ImageModel(QObject *parent = nullptr);

    int width() const;
    int height() const;
    QUrl source() const;

    int radius() const;
    int total() const;
    int completeTotal() const;

    void update(int width, int height, const QUrl &source);

public slots:
    void setWidth(int width);
    void setHeight(int height);
    void setSource(const QUrl &source);

    void setRadius(int radius);
    void setTotal(int total);
    void setCompleteTotal(int completeTotal);

signals:
    void widthChanged(int width);
    void heightChanged(int height);
    void sourceChanged(const QUrl &source);

    void radiusChanged(int radius);
    void totalChanged(int total);
    void completeTotalChanged(int completeTotal);

private:
    int m_width;
    int m_height;
    QUrl m_source;
    int m_radius;
    int m_total;
    int m_completeTotal;
};

#endif // IMAGEMODEL_H
