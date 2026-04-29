#include "cardsscreen.h"
#include "ui_cardsscreen.h"
#include "cardlabel.h"
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QDebug>

CardsScreen::CardsScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardsScreen)
{
    ui->setupUi(this);

}

CardsScreen::~CardsScreen()
{
    delete ui;
}

void CardsScreen::on_btn_dealCards_clicked()
{
    createAllCards();   // 生成牌
    shuffleCards();     // 洗牌
    dealCards();        // 发牌

    // 显示到三个玩家区域（你要改成自己的 groupBox 名字）
    showCards(ui->groupBox_11, m_player1Cards); // 地主
    showCards(ui->groupBox_12, m_player2Cards); // 农民
    showCards(ui->groupBox_13, m_player3Cards); // 农民
    showCards(ui->groupBox_14, m_bottomCards);   // 底牌
}

void CardsScreen::Automaticdealing(QStringList cards)
{


    m_allCards.clear();

    //遍历牌识别到的牌，生成Card
    for (const QString& card : cards) {
        qDebug()<<card;
        m_allCards.push_back({card});
    }

    //洗牌逻辑，忽略，可参考 shuffleCards();

    //发牌逻辑，一个玩家顺序发三张(只做示例)
    for (int i=0; i<3; i++) {
        m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
    }

    showCards(ui->groupBox_11, m_player1Cards); // 地主
    showCards(ui->groupBox_12, m_player2Cards); // 农民
    showCards(ui->groupBox_13, m_player3Cards); // 农民

}

void CardsScreen::createAllCards()
{
    m_allCards.clear();
    QStringList colors = {"Spade", "Heart", "Club", "Diamond"};
    QStringList values = {"3","4","5","6","7","8","9","10","J","Q","K","A","2"};

    // 生成普通牌
    int weight = 1;
    for (const QString& v : values) {
        for (const QString& c : colors) {
            m_allCards.push_back({c, v, weight});
        }
        weight++;
    }

    // 加入王
    m_allCards.push_back({"JOKER-", "B", weight++}); // 小王
    m_allCards.push_back({"JOKER-", "A", weight++}); // 大王
}

void CardsScreen::shuffleCards()
{
    std::shuffle(m_allCards.begin(), m_allCards.end(), *QRandomGenerator::global());
}

void CardsScreen::dealCards()
{
    // 清空
    m_player1Cards.clear();
    m_player2Cards.clear();
    m_player3Cards.clear();
    m_bottomCards.clear();

    // 轮流发 17 轮，每人17张
    for (int i=0; i<17; i++) {
        m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
    }

    // 剩下3张底牌
    m_bottomCards.push_back(m_allCards[0]);
    m_bottomCards.push_back(m_allCards[1]);
    m_bottomCards.push_back(m_allCards[2]);

    // 地主多拿3张（player1 = 地主）
    // m_player1Cards.push_back(m_allCards[0]);
    // m_player1Cards.push_back(m_allCards[1]);
    // m_player1Cards.push_back(m_allCards[2]);
}

void CardsScreen::showCards(QGroupBox *box, const std::vector<Card> &cards)
{
    // 清空旧布局
    //delete box->layout();

    qDeleteAll(box->findChildren<QLabel*>());
    if (box->layout()) {
        delete box->layout();
    }

    QHBoxLayout* layout = new QHBoxLayout(box);
    layout->setSpacing(-100); // 重叠，目前没生效
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0,0,-10,0);

    // 创建牌控件
    for (const Card& card : cards) {
        CardLabel* label = new CardLabel(card.color, card.value);
        layout->addWidget(label);
    }
}

