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
#include <QEvent>

#ifdef Q_OS_WIN32
#   include <windows.h>
#endif

#if defined(Q_WS_X11) || defined(Q_OS_LINUX)
#   include <QX11Info>
#   include <X11/XKBlib.h>
#   include <X11/Xatom.h>
# undef KeyPress
# undef KeyRelease
#endif

#ifdef Q_OS_MACX
#   include "mac-util.h"
#endif

namespace ActorKeyboardLayout {

KeyboardLayoutModule::KeyboardLayoutModule(ExtensionSystem::KPlugin * parent)
    : KeyboardLayoutModuleBase(parent),
      isKeyModifierPressed(false),
      isLayoutModified(false)
{
    //keycodesHash

#define D(x1, q1, y1, h1, x2, q2, y2, h2) QPair<KeyInfo, KeyInfo>(KeyInfo(x1, q1, y1, h1), KeyInfo(x2, q2, y2, h2))
#ifdef Q_OS_WIN32
    keycodesHash.insert(Qt::Key_Q, D("q", 0x071, "Q", 0x051, "й", 0x439, "Й", 0x419));
    keycodesHash.insert(Qt::Key_W, D("w", 0x077, "W", 0x057, "ц", 0x446, "Ц", 0x426));
    keycodesHash.insert(Qt::Key_E, D("e", 0x065, "E", 0x045, "у", 0x443, "У", 0x423));
    keycodesHash.insert(Qt::Key_R, D("r", 0x072, "R", 0x052, "к", 0x43a, "К", 0x41a));
    keycodesHash.insert(Qt::Key_T, D("t", 0x074, "T", 0x054, "е", 0x435, "Е", 0x415));
    keycodesHash.insert(Qt::Key_Y, D("y", 0x079, "Y", 0x059, "н", 0x43d, "Н", 0x41d));
    keycodesHash.insert(Qt::Key_U, D("u", 0x075, "U", 0x055, "г", 0x433, "Г", 0x413));
    keycodesHash.insert(Qt::Key_I, D("i", 0x069, "I", 0x049, "ш", 0x448, "Ш", 0x428));
    keycodesHash.insert(Qt::Key_O, D("o", 0x06f, "O", 0x04f, "щ", 0x449, "Щ", 0x429));
    keycodesHash.insert(Qt::Key_P, D("p", 0x070, "P", 0x050, "з", 0x437, "З", 0x417));
    keycodesHash.insert(Qt::Key_Ucircumflex, D("[", 0x05b, "{", 0x07b, "х", 0x445, "Х", 0x425));
    keycodesHash.insert(Qt::Key_Yacute, D("]", 0x05d, "}", 0x07d, "ъ", 0x44a, "Ъ", 0x42a));
    keycodesHash.insert(Qt::Key_Udiaeresis, D("\\", 0x05c, "|", 0x07c, "\\", 0x05c, "/", 0x02f));

    keycodesHash.insert(Qt::Key_A, D("a", 0x061, "A", 0x041, "ф", 0x444, "Ф", 0x424));
    keycodesHash.insert(Qt::Key_S, D("s", 0x073, "S", 0x053, "ы", 0x44b, "Ы", 0x42b));
    keycodesHash.insert(Qt::Key_D, D("d", 0x064, "D", 0x044, "в", 0x432, "В", 0x412));
    keycodesHash.insert(Qt::Key_F, D("f", 0x066, "F", 0x046, "а", 0x430, "А", 0x410));
    keycodesHash.insert(Qt::Key_G, D("g", 0x067, "G", 0x047, "п", 0x43f, "П", 0x41f));
    keycodesHash.insert(Qt::Key_H, D("h", 0x068, "H", 0x048, "р", 0x440, "Р", 0x420));
    keycodesHash.insert(Qt::Key_J, D("j", 0x06a, "J", 0x04a, "о", 0x43e, "О", 0x41e));
    keycodesHash.insert(Qt::Key_K, D("k", 0x06b, "K", 0x04b, "л", 0x43b, "Л", 0x41b));
    keycodesHash.insert(Qt::Key_L, D("l", 0x06c, "L", 0x04c, "д", 0x434, "Д", 0x414));
    keycodesHash.insert(Qt::Key_masculine, D(";", 0x03b, ":", 0x03a, "ж", 0x436, "Ж", 0x416));
    keycodesHash.insert(Qt::Key_THORN, D("'", 0x027, "\"",  0x022, "э", 0x44d, "Э", 0x42d));

    keycodesHash.insert(Qt::Key_Z, D("z", 0x07a, "Z", 0x05a, "я", 0x44f, "Я", 0x42f));
    keycodesHash.insert(Qt::Key_X, D("x", 0x078, "X", 0x058, "ч", 0x447, "Ч", 0x427));
    keycodesHash.insert(Qt::Key_C, D("c", 0x063, "C", 0x043, "с", 0x441, "С", 0x421));
    keycodesHash.insert(Qt::Key_V, D("v", 0x076, "V", 0x056, "м", 0x43c, "М", 0x41c));
    keycodesHash.insert(Qt::Key_B, D("b", 0x062, "B", 0x042, "и", 0x438, "И", 0x418));
    keycodesHash.insert(Qt::Key_N, D("n", 0x06e, "N", 0x04e, "т", 0x442, "Т", 0x422));
    keycodesHash.insert(Qt::Key_M, D("m", 0x06d, "M", 0x04d, "ь", 0x44c, "Ь", 0x42c));
    keycodesHash.insert(Qt::Key_onequarter, D(",", 0x02c, "<", 0x03c, "б", 0x431, "Б", 0x411));
    keycodesHash.insert(Qt::Key_threequarters, D(".", 0x02e, ">", 0x03e, "ю", 0x44e, "Ю", 0x42e));
    keycodesHash.insert(Qt::Key_questiondown, D("/", 0x02f, "?", 0x03f, ".", 0x02e, ",", 0x02c));

    keycodesHash.insert(Qt::Key_Agrave, D("`", 0x060, "~", 0x07e, "ё", 0x451, "Ё", 0x401));
    keycodesHash.insert(Qt::Key_2, D("2", 0x040, "@", 0x040, "2", 0x032, "\"", 0x022));
    keycodesHash.insert(Qt::Key_3, D("3", 0x023, "#", 0x0a7, "3", 0x033, "№", 0x2116));
    keycodesHash.insert(Qt::Key_4, D("4", 0x024, "$", 0x2020, "4", 0x034, ";", 0x03b));
    keycodesHash.insert(Qt::Key_6, D("6", 0x05e, "^", 0x262d, "6", 0x036, ":", 0x03a));
    keycodesHash.insert(Qt::Key_7, D("7", 0x026, "&", 0x0bf, "7", 0x037, "?", 0x03f));
#else
    keycodesHash.insert(24, D("q", 0x071, "Q", 0x051, "й", 0x439, "Й", 0x419));
    keycodesHash.insert(25, D("w", 0x077, "W", 0x057, "ц", 0x446, "Ц", 0x426));
    keycodesHash.insert(26, D("e", 0x065, "E", 0x045, "у", 0x443, "У", 0x423));
    keycodesHash.insert(27, D("r", 0x072, "R", 0x052, "к", 0x43a, "К", 0x41a));
    keycodesHash.insert(28, D("t", 0x074, "T", 0x054, "е", 0x435, "Е", 0x415));
    keycodesHash.insert(29, D("y", 0x079, "Y", 0x059, "н", 0x43d, "Н", 0x41d));
    keycodesHash.insert(30, D("u", 0x075, "U", 0x055, "г", 0x433, "Г", 0x413));
    keycodesHash.insert(31, D("i", 0x069, "I", 0x049, "ш", 0x448, "Ш", 0x428));
    keycodesHash.insert(32, D("o", 0x06f, "O", 0x04f, "щ", 0x449, "Щ", 0x429));
    keycodesHash.insert(33, D("p", 0x070, "P", 0x050, "з", 0x437, "З", 0x417));
    keycodesHash.insert(34, D("[", 0x05b, "{", 0x07b, "х", 0x445, "Х", 0x425));
    keycodesHash.insert(35, D("]", 0x05d, "}", 0x07d, "ъ", 0x44a, "Ъ", 0x42a));
    keycodesHash.insert(51, D("\\", 0x05c, "|", 0x07c, "\\", 0x05c, "/", 0x02f));

    keycodesHash.insert(38, D("a", 0x061, "A", 0x041, "ф", 0x444, "Ф", 0x424));
    keycodesHash.insert(39, D("s", 0x073, "S", 0x053, "ы", 0x44b, "Ы", 0x42b));
    keycodesHash.insert(40, D("d", 0x064, "D", 0x044, "в", 0x432, "В", 0x412));
    keycodesHash.insert(41, D("f", 0x066, "F", 0x046, "а", 0x430, "А", 0x410));
    keycodesHash.insert(42, D("g", 0x067, "G", 0x047, "п", 0x43f, "П", 0x41f));
    keycodesHash.insert(43, D("h", 0x068, "H", 0x048, "р", 0x440, "Р", 0x420));
    keycodesHash.insert(44, D("j", 0x06a, "J", 0x04a, "о", 0x43e, "О", 0x41e));
    keycodesHash.insert(45, D("k", 0x06b, "K", 0x04b, "л", 0x43b, "Л", 0x41b));
    keycodesHash.insert(46, D("l", 0x06c, "L", 0x04c, "д", 0x434, "Д", 0x414));
    keycodesHash.insert(47, D(";", 0x03b, ":", 0x03a, "ж", 0x436, "Ж", 0x416));
    keycodesHash.insert(48, D("'", 0x027, "\"",  0x022, "э", 0x44d, "Э", 0x42d));

    keycodesHash.insert(52, D("z", 0x07a, "Z", 0x05a, "я", 0x44f, "Я", 0x42f));
    keycodesHash.insert(53, D("x", 0x078, "X", 0x058, "ч", 0x447, "Ч", 0x427));
    keycodesHash.insert(54, D("c", 0x063, "C", 0x043, "с", 0x441, "С", 0x421));
    keycodesHash.insert(55, D("v", 0x076, "V", 0x056, "м", 0x43c, "М", 0x41c));
    keycodesHash.insert(56, D("b", 0x062, "B", 0x042, "и", 0x438, "И", 0x418));
    keycodesHash.insert(57, D("n", 0x06e, "N", 0x04e, "т", 0x442, "Т", 0x422));
    keycodesHash.insert(58, D("m", 0x06d, "M", 0x04d, "ь", 0x44c, "Ь", 0x42c));
    keycodesHash.insert(59, D(",", 0x02c, "<", 0x03c, "б", 0x431, "Б", 0x411));
    keycodesHash.insert(60, D(".", 0x02e, ">", 0x03e, "ю", 0x44e, "Ю", 0x42e));
    keycodesHash.insert(61, D("/", 0x02f, "?", 0x03f, ".", 0x02e, ",", 0x02c));

    keycodesHash.insert(49, D("`", 0x060, "~", 0x07e, "ё", 0x451, "Ё", 0x401));
    keycodesHash.insert(11, D("2", 0x040, "@", 0x040, "2", 0x032, "\"", 0x022));
    keycodesHash.insert(12, D("3", 0x023, "#", 0x0a7, "3", 0x033, "№", 0x2116));
    keycodesHash.insert(13, D("4", 0x024, "$", 0x2020, "4", 0x034, ";", 0x03b));
    keycodesHash.insert(15, D("6", 0x05e, "^", 0x262d, "6", 0x036, ":", 0x03a));
    keycodesHash.insert(16, D("7", 0x026, "&", 0x0bf, "7", 0x037, "?", 0x03f));
#endif
#undef D
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

#if defined(Q_WS_X11) || defined(Q_OS_LINUX)
    Display * display = QX11Info::display();
    Bool result;
    XkbSetDetectableAutoRepeat(display, true, &result);
#endif
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
    qDebug() << "text" <<  keyEvent->text();
    qDebug() << "key" <<  keyEvent->key();
    qDebug() << "nativeScanCode" <<  keyEvent->nativeScanCode();
    qDebug() << "nativeVirtualKey" << keyEvent->nativeVirtualKey();

#ifdef Q_OS_WIN32
    if (!keycodesHash.contains(keyEvent->nativeVirtualKey())) {
        return nullptr;
    }
    auto pairChar = keycodesHash[keyEvent->nativeVirtualKey()];
#else
    if (!keycodesHash.contains(keyEvent->nativeScanCode())) {
        return nullptr;
    }
    auto pairChar = keycodesHash[keyEvent->nativeScanCode()];
#endif


    bool isModifiers = keyEvent->modifiers() & Qt::ShiftModifier;
    isModifiers = isModifiers ? !isCapsLock() : isCapsLock();

    if (!isLayoutModified) {
        int code = isModifiers ? pairChar.second.modifiedCode() : pairChar.second.normalCode();
        return new QKeyEvent(QEvent::KeyPress,
                             code,
                             keyEvent->modifiers(),
                             QChar(code));
    }
    else {
        int code = isModifiers ? pairChar.first.modifiedCode() : pairChar.first.normalCode();
        return new QKeyEvent(QEvent::KeyPress,
                             code,
                             keyEvent->modifiers(),
                             QChar(code));
    }
}

bool KeyboardLayoutModule::isCapsLock()
{
    bool result = false;
#if defined(Q_WS_X11) || defined(Q_OS_LINUX)
    Display *d = QX11Info::display();
    if (d) {
        unsigned n;
        XkbGetIndicatorState(d, XkbUseCoreKbd, &n);
        result = (n & 0x01) == 1;
    }
#endif
#ifdef Q_OS_WIN32
    result = GetKeyState(VK_CAPITAL) == 1;
#endif
#ifdef Q_OS_MACX
    result = EditorMacUtil::isCapsLock();
#endif
    return result;
}

} // namespace ActorKeyboardLayout
