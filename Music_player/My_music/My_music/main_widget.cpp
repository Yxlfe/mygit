#include "main_widget.h"
#include "ui_main_widget.h"

Main_Widget::Main_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Main_Widget),p_count(0)
{
    ui->setupUi(this);
    ui->listWidget_list->setViewMode(QListView::ListMode);
    ui->listWidget_history->setViewMode(QListView::ListMode);
    setWindowFlags(Qt::CustomizeWindowHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    init_icon();
    init_tooltip();
    TCP_client_init();
}

void Main_Widget::TCP_client_init()
{
    client = new  QTcpSocket(this);
    connect(client,&QTcpSocket::connected,this,&Main_Widget::Connected_handel);
    connect(client,&QTcpSocket::readyRead,this,&Main_Widget::read_handel);
    QString IP = QString("192.168.0.128");
    quint16 Port = 4444;
    client->connectToHost(QHostAddress(IP),Port);

}

Main_Widget::~Main_Widget()
{
    delete ui;
}

void Main_Widget::Connected_handel()
{
    qDebug() << "Client connect success!";
}

void Main_Widget::read_handel()
{
    Recvinfo Info;
    qint64 ret = client->read((char*)(&Info),sizeof(Info));
    if(ret == -1)
    {
        qDebug()<<"read _error!";
    }

    char rec_name[32] = {0};
    char rec_time[32] = {0};
    int rec_flag = Info.Get_member_flag();
    strcpy(rec_name,Info.Get_member_name());
    strcpy(rec_time,Info.Get_member_time());
    if(rec_flag == 1)
    {
       QString str(rec_name);
       QListWidgetItem* item = new QListWidgetItem;
       item->setText(str);
       ui->listWidget_list->addItem(item);
    }
    else if(rec_flag == 2)
    {
       QString str = QString("%1 %2").arg(rec_name).arg(rec_time);
       QListWidgetItem* item = new QListWidgetItem;
       item->setText(str);
       ui->listWidget_history->addItem(item);
    }

    qDebug() << "flag: "<< Info.Get_member_flag();
    qDebug() << "file_name: " << Info.Get_member_name();
    qDebug() << "file_time: " << Info.Get_member_time();
}

void Main_Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap("E:/bg12.jpg"));
}

void Main_Widget::mousePressEvent(QMouseEvent *event)//��ק �ƶ�����
{

//ListFocus();
        offset=event->globalPos()-pos();
        event->accept();
        //ui->verticalSlider->hide();
        setFocus();
        if(event->button()==Qt::LeftButton)
        setCursor(Qt::OpenHandCursor);


}
void Main_Widget::mouseMoveEvent(QMouseEvent *event)//��ק �ƶ�����
{
//ListFocus();
 move(event->globalPos()-offset);
        event->accept();
        setCursor(Qt::ClosedHandCursor);


}
void Main_Widget::mouseReleaseEvent(QMouseEvent *event)//��ק �ƶ�����
{
//ListFocus();
    offset=QPoint();
    event->accept();
    setCursor(Qt::ArrowCursor);

}

/*labelText1.push_back("You may only be a person in this world,");
labelText2.push_back("but for someone,you're the world.");
labelText1.push_back("May there be enough clouds in your life");
labelText2.push_back("        to make a beautiful sunset.");
labelText1.push_back("The best feeling the world is when you");
labelText2.push_back("        know your heart is smiling.");
labelText1.push_back("Love begins with a smile,grows with a");
labelText2.push_back("         kiss and ends with a tear.");
labelText1.push_back("Life is not lack of beauty,but lack");
labelText2.push_back("        of the eyes to find beauty.");
labelText1.push_back("The shortest distance between");
labelText2.push_back("             two people is a smile.");
labelText1.push_back("Life is not about waiting for the storm to pass.");
labelText2.push_back("It's about learning to dance in the rain.");
labelText1.push_back("In order to be irrepaceable,one");
labelText2.push_back("          must always be different.");
labelText1.push_back("The minute you think of giving up,think of");
labelText2.push_back("the reason why you held on so long.");
labelText1.push_back("Life is a shipwreck,but we must not");
labelText2.push_back("   forget to sing in the lifeboats.");
labelText1.push_back("Give everything a shot.You never know what or");
labelText2.push_back("who is going to change your life.");
*/
inline void Main_Widget::init_icon()
{
   ui->play->setIconSize(QSize(48,48));//��ͣ/����
   ui->play->setIcon(QIcon(":/image/image/pase.png"));
   ui->play->setStyleSheet(PaseStyle());
   ui->model->setIconSize(QSize(48,48));
   ui->model->setIcon(QIcon(":/image/image-hover/loop-one-hover.png"));
   ui->model->setStyleSheet(LoopOneStyle());
}

