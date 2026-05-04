#include "cardsscreen.h"
#include "ui_cardsscreen.h"
#include "cardlabel.h"
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QDebug>
#include <QLayout>

CardsScreen::CardsScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardsScreen)
{
    ui->setupUi(this);
    this->setWindowTitle("发牌界面");
    connect(ui->comboBoxPersonNum,QOverload<int>::of(&QComboBox::currentIndexChanged),ui->stackedWidget,&QStackedWidget::setCurrentIndex);

}

CardsScreen::~CardsScreen()
{
    delete ui;
}

void CardsScreen::on_btn_dealCards_clicked()
{
    try
    {
        Handledeal();
    }
    catch (const std::exception& e)
    {
        qDebug() << "发牌异常:" << e.what();
    }


}

void CardsScreen::Automaticdealing(QStringList cards)
{


    m_allCards.clear();
    QRegularExpression cardRegex("^(梅|方|红|黑|广|大王|小王)(A|2|3|4|5|6|7|8|9|10|J|Q|K)?");
    qDebug()<<"AAA:";
    // 正常单张牌最长是3个字符（如“方10”、“梅10”），超过3个字符说明发生了粘连
    for (const QString& currentCard : cards)
    {
        qDebug()<<currentCard;
        if (currentCard.length() > 3)
        {
            QString tempStr = currentCard; // 创建一个临时字符串用来“切片”

            while (!tempStr.isEmpty()) {
                // 永远从 0 开始匹配剩下的字符串
                QRegularExpressionMatch match = cardRegex.match(tempStr, 0);

                if (match.hasMatch()) {
                    QString singleCard = match.captured(0);
                    qDebug() << "成功切分出单张牌:" << singleCard;
                    m_allCards.push_back({singleCard});

                    // 【核心操作】把已经匹配到的牌从字符串开头切掉，剩下的留给下一轮
                    tempStr = tempStr.mid(match.capturedLength());
                } else {
                    // 如果开头匹配不上（比如遇到了干扰字符），直接切掉第一个字符
                    qDebug() << "遇到干扰字符，跳过:" << tempStr.at(0);
                    tempStr = tempStr.mid(1);
                }
            }
        }
        else if(isAllDigits(currentCard))
        {
            qDebug()<<"当前字符全部为数字，跳过："<<currentCard;
            continue;
        }
        else
        {
            m_allCards.push_back({currentCard});
        }

    }

    //识别到牌后显示
    showCards(ui->AllCards, m_allCards);
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
    // m_bottomCards.push_back(m_m_allCards[0]);
    // m_bottomCards.push_back(m_m_allCards[1]);
    // m_bottomCards.push_back(m_m_allCards[2]);

    // 地主多拿3张（player1 = 地主）
    // m_player1Cards.push_back(m_m_allCards[0]);
    // m_player1Cards.push_back(m_m_allCards[1]);
    // m_player1Cards.push_back(m_m_allCards[2]);
}

void CardsScreen::showCards(QGroupBox *box, const std::vector<Card> &cards)
{
    // 清空旧布局
    //delete box->layout();
    if(cards.empty())
    {
        return;
    }

    qDeleteAll(box->findChildren<QLabel*>());
    if (box->layout()) {
        delete box->layout();
    }


    //当前为识别牌展示区，分为两行展示
    if(box->objectName() == "AllCards")
    {

        // 创建主布局（垂直布局，包含两行）
        QVBoxLayout* mainLayout = new QVBoxLayout(box);
        mainLayout->setSpacing(0);  // 两行之间的间距
        mainLayout->setAlignment(Qt::AlignCenter);

        // 计算每行应该放多少张牌（最多28张）
        int cardsPerRow = 28;
        int totalCards = cards.size();
        int firstRowCount = qMin(cardsPerRow, totalCards);
        int secondRowCount = totalCards - firstRowCount;

        // 创建第一行布局
        if (firstRowCount > 0) {
            QHBoxLayout* firstRowLayout = new QHBoxLayout();
            firstRowLayout->setSpacing(0);  // 牌之间的间距
            firstRowLayout->setAlignment(Qt::AlignCenter);

            // 添加第一行的牌
            for (int i = 0; i < firstRowCount; ++i) {
                CardLabel* label = new CardLabel(cards[i].color);
                firstRowLayout->addWidget(label);
            }

            mainLayout->addLayout(firstRowLayout);
        }

        // 创建第二行布局
        if (secondRowCount > 0) {
            QHBoxLayout* secondRowLayout = new QHBoxLayout();
            secondRowLayout->setSpacing(0);
            secondRowLayout->setAlignment(Qt::AlignCenter);

            // 添加第二行的牌
            for (int i = firstRowCount; i < totalCards; ++i) {
                CardLabel* label = new CardLabel(cards[i].color);
                secondRowLayout->addWidget(label);
            }

            mainLayout->addLayout(secondRowLayout);
        }

        // 激活布局
        mainLayout->activate();
        box->updateGeometry();
        box->update();
    }
    else
    {
        QHBoxLayout* layout = new QHBoxLayout(box);
        layout->setSpacing(2); // 重叠，目前没生效
        layout->setAlignment(Qt::AlignCenter);
        //layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0,0,0,0);

        // 创建牌控件
        for (const Card& card : cards) {
            CardLabel* label = new CardLabel(card.color);
            layout->addWidget(label);
        }
        // 激活布局
        layout->activate();
        box->updateGeometry();
        box->update();
    }
}

