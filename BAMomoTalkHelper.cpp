#include "BAMomoTalkHelper.h"
#include<qpushbutton.h>

BAMomoTalkHelper::BAMomoTalkHelper(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.label_5->setVisible(false);
    ui.logs->setVisible(false);

    bool connected = false;
    MainApp app(this);
    string result = "";
    ADB::executeCmd(".\\ADB\\adb kill-server", result);
    cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

    connect(ui.btn_connect, &QPushButton::clicked, [&]() {
        string port = ui.port->text().toStdString();
        string cmd = "localhost:";
        cmd.append(port);
        connected = ADB::connectTo(cmd);

        if (connected)
        {
            ui.port->setReadOnly(true);
            ui.btn_connect->setEnabled(false);
            string status = "已连接到";
            status += cmd;
            ui.label_connectStatus->setText(QString::fromStdString(status));
            std::thread mainapp(&BAMomoTalkHelper::loop, this, std::ref(app));
            mainapp.detach();
        }
        });

}

BAMomoTalkHelper::~BAMomoTalkHelper()
{}

void BAMomoTalkHelper::loop(MainApp & app)
{
    while (1)
    {
        app.schedule();
    }
}
