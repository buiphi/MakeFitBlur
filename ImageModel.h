#ifndef MYIMAGEMODEL_H
#define MYIMAGEMODEL_H

#include <QObject>

struct MyImage{
    int width;
    int height;
    QString source;
};

class MyImageModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int total READ total WRITE setTotal NOTIFY totalChanged)
    Q_PROPERTY(int completeTotal READ completeTotal WRITE setCompleteTotal NOTIFY completeTotalChanged)

    explicit MyImageModel(QObject *parent = nullptr);

    int width() const;
    int height() const;
    QString source() const;

    int radius() const;
    int total() const;
    int completeTotal() const;

    void update(int width, int height, const QString &source);

public slots:
    void setWidth(int width);
    void setHeight(int height);
    void setSource(QString source);

    void setRadius(int radius);
    void setTotal(int total);
    void setCompleteTotal(int completeTotal);

signals:
    void widthChanged(int width);
    void heightChanged(int height);
    void sourceChanged(QString source);

    void radiusChanged(int radius);
    void totalChanged(int total);
    void completeTotalChanged(int completeTotal);

private:
    int m_width;
    int m_height;
    QString m_source;
    int m_radius;
    int m_total;
    int m_completeTotal;
};

#endif // MYIMAGEMODEL_H
