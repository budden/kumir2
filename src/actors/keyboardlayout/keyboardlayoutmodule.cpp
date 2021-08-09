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
    static const QHash<int, QPair<KeyInfo, KeyInfo>> CODES = {
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

    auto keyCodeMapping = translateKeyCode(keyEvent->key());
    if (!keyCodeMapping) {
        return nullptr;
    }

    auto pairChar = CODES[keyCodeMapping];
    bool isModifiers = keyEvent->modifiers() & Qt::ShiftModifier;
    isModifiers = isModifiers ? !isCapsLock() : isCapsLock();

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

bool KeyboardLayoutModule::isRussianLayout()
{
    bool result = false;
#if defined(Q_WS_X11) || defined(Q_OS_LINUX)
#if QT_VERSION < 0x050000
    // Qt4 implementation
    QString keybLang = QApplication::keyboardInputLocale().name();
    result = keybLang.contains("ru");
#else
    // Qt5 implementation
    QInputMethod *inputMethod = QApplication::inputMethod();
    QString keybLang = inputMethod->locale().name();
    result = keybLang.contains("ru");
    Display *d = QX11Info::display();
    if (d && !result) {  // Might be variant of main input method
        // solution found at: http://www.linux.org.ru/forum/development/12852504
        XkbStateRec xkbState;
        XkbGetState(d, XkbUseCoreKbd, &xkbState);
        Atom real_prop_type;
        int fmt;
        unsigned long nitems, extra_bytes;
        char *prop_data = NULL;
        Atom rules_atom = XInternAtom(d, "_XKB_RULES_NAMES", False);
        XGetWindowProperty(d, DefaultRootWindow(d), rules_atom, 0L, 1024,
            False, XA_STRING, &real_prop_type, &fmt, &nitems, &extra_bytes, (unsigned char **)(void *) &prop_data);
        QStringList names;
        for (char *p = prop_data; p - prop_data < (long)nitems && p != NULL; p += strlen(p) + 1) {
            names.append(p);
        }
        if (names.count() > 3) {
            names = names[2].split(",");
        }
        XFree(prop_data);
        keybLang = names[xkbState.group];
        result = keybLang.contains("ru");
    }
#endif
#endif // X11

#ifdef Q_OS_WIN32
    HKL l = GetKeyboardLayout(0);
    result = unsigned(l) == 0x4190419;
#endif
#ifdef Q_OS_MACX
    result = EditorMacUtil::isRussianLayout();
#endif
    return result;
}

int KeyboardLayoutModule::translateKeyCode(int key)
{
    static const QHash<int, int> KEY_MAPPING_CYRILLIC = {
        { 0x451, Qt::Key_Agrave},
        { 0x401, Qt::Key_Agrave},

        { 0x032, Qt::Key_2},
        { 0x022, Qt::Key_2},

        { 0x033, Qt::Key_3},
        { 0x2116, Qt::Key_3},

        { 0x034, Qt::Key_4},
        { 0x03b, Qt::Key_4},

        { 0x036, Qt::Key_6},
        { 0x03a, Qt::Key_6},

        { 0x037, Qt::Key_7},
        { 0x03f, Qt::Key_7},

        { 0x439, Qt::Key_Q},
        { 0x419, Qt::Key_Q},

        { 0x446, Qt::Key_W},
        { 0x426, Qt::Key_W},

        { 0x443, Qt::Key_E},
        { 0x423, Qt::Key_E},

        { 0x43a, Qt::Key_R},
        { 0x41a, Qt::Key_R},

        { 0x435, Qt::Key_T},
        { 0x415, Qt::Key_T},

        { 0x43d, Qt::Key_Y},
        { 0x41d, Qt::Key_Y},

        { 0x433, Qt::Key_U},
        { 0x413, Qt::Key_U},

        { 0x448, Qt::Key_I},
        { 0x428, Qt::Key_I},

        { 0x449, Qt::Key_O},
        { 0x429, Qt::Key_O},

        { 0x437, Qt::Key_P},
        { 0x417, Qt::Key_P},

        { 0x445, Qt::Key_Ucircumflex},
        { 0x425, Qt::Key_Ucircumflex},

        { 0x44a, Qt::Key_Yacute},
        { 0x42a, Qt::Key_Yacute},

        { 0x05c, Qt::Key_Udiaeresis},
        { 0x2665, Qt::Key_Udiaeresis},

        { 0x444, Qt::Key_A},
        { 0x424, Qt::Key_A},

        { 0x44b, Qt::Key_S},
        { 0x42b, Qt::Key_S},

        { 0x432, Qt::Key_D},
        { 0x412, Qt::Key_D},

        { 0x430, Qt::Key_F},
        { 0x410, Qt::Key_F},

        { 0x43f, Qt::Key_G},
        { 0x41f, Qt::Key_G},

        { 0x440, Qt::Key_H},
        { 0x420, Qt::Key_H},

        { 0x43e, Qt::Key_J},
        { 0x41e, Qt::Key_J},

        { 0x43b, Qt::Key_K},
        { 0x41b, Qt::Key_K},

        { 0x434, Qt::Key_L},
        { 0x414, Qt::Key_L},

        { 0x416, Qt::Key_masculine},
        { 0x436, Qt::Key_masculine},

        { 0x44d, Qt::Key_THORN},
        { 0x42d, Qt::Key_THORN},

        { 0x44f, Qt::Key_Z},
        { 0x42f, Qt::Key_Z},

        { 0x447, Qt::Key_X},
        { 0x427, Qt::Key_X},

        { 0x441, Qt::Key_C},
        { 0x421, Qt::Key_C},

        { 0x43c, Qt::Key_V},
        { 0x41c, Qt::Key_V},

        { 0x438, Qt::Key_B},
        { 0x418, Qt::Key_B},

        { 0x442, Qt::Key_N},
        { 0x422, Qt::Key_N},

        { 0x44c, Qt::Key_M},
        { 0x42c, Qt::Key_M},

        { 0x431, Qt::Key_onequarter},
        { 0x411, Qt::Key_onequarter},

        { 0x44e, Qt::Key_threequarters},
        { 0x42e, Qt::Key_threequarters},

        { 0x02e, Qt::Key_questiondown},
        { 0x02c, Qt::Key_questiondown},
    };

    static const QHash<int, int> KEY_MAPPING_LATIN = {
        { 0x060, Qt::Key_Agrave},
        { 0x07e, Qt::Key_Agrave},

        { 0x040, Qt::Key_2},
        { 0x040, Qt::Key_2},

        { 0x023, Qt::Key_3},
        { 0x0a7, Qt::Key_3},

        { 0x024, Qt::Key_4},
        { 0x2020, Qt::Key_4},

        { 0x05e, Qt::Key_6},
        { 0x262d, Qt::Key_6},

        { 0x026, Qt::Key_7},
        { 0x0bf, Qt::Key_7},

        { 0x071, Qt::Key_Q},
        { 0x051, Qt::Key_Q},

        { 0x077, Qt::Key_W},
        { 0x057, Qt::Key_W},

        { 0x065, Qt::Key_E},
        { 0x045, Qt::Key_E},

        { 0x072, Qt::Key_R},
        { 0x052, Qt::Key_R},

        { 0x074, Qt::Key_T},
        { 0x054, Qt::Key_T},

        { 0x079, Qt::Key_Y},
        { 0x059, Qt::Key_Y},

        { 0x075, Qt::Key_U},
        { 0x055, Qt::Key_U},

        { 0x069, Qt::Key_I},
        { 0x049, Qt::Key_I},

        { 0x06f, Qt::Key_O},
        { 0x04f, Qt::Key_O},

        { 0x070, Qt::Key_P},
        { 0x050, Qt::Key_P},

        { 0x05b, Qt::Key_Ucircumflex},
        { 0x07b, Qt::Key_Ucircumflex},

        { 0x05d, Qt::Key_Yacute},
        { 0x07d, Qt::Key_Yacute},

        { 0x07c, Qt::Key_Udiaeresis},
        { 0x02a, Qt::Key_Udiaeresis},

        { 0x061, Qt::Key_A},
        { 0x041, Qt::Key_A},

        { 0x073, Qt::Key_S},
        { 0x053, Qt::Key_S},

        { 0x064, Qt::Key_D},
        { 0x044, Qt::Key_D},

        { 0x066, Qt::Key_F},
        { 0x046, Qt::Key_F},

        { 0x067, Qt::Key_G},
        { 0x047, Qt::Key_G},

        { 0x068, Qt::Key_H},
        { 0x048, Qt::Key_H},

        { 0x06a, Qt::Key_J},
        { 0x04a, Qt::Key_J},

        { 0x06b, Qt::Key_K},
        { 0x04b, Qt::Key_K},

        { 0x06c, Qt::Key_L},
        { 0x04c, Qt::Key_L},

        { 0x03b, Qt::Key_masculine},
        { 0x03a, Qt::Key_masculine},

        { 0x027, Qt::Key_THORN},
        { 0x022, Qt::Key_THORN},

        { 0x07a, Qt::Key_Z},
        { 0x05a, Qt::Key_Z},

        { 0x078, Qt::Key_X},
        { 0x058, Qt::Key_X},

        { 0x063, Qt::Key_C},
        { 0x043, Qt::Key_C},

        { 0x076, Qt::Key_V},
        { 0x056, Qt::Key_V},

        { 0x062, Qt::Key_B},
        { 0x042, Qt::Key_B},

        { 0x06e, Qt::Key_N},
        { 0x04e, Qt::Key_N},

        { 0x06d, Qt::Key_M},
        { 0x04d, Qt::Key_M},

        { 0x03c, Qt::Key_onequarter},
        { 0x02c, Qt::Key_onequarter},

        { 0x03e, Qt::Key_threequarters},
        { 0x02e, Qt::Key_threequarters},

        { 0x03f, Qt::Key_questiondown},
        { 0x02f, Qt::Key_questiondown},
    };

    if (isRussianLayout()) {
        return KEY_MAPPING_LATIN[key];
    }
    else {
        return KEY_MAPPING_LATIN[key];
    }
}

} // namespace ActorKeyboardLayout
