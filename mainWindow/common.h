#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QFileInfo>
#include <QStringLiteral>
#include <QCoreApplication>
#include <QDebug>

int registryWrite(QString& name, int width, int height);

int registryRead(QString& name, int& width, int& height);

#endif // COMMON_H
