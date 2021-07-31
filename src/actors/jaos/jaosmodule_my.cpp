#include "jaosmodule_my.h"

namespace ActorJAOS {

/* public slot */ void MyJAOSModuleBase::runKumir_jaos_internalCall_jaos_func_of_int_to_int_inner(const int function_number, const int arg)
{

    /** Коды функций: 
     * 
    0 - проверка механизма вызова
    1 - запусти яос (пока не делаем)
    2 - подключись к яос
    3 - отключись от яос (пока не делаем)
    4 - статус подключения

    5 и далее - вызвать пользовательскую функцию с таким номером */
    Q_ASSERT( asyncCallStatusValue != acsvRunning );
    asyncCallStatusValue = acsvRunning;
    lastErrorCodeValue = lecvErrorWithoutFurtherDetail;
    qDebug() << "entered runKumir_jaos_internalCall_jaos_func_of_int_to_int" << function_number;
    switch (function_number) {
        case 0: asyncCallStatusValue = acsvOk; lastErrorCodeValue = lecvOk; 
            internalAsyncCallIntResultValue = 81; break;
        case 1: asyncCallStatusValue = acsvDoneWithError; break;
        case 2: 
            qDebug() << "about to call echoClient.start";
            emit CallStart(arg);
            connectionStatusValue = csvConnecting;
            qDebug() << "called echoClient.start";
            break;
        case 3: 
            qDebug() << "about to call echoClient.startDisconnecting";
            if (connectionStatusValue == csvConnected) {
                emit MyJAOSModuleBaseSignalToDisconnectFromServer();
            } else {
                Q_ASSERT(connectionStatusValue == csvNoConnection);
            };
            break;
        case 4:
            qDebug() << "entered 4 (see ConnectionStatusValue)";
            if (!containerThread) {
                internalAsyncCallIntResultValue = connectionStatusValue;
            }
        default: 
            asyncCallStatusValue = acsvDoneWithError;
            break;
   }
}

void MyJAOSModuleBase::onEchoClientConnected() {
     qDebug() << "MyJAOSModule base: informed that echo client is connected";
     Q_ASSERT(connectionStatusValue = csvConnecting);
     Q_ASSERT(asyncCallStatusValue = acsvRunning);
     asyncCallStatusValue = acsvOk;
     lastErrorCodeValue = lecvOk;
     connectionStatusValue = csvConnected;
     }


}