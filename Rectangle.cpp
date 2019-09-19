#include "Rectangle.h"

void Rectangle::draw(QPainter *p) {
    p->drawRect(*this);
}

QPoint Rectangle::getP1() const {
    return QRect::topLeft();
}

void Rectangle::setP1(QPoint p) {
    QRect::setTopLeft(p);
}

QPoint Rectangle::getP2() const {
    return QRect::bottomRight();
}

void Rectangle::setP2(QPoint p) {
    QRect::setBottomRight(p);
}

bool Rectangle::intersects(const QRect &rect) {
    return QRect::intersects(rect);
}
