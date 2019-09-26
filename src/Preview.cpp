#include "Preview.h"
#include <QPainter>

class MiniDrawingZone : public QWidget {
public:
    explicit MiniDrawingZone(QWidget *parent = nullptr, Canvas *canvas = nullptr) : QWidget(parent), canvas(canvas) {}

protected:
    void paintEvent(QPaintEvent *e) override {
        // Standard behavior
        QWidget::paintEvent(e);

        // Create a painter for this canvas
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QColor color = canvas->getColor();
        QPen pen = canvas->getPen();
        pen.setColor(color);
        QBrush brush = canvas->getBrush();
        brush.setColor(color);
        painter.setPen(pen);
        painter.setBrush(brush);

        int margin = 10 + pen.width() / 2;

        painter.drawRect(this->rect().marginsRemoved(QMargins(margin, margin, margin, margin)));
    }

private:
    Canvas *canvas;
};

Preview::Preview(QWidget *parent, Canvas *canvas) : QDialog(parent), ui(new Ui::Preview), canvas(canvas) {
    ui->setupUi(this);

    // Background color
    QPalette pal = ui->frame->palette();
    pal.setColor(QPalette::Background, Qt::white);
    ui->horizontalLayout->removeWidget(ui->drawing_widget);
    ui->drawing_widget = new MiniDrawingZone(ui->frame, canvas);
    ui->horizontalLayout->addWidget(ui->drawing_widget);
    ui->frame->setAutoFillBackground(true);
    ui->frame->setPalette(pal);

    ui->drawing_widget->update();
}