int CardsScreen::getCardValue(const QString &cardName)
{
    if (CARD_VALUE_MAP.contains(cardName)) {
        return CARD_VALUE_MAP.value(cardName);
    }

    // 如果没找到对应的牌，可以根据业务需求返回 -1 或抛出异常
    qDebug() << "警告：未找到对应的牌面映射 ->" << cardName;
    return -1;
}

bool CardsScreen::isAllDigits(const QString &str)
{
    if (str.isEmpty()) return false;
    for (const QChar &c : str)
    {
        if (!c.isDigit())
        { // 或者使用: if (c < '0' || c > '9')
            return false;
        }
    }
    return true;
}

void CardsScreen::deleteCards(QString objectName)
{
    QWidget *currentPage = ui->stackedWidget->currentWidget();
    if (!currentPage) return;

    QGroupBox *groupBox = currentPage->findChild<QGroupBox*>(objectName);

    if (groupBox)
    {
        // 3. 获取 QGroupBox 内的所有直接子控件
        QList<QWidget*> children = groupBox->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);

        // 4. 遍历并使用 deleteLater() 安全删除
        for (QWidget *child : children)
        {
            child->deleteLater();
        }
    }
}

void CardsScreen::Handledeal()
{

    //获取参数设置的牌
    QString targetCard;
    QString targetCardSuit=ui->comboBoxSuit->currentText();
    QString targetCardValue=ui->comboBoxValue->currentText();
    int SkippNum=getCardValue(targetCardValue);
    qDebug()<<"跳牌数值:"<<SkippNum;

    targetCard=targetCardSuit+targetCardValue;
    if(targetCardValue=="小王" || targetCardValue=="大王" || targetCardValue=="广")
    {
        targetCard=targetCardValue;
    }
    qDebug()<<"参数牌:"<<targetCard;


    //清除之前的所有牌
    m_player1Cards.clear();
    m_player2Cards.clear();
    m_player3Cards.clear();
    m_player4Cards.clear();
    m_player5Cards.clear();
    m_player6Cards.clear();

    //遍历所有牌，找到目标牌的位置
    int targetIndex = -1;
    for (int i = 0; i < m_allCards.size(); ++i) {
        if (m_allCards[i].color == targetCard) {
            targetIndex = i;
            qDebug()<<"找到的参数牌:"<<m_allCards[i].color;
            break; // 找到第一张匹配的就退出
        }
    }
    if(targetIndex==-1)
    {
        qDebug()<<"没有参数牌";
        return;
    }

    qDebug()<<"参数牌:"<<targetIndex;


    int personNum=ui->comboBoxPersonNum->currentIndex()+2; //当前索引加2，为实际玩家数量
    // 如果没有找到目标牌，或者剩下的牌不够发，直接返回
    if (personNum*2 > m_allCards.size()) {
        return;
    }

    //计算实际开始发牌的下标
    int dealStartIndex = (targetIndex + SkippNum) % m_allCards.size();
    qDebug()<<"开始发牌索引:"<<dealStartIndex;

    //开始发牌存入各种变量
    int cardsDealt = 0;       // 记录已经发出了多少张牌
    switch(personNum)
    {
    case 2:
        while (cardsDealt < personNum*2)
        {
            // 【核心公式】：(发牌起点 + 已经发了几张) % 牌的总数
            // 这样 currentIdx 永远会在 0 到 m_allCards.size()-1 之间循环
            int currentIdx = (dealStartIndex + cardsDealt) % m_allCards.size();

            Card currentCard = m_allCards[currentIdx];

            // 利用取余运算轮流给玩家发牌：0, 2, 4...给玩家1； 1, 3, 5...给玩家2
            if (cardsDealt % 2 == 0) {
                m_player1Cards.push_back(currentCard); // 玩家1
            } else {
                m_player2Cards.push_back(currentCard); // 玩家2
            }

            cardsDealt++; // 已发牌数加1
        }

        showCards(ui->groupBox_21, m_player1Cards);
        showCards(ui->groupBox_22, m_player2Cards);
        break;

    case 3:
        while (cardsDealt < personNum*2)
        {
            int currentIdx = (dealStartIndex + cardsDealt) % m_allCards.size();

            Card currentCard = m_allCards[currentIdx];

            // 利用取余运算轮流给玩家发牌：0, 2, 4...给玩家1； 1, 3, 5...给玩家2
            if (cardsDealt % 3 == 0) {
                m_player1Cards.push_back(currentCard); // 玩家1
            } else if(cardsDealt % 3 == 1)
            {
                m_player2Cards.push_back(currentCard); // 玩家2
            } else if(cardsDealt % 3 ==2)
            {
                m_player3Cards.push_back(currentCard);
            }

            cardsDealt++; // 已发牌数加1
        }
        showCards(ui->groupBox_31, m_player1Cards);
        showCards(ui->groupBox_32, m_player2Cards);
        showCards(ui->groupBox_33, m_player3Cards);
        break;

    case 4:
        while (cardsDealt < personNum*2)
        {
            int currentIdx = (dealStartIndex + cardsDealt) % m_allCards.size();

            Card currentCard = m_allCards[currentIdx];

            if (cardsDealt % 4 == 0) {
                m_player1Cards.push_back(currentCard); // 玩家1
            } else if(cardsDealt % 4 == 1)
            {
                m_player2Cards.push_back(currentCard); // 玩家2
            } else if(cardsDealt % 4 ==2)
            {
                m_player3Cards.push_back(currentCard);
            } else if(cardsDealt % 4 ==3)
            {
                m_player4Cards.push_back(currentCard);
            }

            cardsDealt++; // 已发牌数加1
        }
        showCards(ui->groupBox_41, m_player1Cards);
        showCards(ui->groupBox_42, m_player2Cards);
        showCards(ui->groupBox_43, m_player3Cards);
        showCards(ui->groupBox_44, m_player4Cards);
        break;

    case 5:
        while (cardsDealt < personNum*2)
        {
            int currentIdx = (dealStartIndex + cardsDealt) % m_allCards.size();

            Card currentCard = m_allCards[currentIdx];

            if (cardsDealt % 5 == 0) {
                m_player1Cards.push_back(currentCard); // 玩家1
            } else if(cardsDealt % 5 == 1)
            {
                m_player2Cards.push_back(currentCard); // 玩家2
            } else if(cardsDealt % 5 ==2)
            {
                m_player3Cards.push_back(currentCard);
            } else if(cardsDealt % 5 ==3)
            {
                m_player4Cards.push_back(currentCard);
            }else if(cardsDealt % 5 ==4)
            {
                m_player5Cards.push_back(currentCard);
            }

            cardsDealt++; // 已发牌数加1
        }
        showCards(ui->groupBox_51, m_player1Cards);
        showCards(ui->groupBox_52, m_player2Cards);
        showCards(ui->groupBox_53, m_player3Cards);
        showCards(ui->groupBox_54, m_player4Cards);
        showCards(ui->groupBox_55, m_player5Cards);
        break;

    case 6:
        while (cardsDealt < personNum*2)
        {
            int currentIdx = (dealStartIndex + cardsDealt) % m_allCards.size();

            Card currentCard = m_allCards[currentIdx];

            if (cardsDealt % 6 == 0) {
                m_player1Cards.push_back(currentCard); // 玩家1
            } else if(cardsDealt % 6 == 1)
            {
                m_player2Cards.push_back(currentCard); // 玩家2
            } else if(cardsDealt % 6 ==2)
            {
                m_player3Cards.push_back(currentCard);
            } else if(cardsDealt % 6 ==3)
            {
                m_player4Cards.push_back(currentCard);
            }else if(cardsDealt % 6 ==4)
            {
                m_player5Cards.push_back(currentCard);
            }else if(cardsDealt % 6 ==5)
            {
                m_player6Cards.push_back(currentCard);
            }

            cardsDealt++; // 已发牌数加1
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


//     红A，黑A，黑2，黑3，黑4，黑5，黑6，黑7，黑8，黑9，黑10，黑K，黑Q，红2，红3，红4
//     红A，小王，黑2，黑3，黑4，黑5，黑6，黑7，黑8，黑9，黑10，黑K，黑Q，红2，红3，红4
//     红A，小王，大王，黑3，黑4，黑5，黑6，黑7，黑8，黑9，黑10，黑K，黑Q，红2，红3，红4

void CardsScreen::on_btn_Reset_clicked()
{
    int index=ui->stackedWidget->currentIndex(); //获取当前页索引
    switch(index)
    {
    case 0:  //2人
        qDebug()<<"重置2人游戏牌";
        deleteCards("groupBox_21");
        deleteCards("groupBox_22");
        break;
    case 1: //3人
        deleteCards("groupBox_31");
        deleteCards("groupBox_32");
        deleteCards("groupBox_33");
        break;
    case 2: //4人
        deleteCards("groupBox_41");
        deleteCards("groupBox_42");
        deleteCards("groupBox_43");
        deleteCards("groupBox_44");
        break;
    case 3: //5人
        deleteCards("groupBox_51");
        deleteCards("groupBox_52");
        deleteCards("groupBox_53");
        deleteCards("groupBox_54");
        deleteCards("groupBox_55");
        break;
    case 4: //6人
        deleteCards("groupBox_61");
        deleteCards("groupBox_62");
        deleteCards("groupBox_63");
        deleteCards("groupBox_64");
        deleteCards("groupBox_65");
        deleteCards("groupBox_66");
        break;
    }
}

