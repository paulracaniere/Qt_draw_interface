#ifndef QT_TP2_ELLIPSE_H
#define QT_TP2_ELLIPSE_H

#include "Shape.h"
#include <QRect>

class Ellipse : public Shape {
Q_OBJECT
public:
    Ellipse() = default;

    Ellipse(QPoint p1, QPoint p2) : rectangle(p1, p2) {}

    Ellipse(const Ellipse &ellipse) : rectangle(ellipse.getP1(), ellipse.getP2()) {}

    void draw(QPainter *) override;

    QPoint getP1() const override;

    void setP1(QPoint) override;

    QPoint getP2() const override;

    void setP2(QPoint) override;

    bool intersects(const QRect &) override;

    inline QString getClassName() const override { return "Ellipse"; }

    void write(QDataStream &) const override;

    void read(QDataStream &) override;

private:
    QRect rectangle;
};

Q_DECLARE_METATYPE(Ellipse);

#endif //QT_TP2_ELLIPSE_H
