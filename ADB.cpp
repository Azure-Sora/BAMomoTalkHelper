#include "ADB.h"
#include<string>
using namespace std;

bool ADB::executeCmd(std::string command, std::string& result)
{
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe)
    {
        return false;
    }
    
    char ch = 0;
    while (!feof(pipe))
    {
        fread(&ch, sizeof(char), 1, pipe);
        result += ch;
    }

    _pclose(pipe);
    return true;
}

bool ADB::executeADB(std::string command, std::string& result)
{
    string cmd = ".\\ADB\\adb " + command;
    return executeCmd(cmd, result);
}

bool ADB::connectTo(std::string device)
{
    string result = "";
    string connectCommand = ".\\ADB\\adb connect " + device;
    executeCmd(connectCommand, result);
    if (result.find("connected to") == string::npos)
    {
        return false;
    }
    return true;
}

bool ADB::getScreenShot()
{
    //cout << "GetScreenShot\n";

    string rslt = "";

    executeADB("shell screencap -p /sdcard/screen.jpg", rslt);
    executeADB("pull /sdcard/screen.jpg", rslt);

    return true;
}

bool ADB::tap(int x, int y)
{
    string rslt = "";
    string cmd = "shell input tap " + to_string(x) + " " + to_string(y);

    executeADB(cmd, rslt);

    return true;
}
