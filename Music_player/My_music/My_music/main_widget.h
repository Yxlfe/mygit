#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QListWidgetItem>
#include <QTcpSocket>
#include <QHostAddress>
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include<QPixmap>
#include<QPalette>
#include<QPainter>

#include <QDebug>
#include "sendinfo.h"
#include "recvinfo.h"

namespace Ui {
class Main_Widget;
}

class Main_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Main_Widget(QWidget *parent = 0);
    ~Main_Widget();
    inline QString PlayStyle();
    inline QString PaseStyle();
    inline QString LoopStyle();
    inline QString LoopOneStyle();
    inline QString RandomStyle();
    inline void init_tooltip();
    inline void init_icon();
    void mouseMoveEvent(QMouseEvent *event);//拖拽 移动窗口
    void mouseReleaseEvent(QMouseEvent *event);//拖拽 移动窗口
    void mousePressEvent(QMouseEvent *event);
    void TCP_client_init();
    void Connected_handel();
    void TCP_Send(SendInfo);
    void read_handel();
    void listwidget_list_delete();
    void listwidget_history_delete();

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void on_close_clicked();

    void on_maximize_clicked();

    void on_minimize_clicked();


    void on_play_clicked();


    void on_start_clicked();

    void on_model_clicked();

    void on_end_clicked();

    void on_last_clicked();

    void on_next_clicked();

    void on_sound_add_clicked();

    void on_sound_reduce_clicked();

    void on_list_clicked();

    void on_history_clicked();

    void on_listWidget_list_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Main_Widget *ui;
    QPoint offset;//点
    QTcpSocket* client;
    int p_count;
};

#endif // MAIN_WIDGET_H
