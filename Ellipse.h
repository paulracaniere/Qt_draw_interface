//
// Created by Paul Racanière on 18/09/2019.
//

#ifndef QT_TP2_ELLIPSE_H
#define QT_TP2_ELLIPSE_H

#include "Shape.h"
#include <QRect>


class Ellipse : public Shape, QRect {
public:
    Ellipse(QPoint p1, QPoint p2) : QRect(p1, p2) {}

    void draw(QPainter *) override;

    QPoint getP1() const override;

    void setP1(QPoint) override;

    QPoint getP2() const override;

    void setP2(QPoint) override;

    bool intersects(const QRect &) override;
};


#endif //QT_TP2_ELLIPSE_H
