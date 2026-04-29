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
    connect(ui->comboBoxPersonNum,QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidget,&QStackedWidget::setCurrentIndex);
}

CardsScreen::~CardsScreen()
{
    delete ui;
}

void CardsScreen::on_btn_dealCards_clicked()
{
    //createAllCards();   // 生成牌
    //shuffleCards();     // 洗牌
    dealCards();        // 发牌

    // 显示到三个玩家区域（你要改成自己的 groupBox 名字）
    showCards(ui->groupBox_41, m_player1Cards); // 地主
    showCards(ui->groupBox_42, m_player2Cards); // 农民
    showCards(ui->groupBox_43, m_player3Cards); // 农民
    showCards(ui->groupBox_44, m_player4Cards);   // 底牌
}

void CardsScreen::Automaticdealing(QStringList cards)
{


    m_allCards.clear();

    //遍历牌识别到的牌，生成Card
    for (const QString& card : cards) {
        //qDebug()<<card;
        m_allCards.push_back({card});
    }

    //识别到牌后显示
    showCards(ui->AllCards, m_allCards);

    Handledeal(); //发牌
    //洗牌逻辑，忽略，可参考 shuffleCards();

    //发牌逻辑，一个玩家顺序发三张(只做示例)
    // for (int i=0; i<3; i++) {
    //     m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
    //     m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
    //     m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
    // }

    // showCards(ui->groupBox_11, m_player1Cards); // 地主
    // showCards(ui->groupBox_12, m_player2Cards); // 农民
    // showCards(ui->groupBox_13, m_player3Cards); // 农民

}

void CardsScreen::Handledeal()
{

    //获取参数设置的牌
    QString targetCard;
    QString targetCardSuit=ui->comboBoxSuit->currentText();
    QString targetCardValue=ui->comboBoxValue->currentText();
    if(targetCardValue=="小王" || targetCardValue=="大王")
    {
        targetCard=targetCardValue;
    }
    targetCard=targetCardSuit+targetCardValue;


    // 2. 遍历所有牌，找到目标牌的位置
    int startIndex = -1;
    for (int i = 0; i < m_allCards.size(); ++i) {
        if (m_allCards[i].color == targetCard) {
            startIndex = i;

            break; // 找到第一张匹配的就退出
        }
    }
    qDebug()<<"startIndex:"<<startIndex;


    // 如果没有找到目标牌，或者剩下的牌不够发（比如找到的是倒数第2张，后面根本不够跳过4张再发牌），直接返回
    if (startIndex == -1 || startIndex + 4 >= m_allCards.size()) {
        return;
    }

    //删除参数牌之前的牌，以及后续三张，留下需要发的牌
    m_allCards.erase(m_allCards.begin(), m_allCards.begin() + startIndex+4); //erase删除不含尾


    //开始发牌存入各种变量
    int personNum=ui->comboBoxPersonNum->currentIndex()+2; //当前索引加2，为实际玩家数量
    switch(personNum)
    {
    case 2:
        for(int i=0; i<2 && m_allCards.size()>1; i++)  //当前牌需要大于1才发
        {
            m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        }

        showCards(ui->groupBox_21, m_player1Cards);
        showCards(ui->groupBox_22, m_player2Cards);
        break;

    case 3:
        for(int i=0; i<2 && m_allCards.size()>2; i++)
        {
            m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        }
        showCards(ui->groupBox_31, m_player1Cards);
        showCards(ui->groupBox_32, m_player2Cards);
        showCards(ui->groupBox_33, m_player3Cards);
        break;

    case 4:
        for(int i=0; i<2 && m_allCards.size()>3; i++)
        {
            m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player4Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        }
        showCards(ui->groupBox_41, m_player1Cards);
        showCards(ui->groupBox_42, m_player2Cards);
        showCards(ui->groupBox_43, m_player3Cards);
        showCards(ui->groupBox_44, m_player4Cards);
        break;

    case 5:
        for(int i=0; i<2 && m_allCards.size()>4; i++)
        {
            m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player4Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player5Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        }
        showCards(ui->groupBox_51, m_player1Cards);
        showCards(ui->groupBox_52, m_player2Cards);
        showCards(ui->groupBox_53, m_player3Cards);
        showCards(ui->groupBox_54, m_player4Cards);
        showCards(ui->groupBox_55, m_player5Cards);
        break;

    case 6:
        for(int i=0; i<2 && m_allCards.size()>5; i++)
        {
            m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player4Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player5Cards.push_back(m_allCards.back()); m_allCards.pop_back();
            m_player6Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        }
        showCards(ui->groupBox_61, m_player1Cards);
        showCards(ui->groupBox_62, m_player2Cards);
        showCards(ui->groupBox_63, m_player3Cards);
        showCards(ui->groupBox_64, m_player4Cards);
        showCards(ui->groupBox_65, m_player5Cards);
        showCards(ui->groupBox_66, m_player6Cards);

        break;
    }

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
    m_player4Cards.clear();
    m_player5Cards.clear();
    m_player6Cards.clear();




    // 轮流发 17 轮，每人17张
    for (int i=0; i<17; i++) {
        m_player2Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        m_player3Cards.push_back(m_allCards.back()); m_allCards.pop_back();
        m_player1Cards.push_back(m_allCards.back()); m_allCards.pop_back();
    }

    // 剩下3张底牌
    // m_bottomCards.push_back(m_allCards[0]);
    // m_bottomCards.push_back(m_allCards[1]);
    // m_bottomCards.push_back(m_allCards[2]);

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
        CardLabel* label = new CardLabel(card.color);
        layout->addWidget(label);
    }
}

