/**
 * Copyright (c) 2017-present, Status Research and Development GmbH.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "reactnativeconfig.h"
#include "bridge.h"
#include "eventdispatcher.h"

#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

namespace {
struct RegisterQMLMetaType {
    RegisterQMLMetaType() {
        qRegisterMetaType<ReactNativeConfig*>();
    }
} registerMetaType;
} // namespace

class ReactNativeConfigPrivate {
public:
    Bridge* bridge = nullptr;
};

ReactNativeConfig::ReactNativeConfig(QObject* parent) : QObject(parent), d_ptr(new ReactNativeConfigPrivate) {}

ReactNativeConfig::~ReactNativeConfig() {}

void ReactNativeConfig::setBridge(Bridge* bridge) {
    Q_D(ReactNativeConfig);
    d->bridge = bridge;
}

QString ReactNativeConfig::moduleName() {
    return "ReactNativeConfig";
}

QList<ModuleMethod*> ReactNativeConfig::methodsToExport() {
    return QList<ModuleMethod*>{};
}

QVariantMap ReactNativeConfig::constantsToExport() {
    const QString Delimiter = "=";
    QString defaultEnvFile = QCoreApplication::applicationDirPath() + "/../../.env";
    QVariantMap config;
    QFile file(defaultEnvFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ReactNativeConfig Can't open config file " << file.fileName() << " Error code: " << file.error();
        return QVariantMap();
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = file.readLine();
        if (line.count(Delimiter) == 1) {
            QStringList values = line.split(Delimiter);
            if (values.size() == 2) {
                config[values[0]] = values[1];
            }
        }

    }

    file.close();
    return config;
}
