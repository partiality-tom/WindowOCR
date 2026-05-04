#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QScreen>
#include <QReadWriteLock>
#include <QWaitCondition>
#include <QtConcurrent/QtConcurrent>
#include "SelectionWindow.h"
#include "cardsscreen.h"
#include "simple_ocr.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSelectArea();  //识别区域选择
    void onAreaSelected(QRect rect);

    void on_btn_dealCards_clicked();
    void on_stop_toggled(bool checked);

signals:
    void ResultText(QString text);
    void SendText(QStringList text);

private:
    Ui::MainWindow *ui;
    QRect selectRect;
    SelectionWindow *w;

    bool m_isRunning; //是否在识别文字的标志
    QReadWriteLock m_lock;
    QWaitCondition m_condition;
    bool m_threadExit;

    SimpleOCR m_ocr;
    CardsScreen *m_CardsScreen;
    QFuture<void> m_future;
};

#endif // MAINWINDOW_H
