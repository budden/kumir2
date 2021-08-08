/*
This file is generated, but you can safely change it
until you run "gen_actor_source.py" with "--project" flag.

Generated file is just a skeleton for module contents.
You should change it corresponding to functionality.
*/

// Self include
#include "keyboardlayoutmodule.h"

// Kumir includes
#include <kumir2-libs/extensionsystem/kplugin.h>

// Qt includes
#include <QtCore>
#if QT_VERSION >= 0x050000
#   include <QtWidgets>
#else
#   include <QtGui>
#endif

#include <QMap>


#ifdef Q_OS_WIN32
# include <windows.h>
#else
#  include <X11/XKBlib.h>
# undef KeyPress
# undef KeyRelease
# undef FocusIn
# undef FocusOut
// #undef those Xlib #defines that conflict with QEvent::Type enum
#endif

namespace ActorKeyboardLayout {

KeyboardLayoutModule::KeyboardLayoutModule(ExtensionSystem::KPlugin * parent)
    : KeyboardLayoutModuleBase(parent),
      isKeyModifierPressed(false),
      isLayoutModified(false)
{
    // Module constructor, called once on plugin load
    // TODO implement me
}

/* public static */ QList<ExtensionSystem::CommandLineParameter> KeyboardLayoutModule::acceptableCommandLineParameters()
{
    // See "src/shared/extensionsystem/commandlineparameter.h" for constructor details
    return QList<ExtensionSystem::CommandLineParameter>();
}

/* public slot */ void KeyboardLayoutModule::changeGlobalState(ExtensionSystem::GlobalState old, ExtensionSystem::GlobalState current)
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

    if (Shared::PluginInterface::GS_Running == old) {
        if (Shared::PluginInterface::GS_Observe == current || Shared::PluginInterface::GS_Unlocked == current) {
            finalizeRun();
        }
    }
}

/* public slot */ void KeyboardLayoutModule::loadActorData(QIODevice * source)
{
    // Set actor specific data (like environment)
    // The source should be ready-to-read QIODevice like QBuffer or QFile
    Q_UNUSED(source);  // By default do nothing

}

/* public */ QWidget* KeyboardLayoutModule::mainWidget() const
{
    // Returns module main view widget, or nullptr if there is no any views
    // NOTE: the method is const and might be called at any time,
    //       so DO NOT create widget here, just return!
    // TODO implement me
    return nullptr;
}

/* public */ QWidget* KeyboardLayoutModule::pultWidget() const
{
    // Returns module control view widget, or nullptr if there is no control view
    // NOTE: the method is const and might be called at any time,
    //       so DO NOT create widget here, just return!
    // TODO implement me
    return nullptr;
}

/* public slot */ void KeyboardLayoutModule::reloadSettings(ExtensionSystem::SettingsPtr settings, const QStringList & keys)
{
    // Updates setting on module load, workspace change or appliyng settings dialog.
    // If @param keys is empty -- should reload all settings, otherwise load only setting specified by @param keys
    // TODO implement me
    Q_UNUSED(settings);  // Remove this line on implementation
    Q_UNUSED(keys);  // Remove this line on implementation
}

/* public slot */ void KeyboardLayoutModule::reset()
{
    qApp->installEventFilter(this);
}

/* public slot */ void KeyboardLayoutModule::setAnimationEnabled(bool enabled)
{
    // Sets GUI animation flag on run
    // NOTE this method just setups a flag and might be called anytime, even module not needed
    // TODO implement me
    Q_UNUSED(enabled);  // Remove this line on implementation
}

/* public slot */ void KeyboardLayoutModule::terminateEvaluation()
{
    // Called on program interrupt to ask long-running module's methods
    // to stop working
    // TODO implement me
}

void KeyboardLayoutModule::finalizeRun()
{
    qApp->removeEventFilter(this);
}

QString KeyboardLayoutModule::initialize(const QStringList &configurationParameters, const ExtensionSystem::CommandLine &runtimeParameters)
{
    Q_UNUSED(configurationParameters);
    Q_UNUSED(runtimeParameters);

    reset();
    return "";
}

bool KeyboardLayoutModule::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyRelease && event->spontaneous()) {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Space && !keyEvent->isAutoRepeat()) {
            if (!isLayoutModified) {
                QKeyEvent *newKeyEvent = new QKeyEvent(QEvent::KeyPress,
                                                       Qt::Key_Space,
                                                       keyEvent->modifiers(),
                                                       QChar(Qt::Key_Space));
                QApplication::postEvent(obj, newKeyEvent);
            }

            isKeyModifierPressed = false;
            isLayoutModified = false;
            return true;
        }
    }

    if (event->type() == QEvent::KeyPress && event->spontaneous()) {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Space) {
            isKeyModifierPressed = true;
            return true;
        }

        if (isKeyModifierPressed) {
            isLayoutModified = true;
        }

        QKeyEvent *newKeyEvent = createKeyEventByCurrentLayout(keyEvent);
        if (newKeyEvent != nullptr) {
            QApplication::postEvent(obj, newKeyEvent);
            return true;
        }
    }

    return QObject::eventFilter(obj, event);
}



