#include "Ellipse.h"

void Ellipse::draw(QPainter *p) {
    p->drawEllipse(rectangle);
    if (isSelected()) {
        QPen pen = p->pen();
        QBrush brush = p->brush();
        p->setPen(Qt::black);
        p->setPen(Qt::DashLine);
        p->setBrush(Qt::NoBrush);
        int pos_offset = 3 + pen.width() / 2;
        int size_offset = 6 + pen.width();
        p->drawRect(rectangle.x() - pos_offset, rectangle.y() - pos_offset,
                    rectangle.width() + size_offset, rectangle.height() + size_offset);
        p->setPen(pen);
        p->setBrush(brush);
    }
}

QPoint Ellipse::getP1() const {
    return rectangle.topLeft();
}

void Ellipse::setP1(QPoint p) {
    rectangle.setTopLeft(p);
}

QPoint Ellipse::getP2() const {
    return rectangle.bottomRight();
}

void Ellipse::setP2(QPoint p) {
    rectangle.setBottomRight(p);
}

bool Ellipse::intersects(const QRect &rect) {
    return rectangle.intersects(rect);
}

void Ellipse::write(QDataStream &out) const {
    out << getClassName();
    out << rectangle;
}

void Ellipse::read(QDataStream &in) {
    in >> rectangle;
}
