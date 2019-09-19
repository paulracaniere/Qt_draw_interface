//
// Created by Paul Racanière on 18/09/2019.
//

#ifndef QT_TP2_LINE_H
#define QT_TP2_LINE_H

#include <QLineF>
#include "Shape.h"

class Line : public Shape, QLineF {
public:
    Line(QPoint p1, QPoint p2) : QLineF(p1, p2) {}

    QPoint getP1() const override;

    void setP1(QPoint) override;

    QPoint getP2() const override;

    void setP2(QPoint) override;

    void draw(QPainter *) override;

    bool intersects(const QRect &) override;
};

#endif //QT_TP2_LINE_H
