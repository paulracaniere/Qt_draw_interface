#include "Rectangle.h"
#include <QVariant>

void Rectangle::draw(QPainter *p) {
    p->drawRect(rectangle);
    if (isSelected()) {
        QPen pen = p->pen();
        QBrush brush = p->brush();
        p->setPen(Qt::black);
        p->setPen(Qt::DashLine);
        p->setBrush(Qt::NoBrush);
        int offset = 3 + pen.width() / 2;
        int doffset = 6 + pen.width();
        p->drawRect(rectangle.x() - offset, rectangle.y() - offset,
                    rectangle.width() + doffset, rectangle.height() + doffset);
        p->setPen(pen);
        p->setBrush(brush);
    }
}

QPoint Rectangle::getP1() const {
    return rectangle.topLeft();
}

void Rectangle::setP1(QPoint p) {
    rectangle.setTopLeft(p);
}

QPoint Rectangle::getP2() const {
    return rectangle.bottomRight();
}

void Rectangle::setP2(QPoint p) {
    rectangle.setBottomRight(p);
}

bool Rectangle::intersects(const QRect &rect) {
    return rectangle.intersects(rect);
}

void Rectangle::write(QDataStream &out) const {
    out << getClassName();
    out << rectangle;
}

void Rectangle::read(QDataStream &in) {
    in >> rectangle;
}
