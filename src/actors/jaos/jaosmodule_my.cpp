#include "jaosmodule_my.h"

namespace ActorJAOS {

MyJAOSModuleBase::MyJAOSModuleBase(ExtensionSystem::KPlugin * parent)
    : JAOSModuleBase(parent)
{
    // echoClient = new EchoClient(this);
    // connect(this, &MyJAOSModuleBase::CallStart, echoClient, &EchoClient::start);
}

    AsyncCallStatusValue MyJAOSModuleBase::asyncCallStatusValue() {
        if (containerThread == nullptr) { 
            return acsvDisconnected;
        }
        QJakClientEventLoop *el = containerThread->eventLoop;
        if (el == nullptr) {
            return acsvDisconnected;
        }
        return el->asyncCallStatusValue;
    }
    
    void MyJAOSModuleBase::ensureSignalsToEventLoopAreBound() {
        Q_ASSERT(containerThread != nullptr);
        QJakClientEventLoop *el = containerThread->eventLoop;
        Q_ASSERT(el != nullptr);
        if (! el -> signalsFromPluginAreBoundP) { 
            el->connect(this,&MyJAOSModuleBase::sendCallToServer,el,
                &QJakClientEventLoop::sendCallToServer);
            el->connect(this,&MyJAOSModuleBase::MyJAOSModuleBaseSignalToDisconnectFromServer,
            el, &QJakClientEventLoop::startDisconnecting);
        }
    }


    ConnectionStatusValue MyJAOSModuleBase::connectionStatusValue() {
        if (containerThread == nullptr) { 
            return csvNoConnection;
        }
        QJakClientEventLoop *el = containerThread->eventLoop;
        if (el == nullptr) {
            return csvNoConnection;
        }
        return el->connectionStatusValue;
    }

    int MyJAOSModuleBase::internalAsyncCallIntResultValue() {
        Q_ASSERT(containerThread != nullptr);
        QJakClientEventLoop *el = containerThread->eventLoop;
        Q_ASSERT(el != nullptr);
        return el->lastCallResult; 
    }

 

/* public slot */ void MyJAOSModuleBase::CallStart(const int arg) {
    containerThread = new ContainerThread(true,nullptr);
    containerThread->start();
}

/* public slot */ void MyJAOSModuleBase::runKumir_jaos_internalCall_jaos_func_of_int_to_int_inner(const int function_number, const int arg)
{

    /** Коды функций: 
     * 
    1 - запусти яос (пока не делаем)
    2 - подключись к яос
    3 - отключись от яос (пока не делаем)
    // 4 - статус подключения - нет, надо сделать отдельную ф-ю на уровне кумира, но и без того плохо!

    5 и далее - вызвать пользовательскую функцию с таким номером */
    qDebug() << "entered runKumir_jaos_internalCall_jaos_func_of_int_to_int" << function_number;
    Q_ASSERT( asyncCallStatusValue() != acsvRunning );
    lastErrorCodeValue = lecvErrorWithoutFurtherDetail;
    switch (function_number) {
        case 1: break;
        case 2: 
            qDebug() << "about to emit signal to start connection thread and connect to server";
            emit CallStart(arg);
            break;
        case 3: 
            qDebug() << "about to emit MyJAOSModuleBaseSignalToDisconnectFromServer";
            if (connectionStatusValue() == csvConnected) {
                ensureSignalsToEventLoopAreBound();
                emit MyJAOSModuleBaseSignalToDisconnectFromServer();
            } else {
                Q_ASSERT(connectionStatusValue() == csvNoConnection);
            };
            break;
        default: 
            ensureSignalsToEventLoopAreBound();
            emit sendCallToServer(function_number,arg);
            break;
   }
}

}