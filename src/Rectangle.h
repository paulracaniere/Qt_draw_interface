#ifndef QT_TP2_RECTANGLE_H
#define QT_TP2_RECTANGLE_H

#include "Shape.h"
#include <QRect>


class Rectangle : public Shape {
Q_OBJECT
public:
    Rectangle() = default;

    Rectangle(QPoint p1, QPoint p2) : rectangle(p1, p2) {}

    Rectangle(const Rectangle &rect) : rectangle(rect.getP1(), rect.getP2()) {}

    void draw(QPainter *) override;

    QPoint getP1() const override;

    void setP1(QPoint) override;

    QPoint getP2() const override;

    void setP2(QPoint) override;

    bool intersects(const QRect &) override;

    inline QString getClassName() const override { return "Rectangle"; }

    void write(QDataStream &) const override;

    void read(QDataStream &) override;

private:
    QRect rectangle;
};

Q_DECLARE_METATYPE(Rectangle);

#endif //QT_TP2_RECTANGLE_H
