#ifndef QT_TP2_CANVAS_H
#define QT_TP2_CANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include <QLine>
#include <QRect>
#include <QPen>
#include <QBrush>
#include <QAction>

#include "Shape.h"
#include "Rectangle.h"
#include "Line.h"
#include "Ellipse.h"


class Canvas : public QWidget {
Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    QColor getColor() const;

    inline QPen getPen() const {
        return QPen(brushStyle, penSize, penStyle, penCapStyle, penJoinStyle);
    }

    inline QBrush getBrush() const {
        return QBrush(penColor, brushStyle);
    }

    enum MouseModes {
        SELECTION,
        PEN,
        RECTANGLE,
        ELLIPSE
    };

public slots:

    void setMouseMod(QAction *);

    void setColor(const QColor &color);

    void setBrushFill(bool);

    void setPenStyle(QAction *);

    void setPenCapStyle(QAction *);

    void setPenJoinStyle(QAction *);

    void deleteLastShape();

    void deleteAllShapes();

    void setLineWidth(int);

    void saveAllShapes();

    void readAllShapes();

protected:
    void paintEvent(QPaintEvent *) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    MouseModes mouseMod = SELECTION;
    QList<Shape *> shapes;
    QList<QPen *> pens;
    QList<QBrush *> brushes;

    Qt::PenStyle penStyle = Qt::SolidLine;
    Qt::PenCapStyle penCapStyle = Qt::FlatCap;
    Qt::PenJoinStyle penJoinStyle = Qt::MiterJoin;
    QColor penColor = Qt::black;
    Qt::BrushStyle brushStyle = Qt::NoBrush;
    qreal penSize = 1;

    int lastSelected = -1;
    QPoint lastMousePosition;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
};


#endif //QT_TP2_CANVAS_H
