#pragma once
#include<opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include<Windows.h>
#include<atlimage.h>
#include<iostream>
#include"ADB.h"
#include<thread>
#include <QObject>
using namespace cv;
using std::string;
using std::cout;


class MainApp  : public QObject
{
	Q_OBJECT

public:
	MainApp(QObject *parent);
	~MainApp();

	bool findTemplPos(std::string srcPath, std::string templPath, Point& resultPt);
	bool findUnreadMsg();
	bool waitKizunaEvent();
	bool skipKizunaEvent(bool retry = false);
	void refreshMonoTalk();
	void swipeMsgList();
	void schedule();

signals:
	void newLog();
	void scheduleFinished();
};
