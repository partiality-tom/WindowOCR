#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QPixmap>

#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_isRunning(false)
    ,m_threadExit(false)
    ,w(nullptr)
    ,m_CardsScreen(nullptr)
    , m_ocr(SimpleOCRConfig{ "./config.txt" })
{
    ui->setupUi(this);

    SetConsoleOutputCP(65001);

    setWindowTitle("投屏实时文字识别");

    // 初始化OCR


    // 按钮：开始选区
    connect(ui->selectBtn, &QPushButton::clicked, this, &MainWindow::startSelectArea);



    connect(this,&MainWindow::ResultText,this,[this](QString text){
        ui->textEdit->clear();
        ui->textEdit->setText(text);
    },Qt::QueuedConnection);


    SimpleOCRConfig config;
    config.det_model_dir = "./config.txt";  //
    qDebug()<<"正在初始化 OCR 引擎...";

    //std::cout << "初始化完成！" << std::endl;
    qDebug()<<"初始化完成！";

    m_future=QtConcurrent::run([this](){
        qDebug() << "✅ 截图OCR线程启动";
        while(!m_threadExit)
        {
            {
                QReadLocker locker(&m_lock);
                while (!m_isRunning && !m_threadExit) {

                    m_condition.wait(&m_lock);
                }

                if (m_threadExit)
                {
                    break;
                }
            }


            QPixmap cropPix = QApplication::primaryScreen()->grabWindow(0,
                                                                        selectRect.x(),selectRect.y(),selectRect.width(),selectRect.height());
            QImage qImage = cropPix.toImage();
            cv::Mat mat;
            if (qImage.format() == QImage::Format_RGB32 ||
                qImage.format() == QImage::Format_ARGB32 ||
                qImage.format() == QImage::Format_ARGB32_Premultiplied) {
                mat = cv::Mat(qImage.height(), qImage.width(), CV_8UC4, (uchar*)qImage.bits(), qImage.bytesPerLine());
                cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
            }
            else {
                // 如果是其他格式（如 RGB888），先转成通用格式再处理
                QImage rgbImage = qImage.convertToFormat(QImage::Format_RGB32);
                mat = cv::Mat(rgbImage.height(), rgbImage.width(), CV_8UC4, (uchar*)rgbImage.bits(), rgbImage.bytesPerLine());
                cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
            }

            QElapsedTimer timer;
            timer.start(); // 1. 开始计时

            OCRResult results = m_ocr.processMat(mat);
            qint64 elapsedMs = timer.elapsed();      // 获取毫秒数 (整数)
            double elapsedS = timer.elapsed() / 1000.0; // 获取秒数 (浮点)

            std::vector<std::vector<std::string>> res=results.res;

            // 3. 输出结果 (使用 .noquote() 去除引号)
            qDebug().noquote() << QString("识别耗时: %1 毫秒 (%2 秒)").arg(elapsedMs).arg(elapsedS);

            QStringList resultList;

            for (const auto& line : res) {
                QString lineStr;

                // 遍历当前的 vector<string>，把里面的每个 string 拼接到一起
                for (const auto& str : line) {
                    lineStr += QString::fromStdString(str);
                }

                // 存入列表
                resultList << lineStr;
            }

            // 2. 写入 UI
            // 使用 invokeMethod 确保在 UI 线程更新（因为你是在子线程运行 OCR）
            QMetaObject::invokeMethod(ui->textEdit, "setText", Qt::QueuedConnection, Q_ARG(QString, resultList.join("\n")));
        }




    });

}

MainWindow::~MainWindow()
{
    {
        QWriteLocker locker(&m_lock);
        m_isRunning = false;
        m_threadExit = true;  // 退出线程
        m_condition.wakeOne();
    }
    if(m_future.isRunning())
    {
        m_future.waitForFinished();
    }

    delete ui;
}

// 打开透明全屏选区窗口
void MainWindow::startSelectArea()
{
    //初始化选择识别区域
    if(w==nullptr)
    {
        w = new SelectionWindow;
        connect(w, &SelectionWindow::selected, this, &MainWindow::onAreaSelected);
    }
    w->show();
}

// 用户选完区域
void MainWindow::onAreaSelected(QRect rect)
{
    selectRect = rect;
    ui->label->setText("已选区:" + QString::number(rect.width())
                       + "x" + QString::number(rect.height()));

    w->hide(); //半透明选择窗口隐藏

    QWriteLocker locker(&m_lock);
    m_isRunning=true;
    m_condition.wakeOne();


}



void MainWindow::on_stop_clicked()
{
    QWriteLocker lock(&m_lock);
    m_isRunning=false;
    lock.unlock();
}


void MainWindow::on_btn_dealCards_clicked()
{
    if(m_CardsScreen==nullptr)
    {
        m_CardsScreen=new CardsScreen();
        //识别框里的文本变化了，就发送最新文本到发m_CardsScreen
        connect(ui->textEdit,&QTextEdit::textChanged,this,[this](){
            QString new_string=ui->textEdit->toPlainText();
            qDebug()<<"识别区最新文本:"<<new_string;
            QStringList list = new_string.split(" ", Qt::SkipEmptyParts);
            //emit SendText(list);
        });
        connect(this,&MainWindow::SendText,m_CardsScreen,&CardsScreen::Automaticdealing);
    }
    m_CardsScreen->show();
}



