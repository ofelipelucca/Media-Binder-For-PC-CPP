#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Connect editingFinished signal of play/pause shortcut editor to corresponding slot
    connect(ui->playpauseShortcutEdit, &QKeySequenceEdit::editingFinished, this, &MainWindow::onPlayPauseShortcutEdit_editingFinished);
    
    // Connect editingFinished signal of next track shortcut editor to corresponding slot
    connect(ui->nextShortcutEdit, &QKeySequenceEdit::editingFinished, this, &MainWindow::onNextShortcutEdit_editingFinished);
    
    // Connect editingFinished signal of previous track shortcut editor to corresponding slot
    connect(ui->previousShortcutEdit, &QKeySequenceEdit::editingFinished, this, &MainWindow::onPreviousShortcutEdit_editingFinished);

    // Connect stateChanged signal of play/pause checkbox to corresponding slot
    connect(ui->playpauseCheckbox, &QCheckBox::stateChanged, this, &MainWindow::onPlayPauseCheckbox_stateChanged);
    
    // Connect stateChanged signal of next track checkbox to corresponding slot
    connect(ui->nextCheckbox, &QCheckBox::stateChanged, this, &MainWindow::onNextCheckbox_stateChanged);
    
    // Connect stateChanged signal of previous track checkbox to corresponding slot
    connect(ui->previousCheckbox, &QCheckBox::stateChanged, this, &MainWindow::onPreviousCheckbox_stateChanged);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onPlayPauseShortcutEdit_editingFinished() {
    emit playPauseShortcutEdited(ui->playpauseShortcutEdit->keySequence());
}

void MainWindow::onNextShortcutEdit_editingFinished() {
    emit nextShortcutEdited(ui->nextShortcutEdit->keySequence());
}

void MainWindow::onPreviousShortcutEdit_editingFinished() {
    emit previousShortcutEdited(ui->previousShortcutEdit->keySequence());
}

void MainWindow::onPlayPauseCheckbox_stateChanged(const int state) {
    emit playPauseCheckboxChanged(state == Qt::Checked);
}

void MainWindow::onNextCheckbox_stateChanged(const int state) {
    emit nextCheckboxChanged(state == Qt::Checked);
}

void MainWindow::onPreviousCheckbox_stateChanged(const int state) {
    emit previousCheckboxChanged(state == Qt::Checked);
}
