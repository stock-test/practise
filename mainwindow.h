#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

private slots:
    void onLong();
    void onShort();
    void onReset();

private:
    void save();

    Ui::MainWindow *ui;

    QLineEdit* mCurPriceEdit;
    QLineEdit* mPositionEdit;
    QLineEdit* mKeepPositionEdit;
    QLineEdit* mAverageEdit;
    QLineEdit* mStockValueEdit;
    QLineEdit* mBalanceEdit;
    QLineEdit* mInitBalance;
    QLineEdit* mCalculateEdit;

    QPushButton* mResetBtn;
    QPushButton* mLongBtn;
    QPushButton* mShortBtn;

    int mInitValue;
    double mAverage;
    int mKeepPosition;
    int mBalance;
    double mCurValue;
};

#endif // MAINWINDOW_H
