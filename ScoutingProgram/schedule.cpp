#include "schedule.h"
#include "overloads.h"

#include <QDebug>
#include <QBoxLayout>
#include <QFile>


Schedule::Schedule(QString eventName)
{
    qDebug() << "Initializing Schedule";

    EventName = eventName;

    roundNum = 1;

    createScheduleGroupBox();
    createMenu();

    updateRoundInfo();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(schedule);
    mainLayout->addWidget(Done);

    setLayout(mainLayout);

    QWidget::connect(Done, SIGNAL(clicked()), this, SLOT(close()));

    qDebug() << "Schedule Initialized";
}

void Schedule::begin()
{
    redTeam1->clear();
    redTeam2->clear();
    redTeam3->clear();
    blueTeam1->clear();
    blueTeam2->clear();
    blueTeam3->clear();

    loadData();
    populateComboBoxes();
    show();
}


void Schedule::createScheduleGroupBox()
{
    qDebug() << "Schedule: Creating Group Box";

    schedule = new QGroupBox(tr("Event Schedule"));
    redAlliance = new QLabel(tr("Red Alliance"));
    blueAlliance = new QLabel(tr("Blue Alliance"));
    selectRound = new QComboBox;
    redTeam1 = new QComboBox;
    redTeam2 = new QComboBox;
    redTeam3 = new QComboBox;
    blueTeam1 = new QComboBox;
    blueTeam2 = new QComboBox;
    blueTeam3 = new QComboBox;
    Done = new QPushButton(tr("Done"));

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;

    hLayout1->addWidget(selectRound);

    hLayout2->addWidget(redAlliance);
    hLayout2->addWidget(redTeam1);
    hLayout2->addWidget(redTeam2);
    hLayout2->addWidget(redTeam3);

    hLayout3->addWidget(blueAlliance);
    hLayout3->addWidget(blueTeam1);
    hLayout3->addWidget(blueTeam2);
    hLayout3->addWidget(blueTeam3);

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);

    QWidget::connect(selectRound, SIGNAL(currentTextChanged(QString)), this, SLOT(roundChanged()));

    schedule->setLayout(vLayout);

    qDebug() << "Schedule: Group Box Created";
}

void Schedule::createMenu()
{
    qDebug() << "Schedule: Creating Menu";

    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    QWidget::connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

    qDebug() << "Schedule: Menu Created";
}

void Schedule::updateRoundInfo()
{
    for(int i = 0; i <= 250; i++)
    {
        selectRound->insertItem(i, QString::number(i + 1));
    }
}

void Schedule::populateComboBoxes()
{
    for(int i = 0; i < iTeams; i++)
        {
            redTeam1->insertItem(i, Teams[i].name);
            redTeam2->insertItem(i, Teams[i].name);
            redTeam3->insertItem(i, Teams[i].name);
            blueTeam1->insertItem(i, Teams[i].name);
            blueTeam2->insertItem(i, Teams[i].name);
            blueTeam3->insertItem(i, Teams[i].name);
        }
}

void Schedule::roundChanged()
{
    Matches[roundNum].red1 = redTeam1->currentText().toInt();
    Matches[roundNum].red2 = redTeam2->currentText().toInt();
    Matches[roundNum].red3 = redTeam3->currentText().toInt();
    Matches[roundNum].blue1 = blueTeam1->currentText().toInt();
    Matches[roundNum].blue2 = blueTeam2->currentText().toInt();
    Matches[roundNum].blue3 = blueTeam3->currentText().toInt();

    roundNum = selectRound->currentText().toInt();
    qDebug() << "round changed to" << roundNum;
}

void Schedule::loadData()
{
    qDebug() << "Schedule: Loading Data";

    QFile *file = new QFile(EventName);

    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Schedule::LoadData(): Could not open read file";
        return;
    }

    QDataStream in(file);
    in.setVersion(QDataStream::Qt_5_2);

    in >> iTeams;

    for(int i = 0; i < iTeams; i++)
    {
        qDebug() << i;
        in >> Teams[i];
        qDebug() << "Schedule::LoadData: " << i << ": " << Teams[i].name;
    }

    file->close();

    qDebug() << "Schedule: Data Loaded";
}
void Schedule::saveData()
{
    qDebug() << "Schedule: Saving";

    QFile *file = new QFile(EventName);

    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Schedule: Could not open write file";
        return;
    }

    QDataStream out(file);
    out.setVersion(QDataStream::Qt_5_2);

    out << iTeams;

    for(int i = 0; i < iTeams; i++)
    {
        out << Teams[i];
    }

    file->flush();
    file->close();

    qDebug() << "Schedule: Saved";
}
