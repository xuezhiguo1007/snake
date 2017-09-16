

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPalette>
#include <QIcon>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLabel>
#include <QFont>
#include <QSound>
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
private:
    QPushButton *upbtn;
    QPushButton *leftbtn;
    QPushButton *downbtn;
    QPushButton *rightbtn;
    QPushButton *startbtn;
    QPushButton *returnbtn;
    int direction;
    int snake[100][2];
    int snake1[100][2];
    int foodcount;
    QTimer *timer;
    int foodx,foody;
    int score;
    int level;
    QLabel *scorelabel;
    QLabel *levellabel;
    QLabel *scoreshow;
    QLabel *levelshow;
    QString str1,str2;
    QSound *sound;
    QSound *sound1;
signals:
    void UpSignal();
    void DownSignal();
    void LeftSignal();
    void RightSignal();
public slots:
    void upbtnSlot();
    void leftbtnSlot();
    void rightbtnSlot();
    void downbtnSlot();
    void startbtnSlot();
    void returnbtnSlot();
    void timeoutSlot();
};

#endif // GAMEWIDGET_H

