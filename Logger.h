#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QString>
#include <QFileInfo>

#include <sstream>

#define _LOG() qDebug() << baseMessage(__FILE__, __FUNCTION__, __LINE__)


inline QString baseMessage(const QString &file, const QString &func, int line){
    QFileInfo f(file);
    QString msg = "[" + f.baseName() + ":" + func + ":" + QString::number(line) + "]";
    return msg;
}

#endif // LOGGER_H



