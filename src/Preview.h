#ifndef QT_TP2_PREVIEW_H
#define QT_TP2_PREVIEW_H

#include "ui_preview.h"

#include "Canvas.h"

#include <QDialog>


class Preview : public QDialog {
Q_OBJECT
public:
    explicit Preview(QWidget *parent = nullptr, Canvas *canvas = nullptr);

    ~Preview() override = default;

public slots:

private:
    Ui::Preview *ui;
    Canvas *canvas;
};


#endif //QT_TP2_PREVIEW_H
