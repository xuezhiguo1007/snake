#include "GameWidget.h"
#define ROW 13
#define COL 16
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setWindowTitle("游戏开始");
    this->setWindowIcon(QIcon(":/new/prefix1/img/1314.jpg"));
    this->resize(480,270);
    this->setMaximumSize(480,270);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/img/123456789.jpg").scaled(this->size())));
    this->setPalette(palette);
    //声音区
    sound=new QSound(":/listen/img/5611.wav");
    sound1=new QSound(":/listen/img/5611.wav");
    //按钮区
    upbtn=new QPushButton("↑",this);
    upbtn->setGeometry(QRect(380,90,40,30));

    leftbtn=new QPushButton("←",this);
    leftbtn->setGeometry(QRect(340,130,40,30));

    rightbtn=new QPushButton("→",this);
    rightbtn->setGeometry(QRect(420,130,40,30));

    downbtn=new QPushButton("↓",this);
    downbtn->setGeometry(QRect(380,170,40,30));

    startbtn=new QPushButton("开始",this);
    startbtn->setGeometry(QRect(350,220,40,30));

    returnbtn=new QPushButton("返回",this);
    returnbtn->setGeometry(QRect(410,220,40,30));

    //设置分数等级为0
    score=0;
    level=0;
    //显示分数等级标签区
    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(19);

    scorelabel=new QLabel("分数:",this);
    scorelabel->setFont(font);
    scorelabel->setGeometry(QRect(325,1,60,30));

    levellabel=new QLabel("等级:",this);
    levellabel->setFont(font);
    levellabel->setGeometry(QRect(325,30,60,30));

    str1=QString::number(score);
    str2=QString::number(level);

    scoreshow=new QLabel(this);
    scoreshow->setFont(font);
    scoreshow->setGeometry(QRect(385,1,60,30));
    scoreshow->setText(str1);

    levelshow=new QLabel(this);
    levelshow->setFont(font);
    levelshow->setGeometry(QRect(385,30,60,30));
    levelshow->setText(str2);
    //设置按钮操作
    connect(leftbtn,SIGNAL(clicked()),this,SLOT(leftbtnSlot()));
    connect(rightbtn,SIGNAL(clicked()),this,SLOT(rightbtnSlot()));
    connect(upbtn,SIGNAL(clicked()),this,SLOT(upbtnSlot()));
    connect(downbtn,SIGNAL(clicked()),this,SLOT(downbtnSlot()));
    connect(startbtn,SIGNAL(clicked()),this,SLOT(startbtnSlot()));
    connect(returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    //设置键盘操作
    connect(this,SIGNAL(UpSignal()),upbtn,SLOT(click()));
    connect(this,SIGNAL(DownSignal()),downbtn,SLOT(click()));
    connect(this,SIGNAL(LeftSignal()),leftbtn,SLOT(click()));
    connect(this,SIGNAL(RightSignal()),rightbtn,SLOT(click()));
    foodcount=0;
     //设置随机数
    int i=1;
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    snake[0][0]=qrand()%COL;
    snake[0][1]=qrand()%ROW;
    foodx=qrand()%COL;
    foody=qrand()%ROW;
    direction=qrand()%4;
    while(i)
    {
        if(snake[0][0]==foodx&&snake[0][1]==foody)
        {
            foodx=qrand()%COL;
            foody=qrand()%ROW;
            i=1;
        }
        else
            i=0;
    }
    timer=new QTimer(this);
    timer->setInterval(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeoutSlot()));

}

GameWidget::~GameWidget()
{
    delete startbtn;
    delete returnbtn;
    delete leftbtn;
    delete rightbtn;
    delete upbtn;
    delete downbtn;
    delete timer;
    delete sound;
    delete sound1;
}
void GameWidget::upbtnSlot()
{
    if(direction==DOWN)
        return;
    else
    {
    direction=UP;
    }
}

void GameWidget::downbtnSlot()
{
    if(direction==UP)
        return;
    else
    {
   direction=DOWN;
    }
}

void GameWidget::leftbtnSlot()
{
    if(direction==RIGHT)
        return;
    else
    {
    direction=LEFT;
    }
}

void GameWidget::rightbtnSlot()
{
    if(direction==LEFT)
        return;
    else
    {
    direction=RIGHT;
    }
}

void GameWidget::startbtnSlot()
{
    timer->start();
}

void GameWidget::returnbtnSlot()
{
    delete this;
}

