#include "jaosmodule_my.h"

namespace ActorJAOS {

MyJAOSModuleBase::MyJAOSModuleBase(ExtensionSystem::KPlugin * parent)
    : JAOSModuleBase(parent)
{
    // echoClient = new EchoClient(this);
    // connect(this, &MyJAOSModuleBase::CallStart, echoClient, &EchoClient::start);
}


/* public slot */ void MyJAOSModuleBase::ConnectedToServer() {
        qDebug() << "Entering ConnectedToServer";
        connectionStatusValue = csvConnected;
        asyncCallStatusValue = acsvOk;
    }

    // typedef void (*HackConnectEventCallback)(QObject *thread, QObject *plugin);
    void HackConnectEvent(QObject *thread, QObject *plugin) {
        ContainerThread *tthread = dynamic_cast<ContainerThread *>(thread);
        MyJAOSModuleBase *tplugin = dynamic_cast<MyJAOSModuleBase *>(plugin);
        Q_ASSERT(tthread = tplugin->containerThread);
        tplugin->bindContainerThreadEvents();
    }
    

/* public slot */ void MyJAOSModuleBase::CallStart(const int arg) {
    containerThread = new ContainerThread(true,nullptr,&HackConnectEvent,this);
    /* Это не работает, не знаю, почему. 
    connect(containerThread,&ContainerThread::PleaseBindMyEvents,this,
        &MyJAOSModuleBase::bindContainerThreadEvents); */

        
        containerThread->start();
    };


/* public slot */ void MyJAOSModuleBase::bindContainerThreadEvents() {
    connect(containerThread->eventLoop,&QJakClientEventLoop::Connected, this, 
            &ActorJAOS::MyJAOSModuleBase::ConnectedToServer);
    connect(containerThread,&ContainerThread::eventLoopDonee, this, 
            &ActorJAOS::MyJAOSModuleBase::DisconnectedFromServer);
    /* connect(this, &ActorJAOS::MyJAOSModuleBase::MyJAOSModuleBaseSignalToDisconnectFromServer,
           containerThread->eventLoop, &QJakClientEventLoop::di  ContainerThread::startDisconnecting); */
    connect(this, &ActorJAOS::MyJAOSModuleBase::sendCallToServer,
            containerThread->eventLoop, &QJakClientEventLoop::sendCallToServer);
    connect(containerThread->eventLoop,&QJakClientEventLoop::GotReplyFromServer, this, 
            &ActorJAOS::MyJAOSModuleBase::onGotReplyFromServer);

    qDebug() << "connected thread's event loop events to plugin";
}

/* public slot */ void MyJAOSModuleBase::DisconnectedFromServer() {
        qDebug() << "Entering DisconnectedFromServer";
        containerThread = nullptr; // а кто его сотрёт? Не знаю. Пока пусть утекает. 
        connectionStatusValue = csvNoConnection;
        // это вообще-то не факт: могло произойти отключение не по нашей инициативе, 
        // а в это время был какой-то другой вызов. Т.е. нужно уметь при отключении понимать, 
        // это мы отключили или оно само отвалилось. Но пока пусть хоть так. 
        asyncCallStatusValue = acsvOk;
    }

/* public slot */ void MyJAOSModuleBase::onGotReplyFromServer(const int result) {
        asyncCallStatusValue = acsvOk;
        internalAsyncCallIntResultValue = result;        
    }


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
    qDebug() << "entered runKumir_jaos_internalCall_jaos_func_of_int_to_int" << function_number;
    Q_ASSERT( asyncCallStatusValue != acsvRunning );
    asyncCallStatusValue = acsvRunning;
    lastErrorCodeValue = lecvErrorWithoutFurtherDetail;
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
            asyncCallStatusValue = acsvOk;
            internalAsyncCallIntResultValue = connectionStatusValue;
            break;
        default: 
            emit sendCallToServer(function_number,arg);
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