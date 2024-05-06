#include "shortcutmanager.h"
#include <QMap>
#include <Windows.h>
#include <Qt>

ShortcutManager *ShortcutManager::instance = nullptr;

ShortcutManager::ShortcutManager(QObject *parent) : QObject(parent) {
    instance = this;
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    
    // Connect signals to slots
    connect(this, &ShortcutManager::playPausePressed, this, &ShortcutManager::onPlayPausePressed);
    connect(this, &ShortcutManager::nextPressed, this, &ShortcutManager::onNextPressed);
    connect(this, &ShortcutManager::previousPressed, this, &ShortcutManager::onPreviousPressed);
    
    // Initialize shortcut activation states
    this->playPauseActive = false;
    this->nextActive = false;
    this->previousActive = false;
}

LRESULT CALLBACK ShortcutManager::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        PKBDLLHOOKSTRUCT pkbhs = (PKBDLLHOOKSTRUCT)lParam;
        if (pkbhs->flags & LLKHF_INJECTED)
            return CallNextHookEx(NULL, nCode, wParam, lParam);

        DWORD vkCode = pkbhs->vkCode;

        switch (wParam) {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            if (instance)
                instance->handleKeyPress(vkCode);
            break;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Convert Windows virtual key codes to Qt key codes
Qt::Key windowsVkToQt(DWORD vkCode) {
    static QMap<DWORD, Qt::Key> keyMap = {
        {0x41, Qt::Key_A},
        {0x42, Qt::Key_B},
        {0x43, Qt::Key_C},
        {0x44, Qt::Key_D},
        {0x45, Qt::Key_E},
        {0x46, Qt::Key_F},
        {0x47, Qt::Key_G},
        {0x48, Qt::Key_H},
        {0x49, Qt::Key_I},
        {0x4A, Qt::Key_J},
        {0x4B, Qt::Key_K},
        {0x4C, Qt::Key_L},
        {0x4D, Qt::Key_M},
        {0x4E, Qt::Key_N},
        {0x4F, Qt::Key_O},
        {0x50, Qt::Key_P},
        {0x51, Qt::Key_Q},
        {0x52, Qt::Key_R},
        {0x53, Qt::Key_S},
        {0x54, Qt::Key_T},
        {0x55, Qt::Key_U},
        {0x56, Qt::Key_V},
        {0x57, Qt::Key_W},
        {0x58, Qt::Key_X},
        {0x59, Qt::Key_Y},
        {0x5A, Qt::Key_Z},
        {VK_CANCEL, Qt::Key_Cancel},
        {VK_BACK, Qt::Key_Backspace},
        {VK_TAB, Qt::Key_Tab},
        {VK_CLEAR, Qt::Key_Clear},
        {VK_RETURN, Qt::Key_Return},
        {VK_SHIFT, Qt::Key_Shift},
        {VK_CONTROL, Qt::Key_Control},
        {VK_MENU, Qt::Key_Alt},
        {VK_PAUSE, Qt::Key_Pause},
        {VK_CAPITAL, Qt::Key_CapsLock},
        {VK_ESCAPE, Qt::Key_Escape},
        {VK_SPACE, Qt::Key_Space},
        {VK_PRIOR, Qt::Key_PageUp},
        {VK_NEXT, Qt::Key_PageDown},
        {VK_END, Qt::Key_End},
        {VK_HOME, Qt::Key_Home},
        {VK_LEFT, Qt::Key_Left},
        {VK_UP, Qt::Key_Up},
        {VK_RIGHT, Qt::Key_Right},
        {VK_DOWN, Qt::Key_Down},
        {VK_SELECT, Qt::Key_Select},
        {VK_PRINT, Qt::Key_Print},
        {VK_EXECUTE, Qt::Key_Execute},
        {VK_INSERT, Qt::Key_Insert},
        {VK_DELETE, Qt::Key_Delete},
        {VK_HELP, Qt::Key_Help},
        {VK_NUMPAD0, Qt::Key_0},
        {VK_NUMPAD1, Qt::Key_1},
        {VK_NUMPAD2, Qt::Key_2},
        {VK_NUMPAD3, Qt::Key_3},
        {VK_NUMPAD4, Qt::Key_4},
        {VK_NUMPAD5, Qt::Key_5},
        {VK_NUMPAD6, Qt::Key_6},
        {VK_NUMPAD7, Qt::Key_7},
        {VK_NUMPAD8, Qt::Key_8},
        {VK_NUMPAD9, Qt::Key_9},
        {VK_MULTIPLY, Qt::Key_Asterisk},
        {VK_ADD, Qt::Key_Plus},
        {VK_SEPARATOR, Qt::Key_Comma},
        {VK_SUBTRACT, Qt::Key_Minus},
        {VK_DECIMAL, Qt::Key_Period},
        {VK_DIVIDE, Qt::Key_Slash},
        {VK_F1, Qt::Key_F1},
        {VK_F2, Qt::Key_F2},
        {VK_F3, Qt::Key_F3},
        {VK_F4, Qt::Key_F4},
        {VK_F5, Qt::Key_F5},
        {VK_F6, Qt::Key_F6},
        {VK_F7, Qt::Key_F7},
        {VK_F8, Qt::Key_F8},
        {VK_F9, Qt::Key_F9},
        {VK_F10, Qt::Key_F10},
        {VK_F11, Qt::Key_F11},
        {VK_F12, Qt::Key_F12},
        {VK_NUMLOCK, Qt::Key_NumLock},
        {VK_SCROLL, Qt::Key_ScrollLock}
    };

    return keyMap.value(vkCode, Qt::Key_unknown);
}

void ShortcutManager::handleKeyPress(DWORD vkCode) {
    Qt::Key qtKeyCode = windowsVkToQt(vkCode);

    if (qtKeyCode != 0) {
        QKeySequence keySequence(qtKeyCode);

        if (playPauseShortcut.matches(keySequence) && this->playPauseActive)
            emit playPausePressed();
        else if (nextShortcut.matches(keySequence) && this->nextActive)
            emit nextPressed();
        else if (previousShortcut.matches(keySequence) && this->previousActive)
            emit previousPressed();
    }
}

void ShortcutManager::setPlayPauseShortcut(const QKeySequence &shortcut) {
    playPauseShortcut = shortcut;
}

void ShortcutManager::setNextShortcut(const QKeySequence &shortcut) {
    nextShortcut = shortcut;
}

void ShortcutManager::setPreviousShortcut(const QKeySequence &shortcut) {
    previousShortcut = shortcut;
}

void ShortcutManager::onPlayPausePressed() {
    instance->sendInput(VK_MEDIA_PLAY_PAUSE);
}

void ShortcutManager::onNextPressed() {
    instance->sendInput(VK_MEDIA_NEXT_TRACK);
}

void ShortcutManager::onPreviousPressed() {
    instance->sendInput(VK_MEDIA_PREV_TRACK);
}

void ShortcutManager::changePlayPauseActive(const bool state) {
    playPauseActive = state;
}

void ShortcutManager::changeNextActive(const bool state) {
    nextActive = state;
}

void ShortcutManager::changePreviousActive(const bool state) {
    previousActive = state;
}

void ShortcutManager::sendInput(DWORD vkCode) {
    KEYBDINPUT kb = { 0 };
    INPUT Input = { 0 };
    kb.wVk = vkCode;
    kb.wScan = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
    Input.type = INPUT_KEYBOARD;

    Input.ki = kb;
    ::SendInput(1, &Input, sizeof(Input));

    ::ZeroMemory(&kb, sizeof(KEYBDINPUT));
    ::ZeroMemory(&Input, sizeof(INPUT));
    kb.dwFlags = KEYEVENTF_KEYUP;

    kb.wVk = vkCode;
    Input.type = INPUT_KEYBOARD;
    Input.ki = kb;
    ::SendInput(1, &Input, sizeof(Input));
}