#include "Line.h"
#include <iostream>

void Line::draw(QPainter *p) {
    p->drawLine(*this);
}

QPoint Line::getP1() const {
    return QLineF::p1().toPoint();
}

void Line::setP1(QPoint p) {
    QLineF::setP1(p);
}

QPoint Line::getP2() const {
    return QLineF::p2().toPoint();
}

void Line::setP2(QPoint p) {
    QLineF::setP2(p);
}

bool Line::intersects(const QRect &rect) {
    QLineF line1(rect.topLeft(), rect.topRight());
    QLineF line2(rect.topRight(), rect.bottomRight());
    QLineF line3(rect.bottomRight(), rect.bottomLeft());
    QLineF line4(rect.bottomLeft(), rect.topLeft());

    return (QLineF::intersect(line1, nullptr) == QLineF::IntersectType::BoundedIntersection) ||
           (QLineF::intersect(line2, nullptr) == QLineF::IntersectType::BoundedIntersection) ||
           (QLineF::intersect(line3, nullptr) == QLineF::IntersectType::BoundedIntersection) ||
           (QLineF::intersect(line4, nullptr) == QLineF::IntersectType::BoundedIntersection);
}

