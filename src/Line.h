#ifndef QT_TP2_LINE_H
#define QT_TP2_LINE_H

#include <QLineF>
#include "Shape.h"

class Line : public Shape {
Q_OBJECT
public:
    Line() = default;

    Line(QPoint p1, QPoint p2) : line(p1, p2) {}

    Line(const Line &line) : line(line.getP1(), line.getP2()) {}

    QPoint getP1() const override;

    void setP1(QPoint) override;

    QPoint getP2() const override;

    void setP2(QPoint) override;

    void draw(QPainter *) override;

    bool intersects(const QRect &) override;

    inline QString getClassName() const override { return "Line"; }

    void write(QDataStream &) const override;

    void read(QDataStream &) override;

private:
    QLineF line;
};

Q_DECLARE_METATYPE(Line);

#endif //QT_TP2_LINE_H
