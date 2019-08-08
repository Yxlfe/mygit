/********************************************************************************
** Form generated from reading UI file 'main_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WIDGET_H
#define UI_MAIN_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main_Widget
{
public:
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget_history;
    QWidget *page_2;
    QGridLayout *gridLayout;
    QListWidget *listWidget_list;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *start;
    QPushButton *end;
    QPushButton *model;
    QPushButton *sound_add;
    QPushButton *sound_reduce;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *minimize;
    QPushButton *maximize;
    QPushButton *close;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *last;
    QPushButton *play;
    QPushButton *next;
    QSpacerItem *horizontalSpacer_2;
    QSlider *process;
    QSlider *verticalSlider;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *list;
    QPushButton *history;

    void setupUi(QWidget *Main_Widget)
    {
        if (Main_Widget->objectName().isEmpty())
            Main_Widget->setObjectName(QStringLiteral("Main_Widget"));
        Main_Widget->resize(985, 769);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/image-hover/music.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Main_Widget->setWindowIcon(icon);
        Main_Widget->setAutoFillBackground(true);
        Main_Widget->setStyleSheet(QStringLiteral(""));
        gridLayout_3 = new QGridLayout(Main_Widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        stackedWidget = new QStackedWidget(Main_Widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidget_history = new QListWidget(page);
        listWidget_history->setObjectName(QStringLiteral("listWidget_history"));
        listWidget_history->setStyleSheet(QLatin1String("QListWidget{\n"
"font: 75 12pt \"Comic Sans MS\";\n"
"background-color:transparent;\n"
"\n"
"}\n"
"QListWidget::item{\n"
"color:rgb(120,120,120);\n"
"border:none;\n"
"margin-top:3px;\n"
"\n"
"}\n"
"QListWidget::item:hover{\n"
"padding-left:4px;\n"
"margin-top:3px;\n"
"color:rgb(100,100,100);\n"
"background-color:rgba(255,255,255,0.2);\n"
"\n"
"\n"
"\n"
"}\n"
"QListWidget::item:selected{\n"
"outline:none;\n"
"margin-top:3px;\n"
"padding-left:4px;\n"
"background-color:rgba(255,255,255,0.5);\n"
"color:rgb(0,0,0);\n"
"}\n"
"QListWidget::item:!active{\n"
"margin-top:3px;\n"
"border:none;\n"
"background-color:rgba(255,255,255,0);\n"
"color:rgb(120,120,120);\n"
"}\n"
"\n"
"\n"
""));

        gridLayout_2->addWidget(listWidget_history, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout = new QGridLayout(page_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget_list = new QListWidget(page_2);
        listWidget_list->setObjectName(QStringLiteral("listWidget_list"));
        listWidget_list->setStyleSheet(QLatin1String("QListWidget{\n"
"font: 75 12pt \"Comic Sans MS\";\n"
"background-color:transparent;\n"
"\n"
"}\n"
"QListWidget::item{\n"
"color:rgb(120,120,120);\n"
"border:none;\n"
"margin-top:3px;\n"
"\n"
"}\n"
"QListWidget::item:hover{\n"
"padding-left:4px;\n"
"margin-top:3px;\n"
"color:rgb(100,100,100);\n"
"background-color:rgba(255,255,255,0.2);\n"
"\n"
"\n"
"\n"
"}\n"
"QListWidget::item:selected{\n"
"outline:none;\n"
"margin-top:3px;\n"
"padding-left:4px;\n"
"background-color:rgba(255,255,255,0.5);\n"
"color:rgb(0,0,0);\n"
"}\n"
"QListWidget::item:!active{\n"
"margin-top:3px;\n"
"border:none;\n"
"background-color:rgba(255,255,255,0);\n"
"color:rgb(120,120,120);\n"
"}\n"
"\n"
"\n"
""));

        gridLayout->addWidget(listWidget_list, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);

        gridLayout_3->addWidget(stackedWidget, 3, 0, 2, 4);

        widget_2 = new QWidget(Main_Widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_5 = new QHBoxLayout(widget_2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        start = new QPushButton(widget_2);
        start->setObjectName(QStringLiteral("start"));
        start->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_5->addWidget(start);

        end = new QPushButton(widget_2);
        end->setObjectName(QStringLiteral("end"));
        end->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_5->addWidget(end);

        model = new QPushButton(widget_2);
        model->setObjectName(QStringLiteral("model"));
        model->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_5->addWidget(model);

        sound_add = new QPushButton(widget_2);
        sound_add->setObjectName(QStringLiteral("sound_add"));
        sound_add->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-image:url(:/image/image-hover/soundadd.jpg);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"background-image:url(:/image/image-hover/soundadd.jpg);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/image/image-hover/soundadd.jpg);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_5->addWidget(sound_add);

        sound_reduce = new QPushButton(widget_2);
        sound_reduce->setObjectName(QStringLiteral("sound_reduce"));
        sound_reduce->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-image:url(:/image/image-hover/soundreduce.jpg);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"background-image:url(:/image/image-hover/soundreduce.jpg);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/image/image-hover/soundreduce.jpg);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}\n"
""));

        horizontalLayout_5->addWidget(sound_reduce);


        gridLayout_3->addWidget(widget_2, 5, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(267, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 1, 0, 2, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(188, 38, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        widget = new QWidget(Main_Widget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        minimize = new QPushButton(widget);
        minimize->setObjectName(QStringLiteral("minimize"));
        minimize->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"border-radius:0px;\n"
"	\n"
"background-image: url(:/image/image/min.png);\n"
"background-color: rgba(255, 255, 255,0);\n"
"background-repeat:no-repeat;\n"
"border:none;\n"
"background-position:center center;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"\n"
"\n"
"	background-color: rgb(255, 255, 255,100);\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgba(95, 95, 95,100);\n"
"border-color:rgba(255,255,255,30);\n"
"border-style:inset;\n"
"color:rgba(0,0,0,100);\n"
"\n"
"}"));

        horizontalLayout->addWidget(minimize);

        maximize = new QPushButton(widget);
        maximize->setObjectName(QStringLiteral("maximize"));
        maximize->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"border-radius:0px;\n"
"background-image: url(:/image/image/max.png);\n"
"background-color: rgba(255, 255, 255,0);\n"
"background-repeat:no-repeat;\n"
"border:none;\n"
"background-position:center center;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"\n"
"\n"
"	background-color: rgb(255, 255, 255,100);\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgba(95, 95, 95,100);\n"
"border-color:rgba(255,255,255,30);\n"
"border-style:inset;\n"
"color:rgba(0,0,0,100);\n"
"\n"
"}\n"
""));

        horizontalLayout->addWidget(maximize);

        close = new QPushButton(widget);
        close->setObjectName(QStringLiteral("close"));
        close->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"border-radius:0px;\n"
"background-image:url(:/image/image/quit.png);\n"
"background-color: rgba(255, 255, 255,0);\n"
"background-repeat:no-repeat;\n"
"border:none;\n"
"background-position:center center;\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"\n"
"background-color: rgba(230,0,0,0.5);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color: rgba(95, 95, 95,100);\n"
"border-color:rgba(255,255,255,30);\n"
"border-style:inset;\n"
"color:rgba(0,0,0,100);\n"
"\n"
"}\n"
""));

        horizontalLayout->addWidget(close);


        horizontalLayout_4->addWidget(widget);


        gridLayout_3->addLayout(horizontalLayout_4, 0, 5, 1, 2);

        verticalSpacer = new QSpacerItem(20, 526, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 5, 2, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        widget_3 = new QWidget(Main_Widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        last = new QPushButton(widget_3);
        last->setObjectName(QStringLiteral("last"));
        last->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-image: url(:/image/image-hover/pre-hover.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"background-image:url(:/image/image-hover/pre-hover.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/image/image-hover/pre-hover.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_2->addWidget(last);

        play = new QPushButton(widget_3);
        play->setObjectName(QStringLiteral("play"));
        play->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_2->addWidget(play);

        next = new QPushButton(widget_3);
        next->setObjectName(QStringLiteral("next"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(next->sizePolicy().hasHeightForWidth());
        next->setSizePolicy(sizePolicy);
        next->setAutoFillBackground(false);
        next->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-image: url(:/image/image-hover/next-hover.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"background-image:url(:/image/image-hover/next-hover.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/image/image-hover/next-hover.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_2->addWidget(next);


        horizontalLayout_3->addWidget(widget_3);

        horizontalSpacer_2 = new QSpacerItem(118, 38, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        process = new QSlider(Main_Widget);
        process->setObjectName(QStringLiteral("process"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(process->sizePolicy().hasHeightForWidth());
        process->setSizePolicy(sizePolicy1);
        process->setStyleSheet(QString::fromUtf8("\n"
"    QSlider::add-page:Horizontal\n"
"     {     \n"
"background-color: rgba(255, 255, 255,100);\n"
"        height:4px;  \n"
"     } \n"
"     QSlider::sub-page:Horizontal   \n"
"    {  \n"
"background-color: rgb(255, 255, 255);\n"
"        height:4px;\n"
"     }\n"
"    QSlider::groove:Horizontal   \n"
"    { \n"
"        background:transparent; \n"
"        height:4px;\n"
"    }  \n"
"    QSlider::handle:Horizontal  \n"
"    { \n"
"        height:16px; \n"
"        width:16px; \n"
"	\n"
"	border-image: url(:/image/\345\234\206\345\275\242 (9).png);\n"
"  margin: -6 0px; \n"
"    }\n"
"     "));
        process->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(process);


        gridLayout_3->addLayout(horizontalLayout_3, 5, 0, 1, 4);

        verticalSlider = new QSlider(Main_Widget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setStyleSheet(QString::fromUtf8(" QSlider \n"
"    {  \n"
"        background-color: rgba(255,255,255,0.2);\n"
"        min-width:5px; \n"
"        max-width:5px;\n"
"        border:15px solid rgba(255,255,255,0.2); \n"
"    }\n"
"     QSlider::add-page:vertical\n"
"     {      \n"
"       \n"
"	    background-color: rgb(250, 250, 0);\n"
"        width:4px;\n"
"     }\n"
"     QSlider::sub-page:vertical  \n"
"    {\n"
"        background-color: rgba(255,255,255,0.5); \n"
"        width:4px;\n"
"     }\n"
"    QSlider::groove:vertical \n"
"    {\n"
"        background:transparent;\n"
"        width:6px;\n"
"    }\n"
"    QSlider::handle:vertical \n"
"    {\n"
"         height: 13px;\n"
"        width:13px;\n"
" \n"
" margin: -0 -4px; \n"
"	border-image: url(:/image/\345\234\206\345\275\242 (8).png);\n"
"     }\n"
""));
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(verticalSlider, 4, 6, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(278, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 5, 4, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        list = new QPushButton(Main_Widget);
        list->setObjectName(QStringLiteral("list"));
        list->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-image: url(:/image/image/list.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"background-image:url(:/image/image/list.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/image/image/list.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}\n"
""));

        horizontalLayout_6->addWidget(list);

        history = new QPushButton(Main_Widget);
        history->setObjectName(QStringLiteral("history"));
        history->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"background-image: url(:/image/image/play-resently.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"background-image: url(:/image/image/presently.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"background-image: url(:/image/image/play-resently.png);\n"
"background-repeat:no-repeat;\n"
"background-position:center center;\n"
"\n"
"}"));

        horizontalLayout_6->addWidget(history);


        gridLayout_3->addLayout(horizontalLayout_6, 1, 2, 2, 1);

        verticalSlider->raise();
        widget_2->raise();
        stackedWidget->raise();

        retranslateUi(Main_Widget);

        QMetaObject::connectSlotsByName(Main_Widget);
    } // setupUi

    void retranslateUi(QWidget *Main_Widget)
    {
        Main_Widget->setWindowTitle(QApplication::translate("Main_Widget", "Main_Widget", 0));
        start->setText(QApplication::translate("Main_Widget", "Start", 0));
        end->setText(QApplication::translate("Main_Widget", "End", 0));
        model->setText(QString());
        sound_add->setText(QString());
        sound_reduce->setText(QString());
        minimize->setText(QString());
        maximize->setText(QString());
        close->setText(QString());
        last->setText(QString());
        play->setText(QString());
        next->setText(QString());
#ifndef QT_NO_TOOLTIP
        process->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        list->setText(QString());
        history->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Main_Widget: public Ui_Main_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WIDGET_H
