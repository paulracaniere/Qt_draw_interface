#include "Canvas.h"
#include <QPainter>

#include <QMessageBox>

#include <iostream>

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
    // Window size
    setMinimumSize(800, 600);

    setFocusPolicy(Qt::StrongFocus);

    // Background color
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    // Cursor
    setCursor(Qt::ArrowCursor);
}

Canvas::~Canvas() = default;

void Canvas::paintEvent(QPaintEvent *e) {
    // Standard behavior
    QWidget::paintEvent(e);
    // Create a painter for this canvas
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (auto i = 0; i < shapes.size(); i++) {
        painter.setPen(*pens[i]);
        painter.setBrush(*brushes[i]);
        shapes[i]->draw(&painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        lastSelected = -1;

        if (mouseMod == SELECTION && !shapes.isEmpty()) {
            QRect selectionRect(event->pos() - QPoint(10, 10), event->pos() + QPoint(10, 10));
            for (auto i = shapes.size() - 1; i >= 0; i--) {
                if (shapes[i]->intersects(selectionRect)) {
                    lastSelected = i;
                    break;
                }
            }
        } else if (mouseMod == PEN) {
            shapes.append(new Line(event->pos(), event->pos()));
            pens.append(new QPen(penColor, penSize, penStyle, penCapStyle, penJoinStyle));
            brushes.append(new QBrush(penColor, brushStyle));
            update();
        } else if (mouseMod == RECTANGLE) {
            shapes.append(new Rectangle(event->pos(), event->pos()));
            pens.append(new QPen(penColor, penSize, penStyle, penCapStyle, penJoinStyle));
            brushes.append(new QBrush(penColor, brushStyle));
            update();
        } else if (mouseMod == OVOID) {
            shapes.append(new Ellipse(event->pos(), event->pos()));
            pens.append(new QPen(penColor, penSize, penStyle, penCapStyle, penJoinStyle));
            brushes.append(new QBrush(penColor, brushStyle));
            update();
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        if (mouseMod == PEN || mouseMod == RECTANGLE || mouseMod == OVOID) {
            Shape *shape = shapes.last();
            shape->setP2(event->pos());
            update();
        }
    }
}

void Canvas::setMouseMod(QAction *action) {
    QVariant data = action->data();
    if (data == 0) {
        mouseMod = SELECTION;
        setCursor(Qt::ArrowCursor);
    } else if (data == 1) {
        mouseMod = PEN;
        setCursor(Qt::CrossCursor);
    } else if (data == 2) {
        mouseMod = RECTANGLE;
        setCursor(Qt::CrossCursor);
    } else if (data == 3) {
        mouseMod = OVOID;
        setCursor(Qt::CrossCursor);
    }
}

QColor Canvas::getColor() const {
    return penColor;
}

void Canvas::setColor(const QColor &color) {
    penColor = color;

    if (lastSelected != -1) {
        pens[lastSelected]->setColor(penColor);
        brushes[lastSelected]->setColor(penColor);
        update();
    }
}

void Canvas::setBrushFill(bool toFill) {
    if (toFill) brushStyle = Qt::SolidPattern;
    else brushStyle = Qt::NoBrush;

    if (lastSelected != -1) {
        brushes[lastSelected]->setStyle(brushStyle);
        update();
    }
}

void Canvas::setPenStyle(QAction *action) {
    QVariant data = action->data();
    if (data == 0) penStyle = Qt::SolidLine;
    else if (data == 1) penStyle = Qt::DashLine;
    else if (data == 2) penStyle = Qt::DotLine;
    else if (data == 3) penStyle = Qt::DashDotLine;
    else penStyle = Qt::DashDotDotLine;

    if (lastSelected != -1) {
        pens[lastSelected]->setStyle(penStyle);
        update();
    }
}

void Canvas::setPenCapStyle(QAction *action) {
    QVariant data = action->data();
    if (data == 0) penCapStyle = Qt::FlatCap;
    else if (data == 1) penCapStyle = Qt::SquareCap;
    else if (data == 2) penCapStyle = Qt::RoundCap;
    else penCapStyle = Qt::MPenCapStyle;

    if (lastSelected != -1) {
        pens[lastSelected]->setCapStyle(penCapStyle);
        update();
    }
}

void Canvas::setPenJoinStyle(QAction *action) {
    QVariant data = action->data();
    if (data == 0) penJoinStyle = Qt::MiterJoin;
    else if (data == 1) penJoinStyle = Qt::BevelJoin;
    else if (data == 2) penJoinStyle = Qt::RoundJoin;
    else if (data == 3) penJoinStyle = Qt::SvgMiterJoin;
    else penJoinStyle = Qt::MPenJoinStyle;

    if (lastSelected != -1) {
        pens[lastSelected]->setJoinStyle(penJoinStyle);
        update();
    }
}

void Canvas::setLineWidth(int width) {
    if (width != penSize) penSize = width;

    if (lastSelected != -1) {
        pens[lastSelected]->setWidth(width);
        update();
    }
}

void Canvas::deleteLastLine() {
    if (!shapes.isEmpty()) {
        shapes.removeLast();
        pens.removeLast();
        brushes.removeLast();
        update();
    }
}

void Canvas::deleteAllLines() {
    if (!shapes.isEmpty() && QMessageBox::question(this, tr("Delete?"), tr("Are you sure you want to delete all?")) ==
                             QMessageBox::No)
        return;

    bool isToBeUpdated = false;
    while (!shapes.isEmpty()) {
        shapes.removeLast();
        pens.removeLast();
        brushes.removeLast();
        isToBeUpdated = true;
    }
    if (isToBeUpdated) update();
}

void Canvas::keyPressEvent(QKeyEvent *event) {
    if (lastSelected != -1) {
        switch (event->key()) {
            case (Qt::Key_Up):
                shapes[lastSelected]->setP1(shapes[lastSelected]->getP1() + QPoint(0, -10));
                shapes[lastSelected]->setP2(shapes[lastSelected]->getP2() + QPoint(0, -10));
                update();
                break;
            case (Qt::Key_Down):
                shapes[lastSelected]->setP1(shapes[lastSelected]->getP1() + QPoint(0, +10));
                shapes[lastSelected]->setP2(shapes[lastSelected]->getP2() + QPoint(0, +10));
                update();
                break;
            case (Qt::Key_Left):
                shapes[lastSelected]->setP1(shapes[lastSelected]->getP1() + QPoint(-10, 0));
                shapes[lastSelected]->setP2(shapes[lastSelected]->getP2() + QPoint(-10, 0));
                update();
                break;
            case (Qt::Key_Right):
                shapes[lastSelected]->setP1(shapes[lastSelected]->getP1() + QPoint(+10, 0));
                shapes[lastSelected]->setP2(shapes[lastSelected]->getP2() + QPoint(+10, 0));
                update();
                break;
        }
    }
}

void Canvas::keyReleaseEvent(QKeyEvent *event) {
}