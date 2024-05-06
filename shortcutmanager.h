#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QKeySequence>
#include <windows.h>

class QKeySequenceEdit;

class ShortcutManager : public QObject {
    Q_OBJECT
public:
    explicit ShortcutManager(QObject *parent = nullptr);
    static ShortcutManager *instance;

    // Methods for setting shortcuts
    void setPlayPauseShortcut(const QKeySequence &shortcut);
    void setNextShortcut(const QKeySequence &shortcut);
    void setPreviousShortcut(const QKeySequence &shortcut);

    // Methods for activating/deactivating shortcuts
    void changePlayPauseActive(const bool state);
    void changeNextActive(const bool state);
    void changePreviousActive(const bool state);

public slots:
    // Slots for handling key press events
    void onPlayPausePressed();
    void onNextPressed();
    void onPreviousPressed();

signals:
    // Signals emitted when corresponding keys are pressed
    void playPausePressed();
    void nextPressed();
    void previousPressed();

private:
    // Low-level keyboard hook procedure
    /// @brief Processes low-level keyboard input events.
    /// @details This function is called whenever a keyboard event occurs, and it is responsible for handling key presses and emitting corresponding signals.
    /// @param nCode The hook code.
    /// @param wParam The type of keyboard message.
    /// @param lParam A pointer to a KBDLLHOOKSTRUCT structure that contains details about the keyboard event.
    /// @return The result of the hook processing.
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    
    // Methods for handling key press events
    /// @brief Verifies the key pressed by the user and emits corresponding signals if a match is found.
    /// @param vkCode The virtual key code of the pressed key.
    void handleKeyPress(DWORD vkCode);

    /// @brief Sends keyboard input for Play/Pause, Next, and Previous media control commands.
    /// @param vkCode The virtual key code of the command to be sent.
    void sendInput(DWORD vkCode);


    // Variables for storing shortcut sequences
    QKeySequence playPauseShortcut; //< Key sequence of Play/Pause shortcut
    QKeySequence nextShortcut;      //< Key sequence of Next shortcut
    QKeySequence previousShortcut;  //< Key sequence of Previous shortcut
    
    // Variables for storing activation states
    bool playPauseActive; //< Play/Pause checkbox state
    bool nextActive;      //< Next checkbox state
    bool previousActive;  //< Previous checkbox state
   
    HHOOK keyboardHook; //< Handle to the keyboard hook
};

#endif // SHORTCUTMANAGER_H