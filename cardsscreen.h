#ifndef CARDSSCREEN_H
#define CARDSSCREEN_H

#include <QGroupBox>
#include <QWidget>

// 一张牌的结构
struct Card {
    QString color;  // 花色，也可充当点数和花色（例如红2）
    QString value;  // 点数
    int weight;     // 权值（用于排序），目前没使用到
};


namespace Ui {
class CardsScreen;
}

class CardsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CardsScreen(QWidget *parent = nullptr);
    ~CardsScreen();

    void Automaticdealing(QStringList cards);  //识别到文字后自动发牌
    void Handledeal();  //发牌逻辑
private slots:
    void on_btn_dealCards_clicked(); //发牌槽函数


private:
    Ui::CardsScreen *ui;

    std::vector<Card> m_allCards;       // 所有54张牌
    std::vector<Card> m_player1Cards;   // 玩家1
    std::vector<Card> m_player2Cards;   // 玩家2
    std::vector<Card> m_player3Cards;   // 玩家3
    std::vector<Card> m_player4Cards;   // 玩家4
    std::vector<Card> m_player5Cards;   // 玩家5
    std::vector<Card> m_player6Cards;   // 玩家6



    void createAllCards();  //生成所有的牌
    void shuffleCards(); //洗牌
    void dealCards();   //发牌
    void showCards(QGroupBox* box, const std::vector<Card>& cards); //显示一组牌
};

#endif // CARDSSCREEN_H
