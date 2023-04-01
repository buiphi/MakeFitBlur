#ifndef SAVEIMAGEWORKER_H
#define SAVEIMAGEWORKER_H

#include <QRunnable>
#include <QImage>

class SaveImageWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    SaveImageWorker(const QString &name, const QImage &image);
    virtual ~SaveImageWorker();

    void run() override;

signals:
    void saveFinished();

private:
    QString m_name;
    QImage m_image;

};

#endif // SAVEIMAGEWORKER_H
