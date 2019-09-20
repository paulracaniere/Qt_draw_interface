#ifndef QT_TP2_RECTANGLE_H
#define QT_TP2_RECTANGLE_H

#include "Shape.h"
#include <QRect>


class Rectangle : public Shape, QRect {
Q_OBJECT
public:
    Rectangle(QPoint p1, QPoint p2) : QRect(p1, p2) {}

    void draw(QPainter *) override;

    QPoint getP1() const override;

    void setP1(QPoint) override;

    QPoint getP2() const override;

    void setP2(QPoint) override;

    bool intersects(const QRect &) override;
};


#endif //QT_TP2_RECTANGLE_H
