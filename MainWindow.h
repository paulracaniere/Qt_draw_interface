#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QTextEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include <QColorDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QActionGroup>
#include <QSpinBox>

#include "Canvas.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void closeEvent(QCloseEvent *event) override;

private:
    Canvas *canvas;

    void openColorMenu();
};

#endif // MAINWINDOW_H
