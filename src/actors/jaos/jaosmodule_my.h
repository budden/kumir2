#include "echoclient.h"

namespace ActorJAOS {


enum AsyncCallStatusValue {
 acsvRunning = 0,
 acsvDoneWithError = 1,
 acsvOk = 2
};

enum LastErrorCodeValue { lecvOk = 0, lecvErrorWithoutFurtherDetail = 1 };

enum ConnectionStatusValue { csvNoConnection = 0, 
 csvConnecting = 1,
 csvConnectionError = 2,
 csvConnected = 3,
 csvDisconnecting = 4,
 csvDisconnectError = 5}; 

class MyJAOSModuleBase
    : public JAOSModuleBase {


public:
    MyJAOSModuleBase(ExtensionSystem::KPlugin * parent)
    : JAOSModuleBase(parent)
{
}

    AsyncCallStatusValue asyncCallStatusValue = acsvOk; 
    LastErrorCodeValue lastErrorCodeValue = lecvErrorWithoutFurtherDetail; 
    int32_t internalAsyncCallIntResultValue; /* возвращаемое значение последнего вызова */
    ConnectionStatusValue connectionStatusValue = csvNoConnection;
    EchoClient *echoClient = NULL;

    };

}