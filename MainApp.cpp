#include "MainApp.h"

MainApp::MainApp(QObject *parent)
	: QObject(parent)
{}

MainApp::~MainApp()
{}

bool MainApp::findTemplPos(std::string srcPath, std::string templPath, Point& resultPt)
{
	Mat src = imread(srcPath);
	Mat templ = imread(templPath);

	if (!src.empty() && !templ.empty())
	{
		Mat result(src.rows - templ.rows + 1, src.cols - templ.cols + 1, CV_32FC1);

		matchTemplate(src, templ, result, TM_CCOEFF_NORMED);

		double dMaxVal; //分数最大值
		Point ptMaxLoc; //最大值坐标
		minMaxLoc(result, 0, &dMaxVal, 0, &ptMaxLoc); //寻找结果矩阵中的最大值

		if (dMaxVal > 0.9)
		{
			resultPt = ptMaxLoc;
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool MainApp::findUnreadMsg()
{
	ADB::getScreenShot();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	//emit newLog("findUnreadMsg");

	string src = "screen.jpg";
	string unread1 = ".\\src\\unread1.jpg";
	string unread2 = ".\\src\\unread2.jpg";
	Point pt;

	if (findTemplPos(src, unread1, pt))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ADB::tap(pt.x, pt.y);
		return true;
	}
	else if (findTemplPos(src, unread2, pt))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ADB::tap(pt.x, pt.y);
		return true;
	}
	return false;
}

bool MainApp::waitKizunaEvent()
{
	Point pt;
	bool clickEvent = false;
	int retryTimes = 10;
	//emit newLog("waitKizunaEvent");
	while (retryTimes)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		ADB::getScreenShot();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (clickEvent && findTemplPos("screen.jpg", ".\\src\\startKizunaEvent.jpg", pt))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			ADB::tap(pt.x + 150, pt.y + 100);
			//emit newLog("startKizunaEvent");
			break;
		}
		if (findTemplPos("screen.jpg", ".\\src\\reply.jpg", pt))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			retryTimes = 10;
			ADB::tap(pt.x + 150, pt.y + 100);
			//emit newLog("reply");
		}
		if (findTemplPos("screen.jpg", ".\\src\\kizunaEvent.jpg", pt))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			retryTimes = 10;
			ADB::tap(pt.x + 150, pt.y + 100);
			//emit newLog("kizunaEvent");
			clickEvent = true;
		}
		--retryTimes;
	}
	if (retryTimes <= 0) return false;
	return true;
}

bool MainApp::skipKizunaEvent(bool retry)
{
	Point pt;
	bool clickMenu = false;
	bool clickSkip = false;
	bool clickOK = false;
	int retryTimes = 10;
	//emit newLog("skipKizunaEvent");
	while (retryTimes)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		ADB::getScreenShot();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (findTemplPos("screen.jpg", ".\\src\\stone.jpg", pt))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			ADB::tap(1000, 800);
			//emit newLog("stone");
			clickOK = true;
			break;
		}
		if (!clickOK && findTemplPos("screen.jpg", ".\\src\\OKButton.jpg", pt))
		{
			retryTimes = 10;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			ADB::tap(pt.x + 150, pt.y + 100);
			//emit newLog("OKButton");
			clickSkip = true;
			continue;
		}
		if (!clickSkip && findTemplPos("screen.jpg", ".\\src\\skip.jpg", pt))
		{
			retryTimes = 10;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			ADB::tap(pt.x + 30, pt.y + 30);
			//emit newLog("skip");
			clickMenu = true;
			continue;
		}
		if (!clickMenu && findTemplPos("screen.jpg", ".\\src\\menuButton.jpg", pt))
		{
			retryTimes = 10;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			ADB::tap(pt.x + 30, pt.y + 30);
			//emit newLog("menuButton");

		}
		--retryTimes;
		if (retryTimes <= 0)
		{
			if (!retry)
			{
				return skipKizunaEvent(true);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

void MainApp::refreshMonoTalk()
{
	//emit newLog("refreshMonoTalk");
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	ADB::tap(100, 100);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	ADB::tap(260, 220);
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));;
	ADB::tap(260, 415);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void MainApp::swipeMsgList()
{
	//emit newLog("swipeMsgList");
	string rslt = "";
	ADB::executeADB("shell input swipe 700 850 700 400", rslt);
}

void MainApp::schedule()
{
	if (findUnreadMsg())
	{
		if (!waitKizunaEvent())
		{
			refreshMonoTalk();
			return;
		}
		if (!skipKizunaEvent()) exit(0);
		refreshMonoTalk();
	}
	else
	{
		swipeMsgList();
	}
}