
#include "common.h"


void stringTohexString(QString& str, QString& hexStr)
{

}

int hexStringToString(QString& hexStr, QString& str)
{
    int ret = 0;
    bool ok;
    QByteArray retByte;
    hexStr = hexStr.trimmed();
    hexStr = hexStr.simplified();
    QStringList sl = hexStr.split(" ");

    foreach (QString s, sl)
    {
        if(!s.isEmpty())
        {
            char c = (s.toInt(&ok,16))&0xFF;
            if (ok)
            {
                retByte.append(c);
            }
            else
            {
                ret = -1;
            }
        }
    }

    str = retByte;

    return ret;
}

int hexStringToHexArray(QString& hexStr, QByteArray& arr)
{
    int ret = 0;
    bool ok;
    hexStr = hexStr.trimmed();
    hexStr = hexStr.simplified();
    QStringList sl = hexStr.split(" ");

    foreach (QString s, sl)
    {
        if(!s.isEmpty())
        {
            char c = (s.toInt(&ok,16))&0xFF;
            if (ok)
            {
                arr.append(c);
            }
            else
            {
                ret = -1;
            }
        }
    }

    return ret;
}

int hexArrayToString(QByteArray& hexArr, QString& str)
{
    int ret = 0;
    str = hexArr.toHex(' ').toLower();
    return ret;
}

// 注册表读写
// 键名称为示例
int registryWrite(QString& name, int width, int height)
{
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName();

    const QString key = QStringLiteral("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\") + fileName;
    QSettings settings(key, QSettings::NativeFormat);
    if (settings.status() != QSettings::NoError) {
        return -1;
    }
    //settings.beginGroup("res");
    // 写入键值对
    settings.setValue("Name", name);
    settings.setValue("Width", width);
    settings.setValue("Height", height);
    //settings.endGroup();
    return 0;
}

int registryRead(QString& name, int& width, int& height)
{
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName();

    const QString key = QStringLiteral("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\") + fileName;
    QSettings settings(key, QSettings::NativeFormat);
    if (settings.status() != QSettings::NoError) {
        return -1;
    }

    // 读键值对
    //settings.beginGroup("res");
    name = settings.value("Name").toString();
    width = settings.value("Width").toInt();
    height = settings.value("Height").toInt();
    //settings.endGroup();

    return 0;
}

