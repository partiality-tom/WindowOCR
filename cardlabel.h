#pragma once
#include <QLabel>
#include <QMouseEvent>

class CardLabel : public QLabel
{
    Q_OBJECT
public:
    QString m_color;  // 花色，也可充当花色和点数
    QString m_value;  // 点数
    QPixmap m_Pixmap;

    explicit CardLabel(QString color, QString value, QWidget *parent = nullptr);
    explicit CardLabel(QString card, QWidget *parent = nullptr);

signals:
    void cardClicked(CardLabel*);

protected:
    void mousePressEvent(QMouseEvent *ev) override;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event); //当控件的宽或高发生实际改变时才会被调用。
    void updatePixmap();

    // QWidget interface
public:
    QSize sizeHint() const;
};
