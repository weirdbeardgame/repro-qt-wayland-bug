/********************************************************************************
** Form generated from reading UI file 'InitialWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALWIDGET_H
#define UI_INITIALWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitialWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QToolButton *viewGameList;
    QToolButton *viewGameGrid;
    QToolButton *viewGridTitles;
    QSlider *gridScale;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *filterType;
    QComboBox *filterRegion;
    QLineEdit *searchText;
    QStackedWidget *stackedWidget;

    void setupUi(QWidget *InitialWidget)
    {
        if (InitialWidget->objectName().isEmpty())
            InitialWidget->setObjectName("InitialWidget");
        InitialWidget->resize(758, 619);
        verticalLayout = new QVBoxLayout(InitialWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(3, 3, 3, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName("horizontalLayout");
        viewGameList = new QToolButton(InitialWidget);
        viewGameList->setObjectName("viewGameList");
        viewGameList->setMinimumSize(QSize(32, 0));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("list-check");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        viewGameList->setIcon(icon);
        viewGameList->setCheckable(true);
        viewGameList->setAutoRaise(true);

        horizontalLayout->addWidget(viewGameList);

        viewGameGrid = new QToolButton(InitialWidget);
        viewGameGrid->setObjectName("viewGameGrid");
        viewGameGrid->setMinimumSize(QSize(32, 0));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("function-line");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        viewGameGrid->setIcon(icon1);
        viewGameGrid->setCheckable(true);
        viewGameGrid->setAutoRaise(true);

        horizontalLayout->addWidget(viewGameGrid);

        viewGridTitles = new QToolButton(InitialWidget);
        viewGridTitles->setObjectName("viewGridTitles");
        viewGridTitles->setMinimumSize(QSize(32, 0));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("price-tag-3-line");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8("."), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        viewGridTitles->setIcon(icon2);
        viewGridTitles->setCheckable(true);
        viewGridTitles->setAutoRaise(true);

        horizontalLayout->addWidget(viewGridTitles);

        gridScale = new QSlider(InitialWidget);
        gridScale->setObjectName("gridScale");
        gridScale->setMinimumSize(QSize(125, 0));
        gridScale->setMaximumSize(QSize(125, 16777215));
        gridScale->setMinimum(10);
        gridScale->setMaximum(200);
        gridScale->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(gridScale);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        filterType = new QComboBox(InitialWidget);
        QIcon icon3;
        iconThemeName = QString::fromUtf8("filter-line");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8("."), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        filterType->addItem(icon3, QString());
        filterType->setObjectName("filterType");

        horizontalLayout_2->addWidget(filterType);

        filterRegion = new QComboBox(InitialWidget);
        QIcon icon4;
        iconThemeName = QString::fromUtf8("global-line");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8("."), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        filterRegion->addItem(icon4, QString());
        filterRegion->setObjectName("filterRegion");

        horizontalLayout_2->addWidget(filterRegion);

        searchText = new QLineEdit(InitialWidget);
        searchText->setObjectName("searchText");
        searchText->setMinimumSize(QSize(150, 0));
        searchText->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(searchText);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        stackedWidget = new QStackedWidget(InitialWidget);
        stackedWidget->setObjectName("stackedWidget");

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(InitialWidget);

        QMetaObject::connectSlotsByName(InitialWidget);
    } // setupUi

    void retranslateUi(QWidget *InitialWidget)
    {
        viewGameList->setText(QCoreApplication::translate("InitialWidget", "Game List", nullptr));
        viewGameGrid->setText(QCoreApplication::translate("InitialWidget", "Game Grid", nullptr));
        viewGridTitles->setText(QCoreApplication::translate("InitialWidget", "Show Titles", nullptr));
        filterType->setItemText(0, QCoreApplication::translate("InitialWidget", "All Types", nullptr));

        filterRegion->setItemText(0, QCoreApplication::translate("InitialWidget", "All Regions", nullptr));

        searchText->setPlaceholderText(QCoreApplication::translate("InitialWidget", "Search...", nullptr));
        (void)InitialWidget;
    } // retranslateUi

};

namespace Ui {
    class InitialWidget: public Ui_InitialWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALWIDGET_H
