#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class SelectionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SelectionWindow(QWidget *parent = nullptr);

signals:
    void selected(QRect rect);

protected:
    //当窗口需要重绘（比如刚显示、被遮挡后恢复、或调用 update()）时，系统会自动调用这个函数。
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint startPoint;
    QPoint endPoint;
    bool isSelecting = false;
    bool selectionDone = false;
};

#endif // SELECTIONWINDOW_H
