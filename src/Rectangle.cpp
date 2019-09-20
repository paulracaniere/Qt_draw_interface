#include "Rectangle.h"

void Rectangle::draw(QPainter *p) {
    p->drawRect(*this);
    if (isSelected()) {
        QPen pen = p->pen();
        QBrush brush = p->brush();
        p->setPen(Qt::black);
        p->setPen(Qt::DashLine);
        p->setBrush(Qt::NoBrush);
        int offset = 3 + pen.width() / 2;
        int doffset = 6 + pen.width();
        p->drawRect(this->x() - offset, this->y() - offset, this->width() + doffset, this->height() + doffset);
        p->setPen(pen);
        p->setBrush(brush);
    }
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
