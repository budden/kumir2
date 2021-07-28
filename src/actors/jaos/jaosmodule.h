/*
This file is generated, but you can safely change it
until you run "gen_actor_source.py" with "--project" flag.

Generated file is just a skeleton for module contents.
You should change it corresponding to functionality.
*/

#ifndef JAOSMODULE_H
#define JAOSMODULE_H

// Base class include
#include "jaosmodulebase.h"

// Kumir includes
#include <kumir2-libs/extensionsystem/kplugin.h>

#include "jaosmodule_my.h"

// Qt includes
#include <QtCore>
#if QT_VERSION >= 0x050000
#   include <QtWidgets>
#else
#   include <QtGui>
#endif

namespace ActorJAOS {


class JAOSModule
    : public MyJAOSModuleBase
{
    Q_OBJECT
public /* methods */:
    JAOSModule(ExtensionSystem::KPlugin * parent);
    static QList<ExtensionSystem::CommandLineParameter> acceptableCommandLineParameters();
public Q_SLOTS:
    void changeGlobalState(ExtensionSystem::GlobalState old, ExtensionSystem::GlobalState current);
    void loadActorData(QIODevice * source);
    void reloadSettings(ExtensionSystem::SettingsPtr settings, const QStringList & keys);
    void reset();
    void terminateEvaluation();
    void runKumir_jaos_internalCall_jaos_func_of_int_to_int(const int function_number, const int arg);
    int runKumir_jaos_internalAsync_call_status();
    int runKumir_jaos_internalLast_error_code();
    int runKumir_jaos_internalAsync_call_int_result();



    /* ========= CLASS PRIVATE ========= */






};
        

} // namespace ActorJAOS

#endif // JAOSMODULE_H
