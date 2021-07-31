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
    explicit MyJAOSModuleBase(ExtensionSystem::KPlugin * parent);

    void runKumir_jaos_internalCall_jaos_func_of_int_to_int_inner(const int function_number, const int arg);

    AsyncCallStatusValue asyncCallStatusValue = acsvOk; 
    int32_t lastErrorCodeValue = lecvErrorWithoutFurtherDetail; 
    int32_t internalAsyncCallIntResultValue; /* возвращаемое значение последнего вызова */
    ConnectionStatusValue connectionStatusValue = csvNoConnection;
    ContainerThread *containerThread;

public Q_SLOTS:
    void onEchoClientConnected(); 

    void ConnectedToServer();

    void CallStart(const int arg);

    void DisconnectedFromServer();

    void onGotReplyFromServer(const int result);

Q_SIGNALS:
    void MyJAOSModuleBaseSignalToDisconnectFromServer();
    void sendCallToServer(const int function_number, const int arg);
};

};

#endif