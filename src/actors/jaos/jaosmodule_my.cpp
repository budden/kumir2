#include "jaosmodule_my.h"

namespace ActorJAOS {


void MyJAOSModuleBase::onEchoClientConnected() {
     qDebug() << "MyJAOSModule base: informed that echo client is connected";
     Q_ASSERT(connectionStatusValue = csvConnecting);
     Q_ASSERT(asyncCallStatusValue = acsvRunning);
     asyncCallStatusValue = acsvOk;
     lastErrorCodeValue = lecvOk;
     connectionStatusValue = csvConnected;
     }


}