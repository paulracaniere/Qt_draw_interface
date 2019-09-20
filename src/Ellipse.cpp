#include "Ellipse.h"

void Ellipse::draw(QPainter *p) {
    p->drawEllipse(*this);
    if (isSelected()) {
        QPen pen = p->pen();
        QBrush brush = p->brush();
        p->setPen(Qt::black);
        p->setPen(Qt::DashLine);
        p->setBrush(Qt::NoBrush);
        int pos_offset = 3 + pen.width() / 2;
        int size_offset = 6 + pen.width();
        p->drawRect(this->x() - pos_offset, this->y() - pos_offset,
                    this->width() + size_offset, this->height() + size_offset);
        p->setPen(pen);
        p->setBrush(brush);
    }
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
