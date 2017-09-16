#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include "GameWidget.h"
#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QFont>
class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = 0);
    ~mainWidget();
    //void resizeEvent(QResizeEvent *);
private:
    QPushButton *startbtn;
    QPushButton *exitbtn;
    GameWidget *g;
    QLabel *label;
signals:
public slots:
    void exitSlot();
    void startSlot();
};

#endif // MAINWIDGET_H

