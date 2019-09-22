#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mAverage(0),
    mKeepPosition(0),
    mBalance(0),
    mCurValue(0)
{
    ui->setupUi(this);

    Qt::WindowFlags wf = windowFlags();
    wf = Qt::WindowStaysOnTopHint;
    setWindowFlags(wf);

    mCurPrice = ui->price; // 当前价格
    mPositionEdit = ui->position_edit; // 买入卖出数量
    mKeepPositionEdit = ui->keep_position_edit; // 持仓数
    mAverageEdit = ui->average; // 持仓均价
    mStockValueEdit = ui->stock_value; // 市场价值
    mBalanceEdit = ui->balance; // 余额
    mInitBalance = ui->init_value; // 初始资金
    mInitBalance->setText("100000");
    mBalanceEdit->setText("100000");
    mKeepPositionEdit->setText("0");

    mBalance = mBalanceEdit->text().toInt();

    mLongBtn = ui->long_btn;
    mShortBtn = ui->short_btn;
    mResetBtn = ui->reset_btn;

    connect(mLongBtn, &QPushButton::clicked, this, &MainWindow::onLong);
    connect(mShortBtn, &QPushButton::clicked, this, &MainWindow::onShort);
    connect(mResetBtn, &QPushButton::clicked, this, &MainWindow::onReset);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        save();
        qApp->exit(0);
    }
}

void MainWindow::onLong()
{
    double curPrice = mCurPrice->text().toDouble();
    // 买卖头寸数量
    int position = mPositionEdit->text().toInt();
    int value = curPrice * position * 100;
    if (mBalance - value <= 0) {
        QMessageBox msgBox;
        msgBox.setText("余额不足");
        msgBox.exec();
        return;
    }

    // 更新均价
    int sumPosition = position + mKeepPosition;
    if (mKeepPosition == 0) {
        mAverage = curPrice;
    } else {
        mAverage = (mAverage * mKeepPosition + curPrice * position) / sumPosition;
    }

    mAverageEdit->setText(QString("%1").arg(mAverage));

    // 更新持有头寸
    mKeepPosition += position;
    mKeepPositionEdit->setText(QString("%1").arg(mKeepPosition));

    // 更新余额
    mBalance -= value;
    mBalanceEdit->setText(QString("%1").arg(mBalance));

    // 更新市场价值
    mCurValue += value;
    mStockValueEdit->setText(QString("%1").arg(mCurValue));
}

void MainWindow::onShort()
{
    // 买卖头寸数量
    double curPrice = mCurPrice->text().toDouble();
    int position = mPositionEdit->text().toInt();
    int value = curPrice * position * 100;

    // 更新均价
    int sumPosition = mKeepPosition - position;
    if (sumPosition == 0) {
        mAverage = 0;
    }

    mAverageEdit->setText(QString("%1").arg(mAverage));

    // 更新持有头寸
    mKeepPosition -= position;
    mKeepPositionEdit->setText(QString("%1").arg(mKeepPosition));

    // 更新市场价值
    mCurValue = mKeepPosition * 100 * mAverage;
    mStockValueEdit->setText(QString("%1").arg(mCurValue));

    // 更新余额
    mBalance += value;
    mBalanceEdit->setText(QString("%1").arg(mBalance));
}

void MainWindow::onReset()
{
    mInitValue = mInitBalance->text().toInt();
    mBalanceEdit->setText(QString("%1").arg(mInitValue));
}

void MainWindow::save()
{

}
