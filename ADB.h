#pragma once
#include<iostream>
class ADB
{
public:
	static bool executeCmd(std::string command, std::string& result);
	static bool executeADB(std::string command, std::string& result);
	static bool connectTo(std::string device);
	static bool getScreenShot();
	static bool tap(int x, int y);
	

};

