#include "dealingscreen.h"
#include "ui_dealingscreen.h"
#include "cardlabel.h"
#include <QGridLayout>
#include <QRandomGenerator>
#include <QDebug>

DealingScreen::DealingScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DealingScreen)
{
    ui->setupUi(this);

/*
    // ================== 1. 自己（底部，水平重叠）==================
    QWidget *selfArea = new QWidget(this);
    QHBoxLayout *selfLayout = new QHBoxLayout(selfArea);
    selfLayout->setSpacing(-80);
    selfLayout->setAlignment(Qt::AlignCenter);

    // 自己的牌（正面显示）
    CardLabel *c1 = new CardLabel("Club", "2");
    CardLabel *c2 = new CardLabel("Diamond", "2");
    selfLayout->addWidget(c1);
    selfLayout->addWidget(c2);

    // ================== 2. 左侧玩家（垂直，牌背）==================
    QWidget *leftArea = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftArea);
    leftLayout->setSpacing(2);
    leftLayout->setAlignment(Qt::AlignTop);

    // 左侧17张牌背
    // for (int i = 0; i < 17; i++) {
    //     CardLabel *back = new CardLabel("-1", "-1");
    //     back->setPixmap(QPixmap("E:/GIF/Background.gif"));
    //     back->setFixedSize(150, 100); // 固定牌大小
    //     leftLayout->addWidget(back);
    // }

    CardLabel *c1_l = new CardLabel("Club", "4");
    CardLabel *c2_l = new CardLabel("Diamond", "6");
    leftLayout->addWidget(c1_l);
    leftLayout->addWidget(c2_l);

    // ================== 3. 右侧玩家（垂直，牌背）==================
    QWidget *rightArea = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightArea); // 这里修复了！
    rightLayout->setSpacing(2);
    rightLayout->setAlignment(Qt::AlignTop);

    // 右侧17张牌背
    // for (int i = 0; i < 17; i++) {
    //     CardLabel *back_r = new CardLabel("-1", "-1");
    //     back_r->setPixmap(QPixmap("E:/GIF/Background.gif"));
    //     back_r->setFixedSize(70, 100);
    //     rightLayout->addWidget(back_r);
    // }
    CardLabel *c1_r = new CardLabel("Heart", "J");
    CardLabel *c2_r = new CardLabel("Heart", "K");
    rightLayout->addWidget(c1_r);
    rightLayout->addWidget(c2_r);



    // ================== 4. 下家（顶部，水平牌背）==================
    QWidget *topArea = new QWidget(this);
    QHBoxLayout *topLayout = new QHBoxLayout(topArea);
    topLayout->setSpacing(2);
    topLayout->setAlignment(Qt::AlignCenter);

    // 顶部17张牌背
    // for (int i = 0; i < 17; i++) {
    //     CardLabel *back_t = new CardLabel("-1", "-1");
    //     back_t->setPixmap(QPixmap("E:/GIF/Background.gif"));
    //     back_t->setFixedSize(70, 100);
    //     topLayout->addWidget(back_t);
    // }

    CardLabel *c1_t = new CardLabel("JOKER-", "A");
    CardLabel *c2_t = new CardLabel("JOKER-", "B");
    topLayout->addWidget(c1_t);
    topLayout->addWidget(c2_t);

    // ================== 5. 中间底牌（3张）==================
    QWidget *diPaiArea = new QWidget(this);
    QHBoxLayout *diPaiLayout = new QHBoxLayout(diPaiArea); // 这里修复了！
    diPaiLayout->setSpacing(5);
    diPaiLayout->setAlignment(Qt::AlignCenter);

    // 3张底牌
    for (int i = 0; i < 3; i++) {
        CardLabel *diPai = new CardLabel("-1", "-1");
        diPai->setPixmap(QPixmap("E:/GIF/Background.gif"));
        diPai->setFixedSize(70, 100);
        diPaiLayout->addWidget(diPai);
    }

    // ================== 主布局：3人斗地主标准布局 ==================
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(20);

    mainLayout->addWidget(topArea,    0, 1, Qt::AlignHCenter);      // 顶部
    mainLayout->addWidget(leftArea,   1, 0, Qt::AlignLeft | Qt::AlignTop);    // 左
    mainLayout->addWidget(rightArea,  1, 2, Qt::AlignRight | Qt::AlignTop);   // 右
    mainLayout->addWidget(diPaiArea,  1, 1, Qt::AlignCenter);      // 中间底牌
    mainLayout->addWidget(selfArea,   2, 1, Qt::AlignHCenter);     // 底部自己

    // 去掉主窗口空白边距
    mainLayout->setContentsMargins(20, 20, 20, 20);

*/


/*
    QHBoxLayout *Layout1 = new QHBoxLayout(ui->widget_1);
    CardLabel *c1_1 = new CardLabel("Club", "4");
    CardLabel *c2_1 = new CardLabel("Diamond", "6");
    Layout1->addWidget(c1_1);
    Layout1->addWidget(c2_1);

    QHBoxLayout *Layout2 = new QHBoxLayout(ui->widget_2);
    CardLabel *c1_2 = new CardLabel("Club", "4");
    CardLabel *c2_2 = new CardLabel("Diamond", "6");
    Layout2->addWidget(c1_2);
    Layout2->addWidget(c2_2);

    QHBoxLayout *Layout3 = new QHBoxLayout(ui->widget_3);
    CardLabel *c1_3 = new CardLabel("Club", "4");
    CardLabel *c2_3 = new CardLabel("Diamond", "6");
    Layout3->addWidget(c1_3);
    Layout3->addWidget(c2_3);

    QHBoxLayout *Layout4 = new QHBoxLayout(ui->widget_4);
    CardLabel *c1_4 = new CardLabel("Club", "4");
    CardLabel *c2_4 = new CardLabel("Diamond", "6");
    Layout4->addWidget(c1_4);
    Layout4->addWidget(c2_4);
*/
}

