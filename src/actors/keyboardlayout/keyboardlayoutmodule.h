/*
This file is generated, but you can safely change it
until you run "gen_actor_source.py" with "--project" flag.

Generated file is just a skeleton for module contents.
You should change it corresponding to functionality.
*/

#ifndef KEYBOARDLAYOUTMODULE_H
#define KEYBOARDLAYOUTMODULE_H

// Base class include
#include "keyboardlayoutmodulebase.h"

// Kumir includes
#include <kumir2-libs/extensionsystem/kplugin.h>

// Qt includes
#include <QtCore>
#if QT_VERSION >= 0x050000
#   include <QtWidgets>
#else
#   include <QtGui>
#endif

namespace ActorKeyboardLayout {

class KeyboardLayoutModule
    : public KeyboardLayoutModuleBase
{
    Q_OBJECT
public /* methods */:
    KeyboardLayoutModule(ExtensionSystem::KPlugin * parent);
    static QList<ExtensionSystem::CommandLineParameter> acceptableCommandLineParameters();
    QWidget* mainWidget() const;
    QWidget* pultWidget() const;
public Q_SLOTS:
    void changeGlobalState(ExtensionSystem::GlobalState old, ExtensionSystem::GlobalState current);
    void loadActorData(QIODevice * source);
    void reloadSettings(ExtensionSystem::SettingsPtr settings, const QStringList & keys);
    void reset();
    void setAnimationEnabled(bool enabled);
    void terminateEvaluation();
    void finalizeRun();
    QString initialize(const QStringList &configurationParameters, const ExtensionSystem::CommandLine &runtimeParameters);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    struct KeyInfo {
    public:
        KeyInfo() {}
        KeyInfo(const QString &normalChar, const QString &modifiedChar):
            normalChar_(normalChar),
            modifiedChar_(modifiedChar)
        {

        }

        QString normalChar() {
            return normalChar_;
        }

        QString modifiedChar() {
            return modifiedChar_;
        };

    private:
        QString normalChar_;
        QString modifiedChar_;
    };

    bool isKeyModifierPressed;
    bool isLayoutModified;

    QKeyEvent *createKeyEventByCurrentLayout(QKeyEvent *keyEvent);
    bool checkCapsLock();

};
        

} // namespace ActorKeyboardLayout

#endif // KEYBOARDLAYOUTMODULE_H
