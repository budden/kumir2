/*
This file is generated, but you can safely change it
until you run "gen_actor_source.py" with "--project" flag.

Generated file is just a skeleton for module contents.
You should change it corresponding to functionality.
*/

// Self include
#include "jaosmodule.h"

// Kumir includes
#include <kumir2-libs/extensionsystem/kplugin.h>

// Qt includes
#include <QtCore>
#if QT_VERSION >= 0x050000
#   include <QtWidgets>
#else
#   include <QtGui>
#endif

namespace ActorJAOS {

JAOSModule::JAOSModule(ExtensionSystem::KPlugin * parent)
    : MyJAOSModuleBase(parent)
{
    // Module constructor, called once on plugin load
    // TODO implement me
}

/* public static */ QList<ExtensionSystem::CommandLineParameter> JAOSModule::acceptableCommandLineParameters()
{
    // See "src/shared/extensionsystem/commandlineparameter.h" for constructor details
    return QList<ExtensionSystem::CommandLineParameter>();
}

/* public slot */ void JAOSModule::changeGlobalState(ExtensionSystem::GlobalState old, ExtensionSystem::GlobalState current)
{
    // Called when changed kumir state. The states are defined as enum ExtensionSystem::GlobalState:
    /*
    namespace ExtensionSystem {
        enum GlobalState {
            GS_Unlocked, // Edit mode
            GS_Observe, // Observe mode
            GS_Running, // Running mode
            GS_Input,  // User input required
            GS_Pause  // Running paused
        };
    }
    */
    // TODO implement me
    using namespace ExtensionSystem;  // not to write "ExtensionSystem::" each time in this method scope
    Q_UNUSED(old);  // Remove this line on implementation
    Q_UNUSED(current);  // Remove this line on implementation
}

/* public slot */ void JAOSModule::loadActorData(QIODevice * source)
{
    // Set actor specific data (like environment)
    // The source should be ready-to-read QIODevice like QBuffer or QFile
    Q_UNUSED(source);  // By default do nothing

}





/* public slot */ void JAOSModule::reloadSettings(ExtensionSystem::SettingsPtr settings, const QStringList & keys)
{
    // Updates setting on module load, workspace change or appliyng settings dialog.
    // If @param keys is empty -- should reload all settings, otherwise load only setting specified by @param keys
    // TODO implement me
    Q_UNUSED(settings);  // Remove this line on implementation
    Q_UNUSED(keys);  // Remove this line on implementation
}

/* public slot */ void JAOSModule::reset()
{
    // Resets module to initial state before program execution
    // TODO implement me
}



/* public slot */ void JAOSModule::terminateEvaluation()
{
    // Called on program interrupt to ask long-running module's methods
    // to stop working
    // TODO implement me
}

/* public slot */ void JAOSModule::runKumir_jaos_internalCall_jaos_func_of_int_to_int(const int function_number, const int arg)
{
    /* алг кумир_яос_внутр вызови_функцию_из_цел_в_цел(цел function_number, цел arg) */
    runKumir_jaos_internalCall_jaos_func_of_int_to_int_inner(function_number, arg);
   
}

/* public slot */ int JAOSModule::runKumir_jaos_internalAsync_call_status()
{
    /* алг цел кумир_яос_внутр статус_асинхронного_вызова */
    return asyncCallStatusValue();
}

/* public slot */ int JAOSModule::runKumir_jaos_internalLast_error_code()
{
    /* алг цел кумир_яос_внутр код_последней_ошибки */
    // TODO implement me
    return int(lastErrorCodeValue);
    
}

/* public slot */ int JAOSModule::runKumir_jaos_internalAsync_call_int_result()
{
    /* алг цел кумир_яос_внутр результат_асинхронного_вызова_цел */
    qDebug() << "entered runKumir_jaos_internalAsyncCallIntResult";
    // TODO implement me
    return internalAsyncCallIntResultValue();
    
}



} // namespace ActorJAOS
