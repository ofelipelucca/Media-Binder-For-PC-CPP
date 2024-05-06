#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void onPlayPauseShortcutEdit_editingFinished(); //< Slot for play/pause shortcut editing finished
    void onNextShortcutEdit_editingFinished(); //< Slot for next track shortcut editing finished
    void onPreviousShortcutEdit_editingFinished(); //< Slot for previous track shortcut editing finished
    void onPlayPauseCheckbox_stateChanged(const int arg1); //< Slot for play/pause checkbox state change
    void onNextCheckbox_stateChanged(const int arg1); //< Slot for next track checkbox state change
    void onPreviousCheckbox_stateChanged(const int arg1); //< Slot for previous track checkbox state change

signals:
    // Events emitted when shortcuts are edited
    void playPauseShortcutEdited(const QKeySequence& sentence);
    void nextShortcutEdited(const QKeySequence& sentence);
    void previousShortcutEdited(const QKeySequence& sentence);

    // Events emitted when checkbox state changes
    void playPauseCheckboxChanged(const bool arg);
    void nextCheckboxChanged(const bool arg);
    void previousCheckboxChanged(const bool arg);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H