DealingScreen::~DealingScreen()
{
    delete ui;
}

void DealingScreen::createAllCards()
{
    allCards.clear();
    QStringList colors = {"Spade", "Heart", "Club", "Diamond"};
    QStringList values = {"3","4","5","6","7","8","9","10","J","Q","K","A","2"};

    // 生成普通牌
    int weight = 1;
    for (const QString& v : values) {
        for (const QString& c : colors) {
            allCards.push_back({c, v, weight});
        }
        weight++;
    }

    // 加入王
    allCards.push_back({"JOKER-", "B", weight++}); // 小王
    allCards.push_back({"JOKER-", "A", weight++}); // 大王
}

void DealingScreen::shuffleCards()
{
    std::shuffle(allCards.begin(), allCards.end(), *QRandomGenerator::global());
}

void DealingScreen::dealCards()
{
    // 清空
    player1Cards.clear();
    player2Cards.clear();
    player3Cards.clear();
    bottomCards.clear();

    // 轮流发 17 轮，每人17张
    for (int i=0; i<17; i++) {
        player2Cards.push_back(allCards.back()); allCards.pop_back();
        player3Cards.push_back(allCards.back()); allCards.pop_back();
        player1Cards.push_back(allCards.back()); allCards.pop_back();
    }

    // 剩下3张底牌
    bottomCards.push_back(allCards[0]);
    bottomCards.push_back(allCards[1]);
    bottomCards.push_back(allCards[2]);

    // 地主多拿3张（player1 = 地主）
    player1Cards.push_back(allCards[0]);
    player1Cards.push_back(allCards[1]);
    player1Cards.push_back(allCards[2]);
}

void DealingScreen::showCards(QGroupBox* box, const std::vector<Card>& cards)
{
    // 清空旧牌
    QList<QLabel*> labels = box->findChildren<QLabel*>();
    qDeleteAll(labels);
    if(box->layout())
    {
        delete box->layout();
    }

    QHBoxLayout* layout = new QHBoxLayout(box);
    layout->setSpacing(-45); // 重叠关键！
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(10,10,10,10);

    // 创建牌控件
    for (const Card& card : cards) {
        CardLabel* label = new CardLabel(card.color, card.value);
        layout->addWidget(label);
    }
}

void DealingScreen::on_sendCards_clicked()
{
    createAllCards();   // 生成牌
    shuffleCards();     // 洗牌
    dealCards();        // 发牌

    // 显示到三个玩家区域（你要改成自己的 groupBox 名字）
    showCards(ui->groupBox_1, player1Cards); // 地主
    showCards(ui->groupBox_2, player2Cards); // 农民
    showCards(ui->groupBox_3, player3Cards); // 农民
    showCards(ui->groupBox_4, bottomCards);   // 底牌
}