QKeyEvent *KeyboardLayoutModule::createKeyEventByCurrentLayout(QKeyEvent *keyEvent)
{
    static const QMap<int, QPair<KeyInfo, KeyInfo>> CODES = {
        {Qt::Key_Q, { {"q", "Q"}, {"й", "Й"} }},
        {Qt::Key_W, { {"w", "W"}, {"ц", "Ц"} }},
        {Qt::Key_E, { {"e", "E"}, {"у", "У"} }},
        {Qt::Key_R, { {"r", "R"}, {"к", "К"} }},
        {Qt::Key_T, { {"t", "T"}, {"е", "Е"} }},
        {Qt::Key_Y, { {"y", "Y"}, {"н", "Н"} }},
        {Qt::Key_U, { {"u", "U"}, {"г", "Г"} }},
        {Qt::Key_I, { {"i", "I"}, {"ш", "Ш"} }},
        {Qt::Key_O, { {"o", "O"}, {"щ", "Щ"} }},
        {Qt::Key_P, { {"p", "P"}, {"з", "З"} }},
        {Qt::Key_Ucircumflex, { {"[", "{"}, {"х", "Х"} }},
        {Qt::Key_Yacute, { {"]", "}"}, {"ъ", "Ъ"} }},
        {Qt::Key_Udiaeresis, { {"\\", "|"}, {"\\", "/"} }},

        {Qt::Key_A, { {"a", "A"}, {"ф", "Ф"} }},
        {Qt::Key_S, { {"s", "S"}, {"ы", "Ы"} }},
        {Qt::Key_D, { {"d", "D"}, {"в", "В"} }},
        {Qt::Key_F, { {"f", "F"}, {"а", "А"} }},
        {Qt::Key_G, { {"g", "G"}, {"п", "П"} }},
        {Qt::Key_H, { {"h", "H"}, {"р", "Р"} }},
        {Qt::Key_J, { {"j", "J"}, {"о", "О"} }},
        {Qt::Key_K, { {"k", "K"}, {"л", "Л"} }},
        {Qt::Key_L, { {"l", "L"}, {"д", "Д"} }},
        {Qt::Key_masculine, { {";", ":"}, {"ж", "Ж"} }},
        {Qt::Key_THORN, { {"'", "\""}, {"э", "Э"} }},

        {Qt::Key_Z, { {"z", "Z"}, {"я", "Я"} }},
        {Qt::Key_X, { {"x", "X"}, {"ч", "Ч"} }},
        {Qt::Key_C, { {"c", "C"}, {"с", "С"} }},
        {Qt::Key_V, { {"v", "V"}, {"м", "М"} }},
        {Qt::Key_B, { {"b", "B"}, {"и", "И"} }},
        {Qt::Key_N, { {"n", "N"}, {"т", "Т"} }},
        {Qt::Key_M, { {"m", "M"}, {"ь", "Ь"} }},
        {Qt::Key_onequarter, { {",", "<"}, {"б", "Б"} }},
        {Qt::Key_threequarters, { {".", ">"}, {"ю", "Ю"} }},
        {Qt::Key_questiondown, { {"/", "?"}, {".", ","} }},

        {Qt::Key_Agrave, { {"`", "~"}, {"ё", "Ё"} }},
        {Qt::Key_2, { {"2", "@"}, {"2", "\""} }},
        {Qt::Key_3, { {"3", "#"}, {"3", "№"} }},
        {Qt::Key_4, { {"4", "$"}, {"4", ";"} }},
        {Qt::Key_6, { {"6", "^"}, {"6", ":"} }},
        {Qt::Key_7, { {"7", "&"}, {"7", "?"} }},
    };

    if (!CODES.contains(keyEvent->nativeVirtualKey())) {
        return nullptr;
    }

    auto pairChar = CODES[keyEvent->nativeVirtualKey()];
    bool isModifiers = keyEvent->modifiers() & Qt::ShiftModifier;
    isModifiers = isModifiers ? !checkCapsLock() : checkCapsLock();

    if (!isLayoutModified) {
        return new QKeyEvent(QEvent::KeyPress,
                             keyEvent->nativeVirtualKey(),
                             keyEvent->modifiers(),
                             isModifiers ? pairChar.second.modifiedChar() : pairChar.second.normalChar());
    }
    else {
        return new QKeyEvent(QEvent::KeyPress,
                             keyEvent->nativeVirtualKey(),
                             keyEvent->modifiers(),
                             isModifiers ? pairChar.first.modifiedChar() : pairChar.first.normalChar());
    }
}

bool KeyboardLayoutModule::checkCapsLock()
{
#ifdef Q_OS_WIN32
    return GetKeyState(VK_CAPITAL) == 1;
#else
    Display * d = XOpenDisplay((char*)0);
    bool caps_state = false;
    if (d)
    {
        unsigned n;
        XkbGetIndicatorState(d, XkbUseCoreKbd, &n);
        caps_state = (n & 0x01) == 1;
    }
    return caps_state;
#endif
}



} // namespace ActorKeyboardLayout
