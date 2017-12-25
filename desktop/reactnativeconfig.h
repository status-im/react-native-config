/**
 * Copyright (c) 2017-present, Status Research and Development GmbH.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#ifndef REACTNATIVECONFIG_H
#define REACTNATIVECONFIG_H

#include "moduleinterface.h"

#include <QVariantMap>

class ReactNativeConfigPrivate;
class ReactNativeConfig : public QObject, public ModuleInterface {
    Q_OBJECT
    Q_INTERFACES(ModuleInterface)

    Q_DECLARE_PRIVATE(ReactNativeConfig)

public:
    Q_INVOKABLE ReactNativeConfig(QObject* parent = 0);
    ~ReactNativeConfig();

    void setBridge(Bridge* bridge) override;

    QString moduleName() override;
    QList<ModuleMethod*> methodsToExport() override;
    QVariantMap constantsToExport() override;

private:
    QScopedPointer<ReactNativeConfigPrivate> d_ptr;
};

#endif // REACTNATIVECONFIG_H
