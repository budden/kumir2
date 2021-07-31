#ifndef JAOSMODULE_MY_H
#define JAOSMODULE_MY_H

#include "echoclient.h"

#include "jaosmodulebase.h"

// Kumir includes
#include <kumir2-libs/extensionsystem/kplugin.h>

namespace ActorJAOS {



const int32_t lecvOk = 0, lecvErrorWithoutFurtherDetail = 1;

class MyJAOSModuleBase
    : public JAOSModuleBase 

{

Q_OBJECT

public:
    explicit MyJAOSModuleBase(ExtensionSystem::KPlugin * parent);

    void runKumir_jaos_internalCall_jaos_func_of_int_to_int_inner(const int function_number, const int arg);

    AsyncCallStatusValue asyncCallStatusValue(); // напрямую читаем из полей цикла событий треда связи с сервером
    ConnectionStatusValue connectionStatusValue(); 
    int32_t lastErrorCodeValue = lecvErrorWithoutFurtherDetail; 
    int internalAsyncCallIntResultValue(); /* возвращаемое значение последнего вызова */
    ContainerThread *containerThread = nullptr;

public Q_SLOTS:
    void CallStart(const int arg);

Q_SIGNALS:
    void MyJAOSModuleBaseSignalToDisconnectFromServer();
    void sendCallToServer(const int function_number, const int arg);
};

};

#endif