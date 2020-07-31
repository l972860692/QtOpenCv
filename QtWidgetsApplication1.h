#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <vector>
class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public slots:
    void on_imagefind_clicked();
    void on_closevideobtn_clicked();
public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);
    void VideoSearch();
private:
    Ui::QtWidgetsApplication1Class ui;
};
class PersonInfo
{
public:
	PersonInfo();
	~PersonInfo();
   

private:

};

PersonInfo::PersonInfo()
{
}

PersonInfo::~PersonInfo()
{
}
