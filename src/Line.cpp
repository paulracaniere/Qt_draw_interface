#include "Line.h"

void Line::draw(QPainter *p) {
    if (isSelected()) {
        QPen pen = p->pen();
        QBrush brush = p->brush();
        p->setPen(Qt::black);
        p->setPen(Qt::DashLine);
        p->setBrush(Qt::NoBrush);
        p->drawLine(*this);
        p->setPen(pen);
        p->setBrush(brush);
    } else {
        p->drawLine(*this);
    }
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