void GameWidget::timeoutSlot()
{
    //判断是否知道食物
   if(snake[0][0]==foodx&&snake[0][1]==foody)
    {
       //吃到食物发出声音
       sound->play();
        //如果吃到食物，食物坐标更新
       int i=0;
        foodcount++;
        score++;
        str1=QString::number(score);
        scoreshow->setText(str1);
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        foodx=qrand()%COL;
        foody=qrand()%ROW;
        while(i<=foodcount)
        {
            i++;
            //判断食物是否出现在蛇身上，如果出现在蛇身上重新产生食物
            if(snake[i][0]==foodx&&snake[i][1]==foody)
            {
                foodx=qrand()%COL;
                foody=qrand()%ROW;
                i=0;
            }
        }
        switch(score)
        {
        case 10:timer->setInterval(350);level++;break;
        case 20:timer->setInterval(250);level++;break;
        case 30:timer->setInterval(150);level++;break;
        }
        str2=QString::number(level);
        levelshow->setText(str2);
    }
    memcpy(snake1,snake,sizeof(snake));
    //实现蛇的游动
    for(int i=foodcount;i>=1;i--)
    {
        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
    }

    switch(direction)
    {
    case UP:snake[0][1]--;break;
    case DOWN:snake[0][1]++;break;
    case LEFT:snake[0][0]--;break;
    case RIGHT:snake[0][0]++;break;
    }
    //判断蛇是否撞到自身
    for(int i=1;i<=foodcount;i++)
    {


        if(snake[0][0]==snake[i][0]&&snake[0][1]==snake[i][1])
        {
            sound1->play();
            memcpy(snake,snake1,sizeof(snake));
            timer->stop();
            if(QMessageBox::question(this,"提示","游戏结束,是否重新游戏",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
               {
                QTime t;
                int i;
                t= QTime::currentTime();
                qsrand(t.msec()+t.second()*1000);
                snake[0][0]=qrand()%COL;
                snake[0][1]=qrand()%ROW;
                direction=qrand()%4;
                foodx=qrand()%COL;
                foody=qrand()%ROW;
                while(i)
                {
                    if(snake[0][0]==foodx&&snake[0][1]==foody)
                    {
                        foodx=qrand()%COL;
                        foody=qrand()%ROW;
                        i=1;
                    }
                    else
                        i=0;
                }
                foodcount=0;
                score=0;
                level=0;

                str1=QString::number(score);
                str2=QString::number(level);
                scoreshow->setText(str1);
                levelshow->setText(str2);
               }
            return;
        }
    }
    //判断蛇是否撞到墙体
    if(snake[0][0]<0||snake[0][0]>=COL||snake[0][1]<0||snake[0][1]>=ROW)
    {
        sound1->play();
        memcpy(snake,snake1,sizeof(snake));
       timer->stop();
       if(QMessageBox::question(this,"提示","游戏结束,是否重新游戏",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
          {
           QTime t;
           int i;
           t= QTime::currentTime();
           qsrand(t.msec()+t.second()*1000);
           snake[0][0]=qrand()%COL;
           snake[0][1]=qrand()%ROW;
           direction=qrand()%4;
           foodx=qrand()%COL;
           foody=qrand()%ROW;
           while(i)
           {
               if(snake[0][0]==foodx&&snake[0][1]==foody)
               {
                   foodx=qrand()%COL;
                   foody=qrand()%ROW;
                   i=1;
               }
               else
                   i=0;
           }
           foodcount=0;
           score=0;
           level=0;

           str1=QString::number(score);
           str2=QString::number(level);
           scoreshow->setText(str1);
           levelshow->setText(str2);
          }
       else
        {
           delete this;
           return ;
        }

    }
    this->update();
}
void GameWidget::paintEvent(QPaintEvent *)
{
    //画方格 
    QPainter painter(this);
    for(int i=0;i<ROW*20;i+=20)
        for(int j=0;j<COL*20;j+=20)
        painter.drawRect(j,i,20,20);
    //画食物
    painter.drawImage(foodx*20,foody*20,QImage(":/new/prefix1/img/apple.png").scaled(QSize(20,20)));
    //画蛇头

    switch(direction)
    {
    case UP:painter.drawImage(snake[0][0]*20,snake[0][1]*20,QImage(":/new/prefix1/img/headup.png").scaled(QSize(20,20)));break;//蛇头向上
    case DOWN:painter.drawImage(snake[0][0]*20,snake[0][1]*20,QImage(":/new/prefix1/img/headdown.png").scaled(QSize(20,20)));break;//蛇头向下
    case LEFT:painter.drawImage(snake[0][0]*20,snake[0][1]*20,QImage(":/new/prefix1/img/headleft.png").scaled(QSize(20,20)));break;//蛇头向下
    case RIGHT:painter.drawImage(snake[0][0]*20,snake[0][1]*20,QImage(":/new/prefix1/img/headright.png").scaled(QSize(20,20)));break;//蛇头向下
    }


    //画蛇身
    for(int i=1;i<=foodcount;i++)
    {
        if(i!=foodcount)
        {
        if((snake[i][0]==snake[i-1][0]&&snake[i][1]==snake[i-1][1]-1&&
           snake[i][0]==snake[i+1][0]-1&&snake[i][1]==snake[i+1][1])||
           (snake[i][0]==snake[i-1][0]-1&&snake[i][1]==snake[i-1][1]&&
            snake[i][0]==snake[i+1][0]&&snake[i][1]==snake[i+1][1]-1))
         painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/tl_corner.png").scaled(QSize(20,20)));
        else if((snake[i][0]==snake[i-1][0]-1&&snake[i][1]==snake[i-1][1]&&
                 snake[i][0]==snake[i+1][0]&&snake[i][1]==snake[i+1][1]+1)||
                 (snake[i][0]==snake[i-1][0]&&snake[i][1]==snake[i-1][1]+1&&
                  snake[i][0]==snake[i+1][0]-1&&snake[i][1]==snake[i+1][1]))
         painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/bl_corner.png").scaled(QSize(20,20)));
        else if((snake[i][0]==snake[i-1][0]+1&&snake[i][1]==snake[i-1][1]&&
                 snake[i][0]==snake[i+1][0]&&snake[i][1]==snake[i+1][1]-1)||
                 (snake[i][0]==snake[i-1][0]&&snake[i][1]==snake[i-1][1]-1&&
                  snake[i][0]==snake[i+1][0]+1&&snake[i][1]==snake[i+1][1]))
         painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/tr_corner.png").scaled(QSize(20,20)));
        else if((snake[i][0]==snake[i-1][0]&&snake[i][1]==snake[i-1][1]+1&&
                 snake[i][0]==snake[i+1][0]+1&&snake[i][1]==snake[i+1][1])||
                 (snake[i][0]==snake[i-1][0]+1&&snake[i][1]==snake[i-1][1]&&
                  snake[i][0]==snake[i+1][0]&&snake[i][1]==snake[i+1][1]+1))
         painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/br_corner.png").scaled(QSize(20,20)));
        else if(snake[i][1]==snake[i-1][1]&&snake[i][0]!=snake[i-1][0])
       painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/h_body.png").scaled(QSize(20,20)));
        else if(snake[i][0]==snake[i-1][0]&&snake[i][1]!=snake[i-1][1])
         painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/v_body.png").scaled(QSize(20,20)));
        }
        else
        {
            //画蛇尾
            if(snake[i][0]==snake[i-1][0]+1&&snake[i][1]==snake[i-1][1])
                painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/tailleft.png").scaled(QSize(20,20)));
            else if(snake[i][0]==snake[i-1][0]-1&&snake[i][1]==snake[i-1][1])
                painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/tailright.png").scaled(QSize(20,20)));
            else if(snake[i][0]==snake[i-1][0]&&snake[i][1]==snake[i-1][1]-1)
                painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/taildown.png").scaled(QSize(20,20)));
             else if(snake[i][0]==snake[i-1][0]&&snake[i][1]==snake[i-1][1]+1)
                painter.drawImage(snake[i][0]*20,snake[i][1]*20,QImage(":/new/prefix1/img/tail.png").scaled(QSize(20,20)));
        }
    }
}
void GameWidget::keyPressEvent(QKeyEvent *k)
{
  int key = k->key();
  if(key==87)
  {
      //if(direction==DOWN)
          //return ;
     // else
      //direction=UP;
      emit UpSignal();
  }
  else if(key==83)
  {
      /*if(direction==UP)
          return;
      else
      direction=DOWN;*/
      emit DownSignal();
  }
  else if(key==65)
  {
      /*if(direction==RIGHT)
          return;
      else
      direction=LEFT;*/
      emit LeftSignal();
  }
  else if(key==68)
  {
      /*if(direction==LEFT)
          return;
      else
      direction=RIGHT;*/
      emit RightSignal();
  }
}



