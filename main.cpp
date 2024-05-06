#include "mainwindow.h"
#include "shortcutmanager.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    ShortcutManager shortcutManager;

    // Set default keyboard shortcuts for media control
    shortcutManager.setPlayPauseShortcut(QKeySequence(VK_NUMPAD5)); //< Default value for play/pause shortcut
    shortcutManager.setNextShortcut(QKeySequence(VK_NUMPAD6)); //< Default value for next track shortcut
    shortcutManager.setPreviousShortcut(QKeySequence(VK_NUMPAD4)); //< Default value for previous track shortcut

    // Connect window events (shortcuts edited by user) to ShortcutManager class
    QObject::connect(&w, &MainWindow::playPauseShortcutEdited, &shortcutManager, &ShortcutManager::setPlayPauseShortcut);
    QObject::connect(&w, &MainWindow::nextShortcutEdited, &shortcutManager, &ShortcutManager::setNextShortcut);
    QObject::connect(&w, &MainWindow::previousShortcutEdited, &shortcutManager, &ShortcutManager::setPreviousShortcut);

    // Connect window events (checkbox state changed) to ShortcutManager class
    QObject::connect(&w, &MainWindow::playPauseCheckboxChanged, &shortcutManager, &ShortcutManager::changePlayPauseActive);
    QObject::connect(&w, &MainWindow::nextCheckboxChanged, &shortcutManager, &ShortcutManager::changeNextActive);
    QObject::connect(&w, &MainWindow::previousCheckboxChanged, &shortcutManager, &ShortcutManager::changePreviousActive);

    w.show();

    return a.exec();
}