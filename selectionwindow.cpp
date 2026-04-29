#include "SelectionWindow.h"

SelectionWindow::SelectionWindow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //移除边框，窗口置顶
    setAttribute(Qt::WA_TranslucentBackground); //设置窗口背景透明
    showFullScreen(); //让窗口全屏显示
    setCursor(Qt::CrossCursor); //更改鼠标光标样式，将鼠标指针变成“+”字形状
}

void SelectionWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); //除编译器关于“未使用变量”的警告。
    QPainter painter(this);

    // 全屏半透明遮罩
    //rect()：获取当前窗口的大小（即全屏大小
    painter.fillRect(rect(), QColor(0,0,0,120));

    if(isSelecting){
        QRect selRect(startPoint, endPoint);
        // 选中区域透明
        // 2. 【关键修改】设置混合模式为“擦除”
        painter.setCompositionMode(QPainter::CompositionMode_Clear);

        // 3. 用任意颜色填充选区，因为混合模式会将其变为透明
        // 这一步相当于在遮罩上“挖”了一个洞
        painter.fillRect(selRect, Qt::white);

        // 4. 【重要】恢复为默认的“绘制”模式，否则后续绘制都会是“擦除”
       painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

        // 画红色边框
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(selRect);
    }
}

void SelectionWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        startPoint = event->globalPos();
        endPoint = startPoint;
        isSelecting = true;
    }
}

void SelectionWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isSelecting){
        endPoint = event->globalPos();
        update(); //发送请求重新绘制界面，稍后绘制
    }
}

void SelectionWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    // 1. 标记选区完成
    selectionDone = true;
    isSelecting = false;
    QRect rect(startPoint, endPoint);
    emit selected(rect.normalized()); //规范化矩形，防止用户反向拖拽造成得到的矩形宽/高为负。
    //close(); //关闭窗口
}
