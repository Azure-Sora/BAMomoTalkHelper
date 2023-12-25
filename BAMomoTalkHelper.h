#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BAMomoTalkHelper.h"
#include "MainApp.h"

class BAMomoTalkHelper : public QMainWindow
{
    Q_OBJECT

public:
    BAMomoTalkHelper(QWidget *parent = nullptr);
    ~BAMomoTalkHelper();
    void loop(MainApp& app);
    Ui::BAMomoTalkHelperClass ui;
};