inline QString Main_Widget::PlayStyle()
{

    return "QPushButton"
   " {"
   "background-image:url(:/image/image/play.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image-hover/play-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/play.png);"

     "}";

}

inline QString Main_Widget::PaseStyle()
{


    return "QPushButton"
   " {"
   "background-image:url(:/image/image/pase.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image-hover/pase-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/pase.png);"

     "}";

}


inline QString Main_Widget::RandomStyle()
{

    return "QPushButton"
   " {"
   "background-image:url(:/image/image/play-random.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image-hover/play-random-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/play-random.png);"

     "}";

}

inline QString Main_Widget::LoopOneStyle()
{
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/loop-one.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image-hover/loop-one-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/loop-one.png);"

     "}";
}

inline QString Main_Widget::LoopStyle()
{
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/loop.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image-hover/loop-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/loop.png);"

     "}";
}


inline void Main_Widget::init_tooltip()
{
    ui->play->setToolTip(QStringLiteral("播放"));
    ui->next->setToolTip(QStringLiteral("下一首"));
    ui->last->setToolTip(QStringLiteral("上一首"));
    ui->maximize->setToolTip(QStringLiteral("最大化"));
    ui->minimize->setToolTip(QStringLiteral("最小化"));
    ui->close->setToolTip(QStringLiteral("关闭"));
    ui->model->setToolTip(QStringLiteral("模式"));
    ui->history->setToolTip(QStringLiteral("历史"));
    ui->list->setToolTip(QStringLiteral("列表"));
}


void Main_Widget::on_close_clicked()
{
     QCoreApplication::quit();
     client->disconnectFromHost();
     client->close();
}

void Main_Widget::on_maximize_clicked()
{
    showFullScreen();
    //showMaximized();
}

void Main_Widget::on_minimize_clicked()
{
    showMinimized();
}

void Main_Widget::on_play_clicked()
{
    SendInfo Info;
    if(p_count == 0)
    {      
        Info.Set_flag(4);
        ui->play->setIcon(QIcon("://../image/image/play.png"));
        ui->play->setStyleSheet(PlayStyle());
        ui->play->setToolTip(QStringLiteral("暂停"));
        ++p_count;

    }
    else if(p_count == 1)
    {
        Info.Set_flag(5);
        ui->play->setIcon(QIcon("://../image/image/pase.png"));
        ui->play->setStyleSheet(PaseStyle());
        ui->play->setToolTip(QStringLiteral("继续"));
        p_count = 0;
    }
    TCP_Send(Info);
}

void Main_Widget::TCP_Send(SendInfo S_Info)
{
   int ret = client->write((char*)(&S_Info),sizeof(S_Info));
   if(-1 == ret)
   {
       qDebug() << "write error!";
   }
}





