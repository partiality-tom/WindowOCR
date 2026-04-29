#ifndef DEALINGSCREEN_H
#define DEALINGSCREEN_H

#include <QGroupBox>
#include <QWidget>

namespace Ui {
class DealingScreen;
}

// 一张牌的结构
struct Card {
    QString color;  // 花色：Spade(黑桃) Heart(红桃) Club(梅花) Diamond(方块)
    QString value;  // 3~10 J Q K A 2 小王 大王
    int weight;      // 权值（用于排序）, 暂时没有使用到
};

class DealingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DealingScreen(QWidget *parent = nullptr);
    ~DealingScreen();

private slots:
    void on_sendCards_clicked();

private:
    Ui::DealingScreen *ui;

    // 全局/成员变量
    std::vector<Card> allCards;       // 所有54张牌
    std::vector<Card> player1Cards;   // 玩家1（地主）20张
    std::vector<Card> player2Cards;   // 玩家2（农民）17张
    std::vector<Card> player3Cards;   // 玩家3（农民）17张
    std::vector<Card> bottomCards;    // 底牌3张

    void createAllCards(); //生成牌
    void shuffleCards(); //洗牌
    void dealCards(); //发牌
    void showCards(QGroupBox* box, const std::vector<Card>& cards); //显示一组牌
};

#endif // DEALINGSCREEN_H
