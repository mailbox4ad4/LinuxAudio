
///////////////////////
// CentralWidget.cpp //
///////////////////////

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>

#include "CentralWidget.h"
#include "Application.h"

CentralWidget::CentralWidget(Application * app)
{
    qDebug() << __PRETTY_FUNCTION__;

    QVBoxLayout * layout = new QVBoxLayout;

    bool connectOk;

    QPushButton * startButton = new QPushButton("Start");
    layout->addWidget(startButton);
    connectOk = QObject::connect(startButton, SIGNAL(clicked()), app, SLOT(startAudioSlot()));
    Q_ASSERT(connectOk);

    QPushButton * stopButton = new QPushButton("Stop");
    layout->addWidget(stopButton);
    connectOk = QObject::connect(stopButton, SIGNAL(clicked()), app, SLOT(stopAudioSlot()));
    Q_ASSERT(connectOk);

    QPushButton * suspendButton = new QPushButton("Suspend");
    layout->addWidget(suspendButton);
    connectOk = QObject::connect(suspendButton, SIGNAL(clicked()), app, SLOT(suspendAudioSlot()));
    Q_ASSERT(connectOk);

    QPushButton * resumeButton = new QPushButton("Resume");
    layout->addWidget(resumeButton);
    connectOk = QObject::connect(resumeButton, SIGNAL(clicked()), app, SLOT(resumeAudioSlot()));
    Q_ASSERT(connectOk);

    QPushButton * resetButton = new QPushButton("Reset");
    layout->addWidget(resetButton);
    connectOk = QObject::connect(resetButton, SIGNAL(clicked()), app, SLOT(resetAudioSlot()));
    Q_ASSERT(connectOk);

    setLayout(layout);
}

CentralWidget::~CentralWidget()
{
    qDebug() << __PRETTY_FUNCTION__;
}
