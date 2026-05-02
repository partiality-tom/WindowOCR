#include "CardLabel.h"

CardLabel::CardLabel(QString color, QString value, QWidget *parent)
    : QLabel(parent), m_color(color), m_value(value)
{
    //setFixedSize(50, 70); // 牌大小


    // 加载你的素材图片
    // 例：":/cards/card_14_1.png" 黑桃A
    // QString path = QString("../../Playingcards/%1%2").arg(color).arg(value);
    // m_Pixmap=QPixmap(path);
    // setPixmap(m_Pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

CardLabel::CardLabel(QString card, QWidget *parent)
{
    //setFixedSize(50, 70); // 牌大小


    // 加载你的素材图片
    // 例：":/cards/card_14_1.png" 黑桃A 广
    QString path = QString("./Playingcards/%1.gif").arg(card);
    m_Pixmap=QPixmap(path);
    setPixmap(m_Pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CardLabel::mousePressEvent(QMouseEvent *ev)
{
    emit cardClicked(this);
    QLabel::mousePressEvent(ev);
}

void CardLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event); //先让 QLabel 完成它内部的基础尺寸更新工作

    updatePixmap();
}

void CardLabel::updatePixmap()
{
    if (m_Pixmap.isNull()) return;
    // 将原始图片缩放到当前 Label 的大小，保持宽高比并平滑缩放
    QPixmap scaledPixmap = m_Pixmap.scaled(
        size(),
        Qt::KeepAspectRatio,   // 保持图片原有的宽高比，不变形
        Qt::SmoothTransformation // 使用平滑算法，防止缩放后模糊或有锯齿
        );
    QLabel::setPixmap(scaledPixmap);
}

QSize CardLabel::sizeHint() const
{
    return QSize(80, 120);  // 宽度80，高度120
}



