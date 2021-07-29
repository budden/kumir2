#ifndef JAOSMODULE_MY_H
#define JAOSMODULE_MY_H

#include "echoclient.h"

#include "jaosmodulebase.h"

// Kumir includes
#include <kumir2-libs/extensionsystem/kplugin.h>

namespace ActorJAOS {


enum AsyncCallStatusValue {
 acsvRunning = 0,
 acsvDoneWithError = 1,
 acsvOk = 2
};

const int32_t lecvOk = 0, lecvErrorWithoutFurtherDetail = 1;

enum ConnectionStatusValue { csvNoConnection = 0, 
 csvConnecting = 1,
 csvConnectionError = 2,
 csvConnected = 3,
 csvDisconnecting = 4,
 csvDisconnectError = 5}; 

class MyJAOSModuleBase
    : public JAOSModuleBase 

{

Q_OBJECT

public:
    MyJAOSModuleBase(ExtensionSystem::KPlugin * parent)
    : JAOSModuleBase(parent)
{
    // echoClient = new EchoClient(this);
    // connect(this, &MyJAOSModuleBase::CallStart, echoClient, &EchoClient::start);
}

    void runKumir_jaos_internalCall_jaos_func_of_int_to_int_inner(const int function_number, const int arg);

    AsyncCallStatusValue asyncCallStatusValue = acsvOk; 
    int32_t lastErrorCodeValue = lecvErrorWithoutFurtherDetail; 
    int32_t internalAsyncCallIntResultValue; /* возвращаемое значение последнего вызова */
    ConnectionStatusValue connectionStatusValue = csvNoConnection;
    ContainerThread *containerThread;

public Q_SLOTS:
    void onEchoClientConnected(); 

    void CallStart(const int arg) {
        containerThread = new ContainerThread(true,nullptr,nullptr);
    // a.connect(thread,&ContainerThread::onEventLoopExitingg,&a,&QCoreApplication::quit);
        containerThread->start();
    };
};

};

#endif