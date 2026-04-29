#pragma once
#include <QLabel>
#include <QMouseEvent>

class CardLabel : public QLabel
{
    Q_OBJECT
public:
    QString m_color;  // 花色，也可充当花色和点数
    QString m_value;  // 点数

    explicit CardLabel(QString color, QString value, QWidget *parent = nullptr);
    explicit CardLabel(QString card, QWidget *parent = nullptr);

signals:
    void cardClicked(CardLabel*);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
};
