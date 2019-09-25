#include "Line.h"

void Line::draw(QPainter *p) {
    if (isSelected()) {
        QPen pen = p->pen();
        QBrush brush = p->brush();
        p->setPen(Qt::black);
        p->setPen(Qt::DashLine);
        p->setBrush(Qt::NoBrush);
        p->drawLine(line);
        p->setPen(pen);
        p->setBrush(brush);
    } else {
        p->drawLine(line);
    }
}

QPoint Line::getP1() const {
    return line.p1().toPoint();
}

void Line::setP1(QPoint p) {
    line.setP1(p);
}

QPoint Line::getP2() const {
    return line.p2().toPoint();
}

void Line::setP2(QPoint p) {
    line.setP2(p);
}

bool Line::intersects(const QRect &rect) {
    QLineF line1(rect.topLeft(), rect.topRight());
    QLineF line2(rect.topRight(), rect.bottomRight());
    QLineF line3(rect.bottomRight(), rect.bottomLeft());
    QLineF line4(rect.bottomLeft(), rect.topLeft());

    return (line.intersect(line1, nullptr) == QLineF::IntersectType::BoundedIntersection) ||
           (line.intersect(line2, nullptr) == QLineF::IntersectType::BoundedIntersection) ||
           (line.intersect(line3, nullptr) == QLineF::IntersectType::BoundedIntersection) ||
           (line.intersect(line4, nullptr) == QLineF::IntersectType::BoundedIntersection);
}

void Line::write(QDataStream &out) const {
    out << getClassName();
    out << line;
}

void Line::read(QDataStream &in) {
    in >> line;
}
