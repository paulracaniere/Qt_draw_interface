#include "Canvas.h"
#include <QPainter>
#include <QMessageBox>

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
    // Window size
    setMinimumSize(800, 600);

    // Set focus to strong for mouse and keyboard inputs
    setFocusPolicy(Qt::StrongFocus);

    // Background color
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    // Cursor
    setCursor(Qt::ArrowCursor);
}

void Canvas::paintEvent(QPaintEvent *e) {
    // Standard behavior
    QWidget::paintEvent(e);

    // Create a painter for this canvas
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draws shapes one at the time
    for (auto i = 0; i < shapes.size(); i++) {
        painter.setPen(*pens[i]);
        painter.setBrush(*brushes[i]);
        shapes[i]->draw(&painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    // Handles clicking
    if (event->buttons() & Qt::LeftButton) {

        // Initializes selection to none
        if (lastSelected != -1) {
            shapes[lastSelected]->setSelected(false);
            lastSelected = -1;
            update();
        }

        if (mouseMod == SELECTION && !shapes.isEmpty()) {
            // Tests which object is selected
            lastMousePosition = event->pos();
            QRect selectionRect(lastMousePosition - QPoint(10, 10), lastMousePosition + QPoint(10, 10));
            for (auto i = shapes.size() - 1; i >= 0; i--) {
                if (shapes[i]->intersects(selectionRect)) {
                    lastSelected = i;
                    shapes[lastSelected]->setSelected(true);
                    break;
                }
            }
            if (lastSelected != -1) update();
        } else if (mouseMod == PEN) {
            // Starts to draw a line
            shapes.append(new Line(event->pos(), event->pos()));
            pens.append(new QPen(penColor, penSize, penStyle, penCapStyle, penJoinStyle));
            brushes.append(new QBrush(penColor, brushStyle));
            update();
        } else if (mouseMod == RECTANGLE) {
            // Starts to draw a rectangle
            shapes.append(new Rectangle(event->pos(), event->pos()));
            pens.append(new QPen(penColor, penSize, penStyle, penCapStyle, penJoinStyle));
            brushes.append(new QBrush(penColor, brushStyle));
            update();
        } else if (mouseMod == ELLIPSE) {
            // Starts to draw an ellipse
            shapes.append(new Ellipse(event->pos(), event->pos()));
            pens.append(new QPen(penColor, penSize, penStyle, penCapStyle, penJoinStyle));
            brushes.append(new QBrush(penColor, brushStyle));
            update();
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    // Handles dragging
    if (event->buttons() & Qt::LeftButton) {
        if (mouseMod == SELECTION && lastSelected != -1) {
            // Moves the last selected object
            Shape *shape = shapes[lastSelected];
            QPoint newMousePosition = event->pos();
            shape->setP1(shape->getP1() + (newMousePosition - lastMousePosition));
            shape->setP2(shape->getP2() + (newMousePosition - lastMousePosition));
            lastMousePosition = newMousePosition;
            update();
        } else if (mouseMod == PEN || mouseMod == RECTANGLE || mouseMod == ELLIPSE) {
            // Continues the shape
            Shape *shape = shapes.last();
            shape->setP2(event->pos());
            update();
        }
    }
}

void Canvas::setMouseMod(QAction *action) {
    // Sets mouse mod accordingly to the action group data
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
        mouseMod = ELLIPSE;
        setCursor(Qt::CrossCursor);
    }
}

QColor Canvas::getColor() const {
    // Returns color of the tool
    return penColor;
}

void Canvas::setColor(const QColor &color) {
    // Sets the color of the tool
    penColor = color;

    // Changes the color of the last selected object if it exists
    if (lastSelected != -1) {
        pens[lastSelected]->setColor(penColor);
        brushes[lastSelected]->setColor(penColor);
        update();
    }
}

void Canvas::setBrushFill(bool toFill) {
    // Changes the filling mode
    if (toFill) brushStyle = Qt::SolidPattern;
    else brushStyle = Qt::NoBrush;

    // Changes the filling mode of the last selected object if it exists
    if (lastSelected != -1) {
        brushes[lastSelected]->setStyle(brushStyle);
        update();
    }
}

void Canvas::setPenStyle(QAction *action) {
    // Changes the line style
    QVariant data = action->data();
    if (data == 0) penStyle = Qt::SolidLine;
    else if (data == 1) penStyle = Qt::DashLine;
    else if (data == 2) penStyle = Qt::DotLine;
    else if (data == 3) penStyle = Qt::DashDotLine;
    else penStyle = Qt::DashDotDotLine;

    // Changes the line style of the last selected object if it exists
    if (lastSelected != -1) {
        pens[lastSelected]->setStyle(penStyle);
        update();
    }
}

void Canvas::setPenCapStyle(QAction *action) {
    // Changes the cap style
    QVariant data = action->data();
    if (data == 0) penCapStyle = Qt::FlatCap;
    else if (data == 1) penCapStyle = Qt::SquareCap;
    else if (data == 2) penCapStyle = Qt::RoundCap;
    else penCapStyle = Qt::MPenCapStyle;

    // Changes the cap style of the last selected object if it exists
    if (lastSelected != -1) {
        pens[lastSelected]->setCapStyle(penCapStyle);
        update();
    }
}

void Canvas::setPenJoinStyle(QAction *action) {
    // Changes the join style
    QVariant data = action->data();
    if (data == 0) penJoinStyle = Qt::MiterJoin;
    else if (data == 1) penJoinStyle = Qt::BevelJoin;
    else if (data == 2) penJoinStyle = Qt::RoundJoin;
    else if (data == 3) penJoinStyle = Qt::SvgMiterJoin;
    else penJoinStyle = Qt::MPenJoinStyle;

    // Changes the join style of the last selected object if it exists
    if (lastSelected != -1) {
        pens[lastSelected]->setJoinStyle(penJoinStyle);
        update();
    }
}

void Canvas::setLineWidth(int width) {
    // Changes the line width
    if (width != penSize) penSize = width;

    // Changes the line width of the last selected object if it exists
    if (lastSelected != -1) {
        pens[lastSelected]->setWidth(width);
        update();
    }
}

void Canvas::deleteLastShape() {
    // Deletes the last drawn shape if it exists
    if (!shapes.isEmpty()) {
        if (lastSelected == shapes.size() - 1) lastSelected = -1;

        shapes.removeLast();
        pens.removeLast();
        brushes.removeLast();

        update();
    }
}

void Canvas::deleteAllShapes() {
    // Deletes all shapes (with question box) if any shape is drawn
    if (!shapes.isEmpty() && QMessageBox::question(this, tr("Delete?"), tr("Are you sure you want to delete all?")) ==
                             QMessageBox::No)
        return;

    bool isToBeUpdated = false;
    while (!shapes.isEmpty()) {
        shapes.removeLast();
        pens.removeLast();
        brushes.removeLast();
        isToBeUpdated = true;
        lastSelected = -1;
    }
    if (isToBeUpdated) update();
}

void Canvas::keyPressEvent(QKeyEvent *event) {
    // Handles key pressing events
    if (lastSelected != -1) {
        switch (event->key()) {
            // The four following arrows are used to move the shape
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
                // When hitting backspace key, the last selected shape is deleted
            case (Qt::Key_Backspace):
                shapes.removeAt(lastSelected);
                lastSelected = -1;
                update();
        }
    }
}
