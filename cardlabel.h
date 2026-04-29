#pragma once
#include <QLabel>
#include <QMouseEvent>

class CardLabel : public QLabel
{
    Q_OBJECT
public:
    QString m_color;  // 3~15  3-A-2-小王-大王
    QString m_value;  // 0-3花色

    explicit CardLabel(QString color, QString value, QWidget *parent = nullptr);
    explicit CardLabel(QString card, QWidget *parent = nullptr);

signals:
    void cardClicked(CardLabel*);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
};
