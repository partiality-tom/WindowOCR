#ifndef CARDSSCREEN_H
#define CARDSSCREEN_H

#include <QGroupBox>
#include <QWidget>

// 一张牌的结构
struct Card {
    QString color;  // 花色：Spade(黑桃) Heart(红桃) Club(梅花) Diamond(方块)
    QString value;  // 3~10 J Q K A 2 小王 大王
    int weight;      // 权值（用于排序），目前没使用到
};

struct StrCard
{
    QString card; //一张牌,适配成员
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
private slots:
    void on_btn_dealCards_clicked();


private:
    Ui::CardsScreen *ui;

    std::vector<Card> m_allCards;       // 所有54张牌
    std::vector<Card> m_player1Cards;   // 玩家1（地主）20张
    std::vector<Card> m_player2Cards;   // 玩家2（农民）17张
    std::vector<Card> m_player3Cards;   // 玩家3（农民）17张
    std::vector<Card> m_bottomCards;    // 底牌3张

    void createAllCards();  //生成所有的牌
    void shuffleCards(); //洗牌
    void dealCards();   //发牌
    void showCards(QGroupBox* box, const std::vector<Card>& cards); //显示一组牌
};

#endif // CARDSSCREEN_H
