#include "CardLabel.h"

CardLabel::CardLabel(QString color, QString value, QWidget *parent)
    : QLabel(parent), m_color(color), m_value(value)
{
    setFixedSize(50, 70); // 牌大小


    // 加载你的素材图片
    // 例：":/cards/card_14_1.png" 黑桃A
    QString path = QString("../../Playingcards/%1%2").arg(color).arg(value);
    setPixmap(QPixmap(path).scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

CardLabel::CardLabel(QString card, QWidget *parent)
{
    setFixedSize(50, 70); // 牌大小


    // 加载你的素材图片
    // 例：":/cards/card_14_1.png" 黑桃A
    QString path = QString("../../Playingcards/%1").arg(card);
    setPixmap(QPixmap(path).scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CardLabel::mousePressEvent(QMouseEvent *ev)
{
    emit cardClicked(this);
    QLabel::mousePressEvent(ev);
}