void Main_Widget::on_model_clicked()
{
    static int m_count = 0;
    SendInfo Info;
    if(m_count == 0)
    {
        Info.Set_flag(8);
        ui->model->setIcon(QIcon("://../image/image-hover/loop-list-hover.png"));
        ui->model->setStyleSheet(LoopStyle());
        ui->model->setToolTip(QStringLiteral("列表循环"));
        ++m_count;
    }
    else if(m_count == 1)
    {
        Info.Set_flag(9);
        ui->model->setIcon(QIcon("://../image/image-hover/play-random-hover.png"));
        ui->model->setStyleSheet(RandomStyle());
        ui->model->setToolTip(QStringLiteral("随机播放"));
        ++m_count;
    }
    else if(m_count == 2)
    {
        Info.Set_flag(10);
        ui->model->setIcon(QIcon("://../image/image-hover/loop-one-hover.png"));
        ui->model->setStyleSheet(LoopOneStyle());
        ui->model->setToolTip(QStringLiteral("单曲循环"));
        m_count = 0;
    }
    TCP_Send(Info);
}


void Main_Widget::on_start_clicked()
{
    SendInfo Info;
    Info.Set_flag(2);
    TCP_Send(Info);
    p_count = 1;
    ui->play->setIcon(QIcon("://../image/image/play.png"));
    ui->play->setStyleSheet(PlayStyle());
    ui->play->setToolTip(QStringLiteral("暂停"));
}

void Main_Widget::on_end_clicked()
{
    SendInfo Info;
    Info.Set_flag(3);
    TCP_Send(Info);
    p_count = 0;
    ui->play->setIcon(QIcon("://../image/image/pase.png"));
    ui->play->setStyleSheet(PaseStyle());
    ui->play->setToolTip(QStringLiteral("继续"));
}

void Main_Widget::on_last_clicked()
{
    SendInfo Info;
    Info.Set_flag(6);
    TCP_Send(Info);
    p_count = 1;
    ui->play->setIcon(QIcon("://../image/image/play.png"));
    ui->play->setStyleSheet(PlayStyle());
    ui->play->setToolTip(QStringLiteral("暂停"));
}

void Main_Widget::on_next_clicked()
{
    SendInfo Info;
    Info.Set_flag(7);
    TCP_Send(Info);
    p_count = 1;
    ui->play->setIcon(QIcon("://../image/image/play.png"));
    ui->play->setStyleSheet(PlayStyle());
    ui->play->setToolTip(QStringLiteral("暂停"));
}

void Main_Widget::on_sound_add_clicked()
{
    SendInfo Info;
    Info.Set_flag(11);
    TCP_Send(Info);
}

void Main_Widget::on_sound_reduce_clicked()
{
    SendInfo Info;
    Info.Set_flag(12);
    TCP_Send(Info);
}



void Main_Widget::listwidget_list_delete()
{
    int num = ui->listWidget_list->count();  //获取列表项的总数目
    ui->listWidget_list->setFocus(); //将光标设置到列表框上，若注释该语句，则删除时，要手动将焦点设置到列表框，即点击列表项
    for(int i=0;i<num;i++)
    {   //逐个获取列表项的指针，并删除
        QListWidgetItem *item = ui->listWidget_list->takeItem(ui->listWidget_list->currentRow());
        delete item;
    }
}

void Main_Widget::listwidget_history_delete()
{
    int num = ui->listWidget_history->count();  //获取列表项的总数目
    ui->listWidget_history->setFocus(); //将光标设置到列表框上，若注释该语句，则删除时，要手动将焦点设置到列表框，即点击列表项
    for(int i=0;i<num;i++)
    {   //逐个获取列表项的指针，并删除
        QListWidgetItem *item = ui->listWidget_history->takeItem(ui->listWidget_history->currentRow());
        delete item;
    }
}

void Main_Widget::on_list_clicked()
{
    SendInfo Info;
    Info.Set_flag(1);
    TCP_Send(Info);
    listwidget_list_delete();
    ui->stackedWidget->setCurrentIndex(1);
}

void Main_Widget::on_history_clicked()
{
    SendInfo Info;
    Info.Set_flag(13);
    TCP_Send(Info);
    listwidget_history_delete();
    ui->stackedWidget->setCurrentIndex(0);
}

void Main_Widget::on_listWidget_list_itemDoubleClicked(QListWidgetItem *item)
{
    SendInfo Info;
    Info.Set_flag(14);
    Info.Set_name(item->text().toStdString().c_str());
    TCP_Send(Info);
}
