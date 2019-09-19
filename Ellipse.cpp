#include "Ellipse.h"

void Ellipse::draw(QPainter *p) {
    p->drawEllipse(*this);
}

QPoint Ellipse::getP1() const {
    return QRect::topLeft();
}

void Ellipse::setP1(QPoint p) {
    QRect::setTopLeft(p);
}

QPoint Ellipse::getP2() const {
    return QRect::bottomRight();
}

void Ellipse::setP2(QPoint p) {
    QRect::setBottomRight(p);
}

bool Ellipse::intersects(const QRect &rect) {
    return QRect::intersects(rect);
}
