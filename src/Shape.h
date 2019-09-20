#ifndef QT_TP2_SHAPE_H
#define QT_TP2_SHAPE_H

#include <QPainter>
#include <QPoint>

// Abstract class shape to designate any shape to draw on canvas
class Shape : public QObject {
Q_OBJECT
public:
    virtual void draw(QPainter *) = 0;

    virtual QPoint getP1() const = 0;

    virtual void setP1(QPoint) = 0;

    virtual QPoint getP2() const = 0;

    virtual void setP2(QPoint) = 0;

    virtual bool intersects(const QRect &) = 0;

    bool isSelected() { return selected; };

    void setSelected(bool isSelected) { selected = isSelected; }

private:
    bool selected = false;
};


#endif //QT_TP2_SHAPE_H
