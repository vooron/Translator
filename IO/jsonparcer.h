#ifndef JSONPARCER_H
#define JSONPARCER_H

#include <string>
#include "QString"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QJsonValue"
#include "QFile"

using namespace std;

class JsonParcer
{

    QJsonDocument val;

public:

    static QJsonDocument getDocument(QString fileName) {
        QString val;
              QFile file;
              file.setFileName(fileName);
              file.open(QIODevice::ReadOnly | QIODevice::Text);
              val = file.readAll();
              file.close();
              return QJsonDocument::fromJson(val.toUtf8());
    }


    static QJsonObject getObject(QString fileName) {
        return getDocument(fileName).object();
    }


    static QJsonArray getArray(QString fileName) {
        return getDocument(fileName).array();
    }

};

#endif // JSONPARCER_H
