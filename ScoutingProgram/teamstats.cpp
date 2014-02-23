/*****************************************************
 * Team Stats
 *
 * Handles "Team Stats" window.
 * **************************************************/

#include "teamstats.h"
#include "overloads.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QTableWidget>
#include <QVBoxLayout>
#include <math.h>

TeamStats::TeamStats(QString eventName)
{
    qDebug() << "Creating Team Stats";

    EventName = eventName;

    CreateTeamStatsGroupBox();
    CreateMenu();
    LoadTeamData();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(TeamStatsGroupBox);
    mainLayout->addWidget(Done);

    setLayout(mainLayout);

    setWindowTitle(tr("Add Teams"));

    qDebug() << "Team Stats Created";
}


void TeamStats::CreateTeamStatsGroupBox()
{
    qDebug() << "Team Stats: Creating Group Box";

    LoadTeamData();
    InitTeamTable();

    TeamStatsGroupBox = new QGroupBox(tr("Team Stats"));
    QHBoxLayout *layout = new QHBoxLayout;

    Done = new QPushButton(tr("Done"));
    Refresh = new QPushButton(tr("Refresh"));

    layout->addWidget(TeamTable);
    layout->addWidget(Refresh);
    layout->addWidget(Done);

    QWidget::connect(Refresh, SIGNAL(clicked()), this, SLOT(refresh()));
    QWidget::connect(Done, SIGNAL(clicked()), this, SLOT(close()));

    TeamStatsGroupBox->setLayout(layout);

    qDebug() << "Team Stats: Group Box Created";
}

void TeamStats::InitTeamTable()
{
    qDebug() << "Team Stats: Initializing Table";
    TeamTable = new QTableWidget(iTeams, 16);
    TeamTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Team Number"));
    TeamTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Total Score"));
    TeamTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Wins"));
    TeamTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Losses"));
    TeamTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Win Percent"));
    TeamTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Lose Percent"));
    TeamTable->setHorizontalHeaderItem(6, new QTableWidgetItem("Ties"));
    TeamTable->setHorizontalHeaderItem(7, new QTableWidgetItem("Max Score"));
    TeamTable->setHorizontalHeaderItem(8, new QTableWidgetItem("Catch Attempts"));
    TeamTable->setHorizontalHeaderItem(9, new QTableWidgetItem("Catch Percent"));
    TeamTable->setHorizontalHeaderItem(10, new QTableWidgetItem("Shot Attempts"));
    TeamTable->setHorizontalHeaderItem(11, new QTableWidgetItem("Shot Percent"));
    TeamTable->setHorizontalHeaderItem(12, new QTableWidgetItem("Blocks"));
    TeamTable->setHorizontalHeaderItem(13, new QTableWidgetItem("Penalty Points"));
    TeamTable->setHorizontalHeaderItem(14, new QTableWidgetItem("Trench Attempts"));
    TeamTable->setHorizontalHeaderItem(15, new QTableWidgetItem("Trench Percent"));
    qDebug() << "Team Stats: Table Initialized";
}

void TeamStats::CreateMenu()
{
    qDebug() << "Team Stats: Creating Menu";

    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    QWidget::connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

    qDebug() << "Team Stats: Menu Created";
}

void TeamStats::LoadTeamData()
{
    qDebug() << "Team Stats: Loading Data";

    QFile *file = new QFile(EventName);

    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "TeamStats::LoadTeamData(): Could not open read file";
        return;
    }

    QDataStream in(file);
    in.setVersion(QDataStream::Qt_5_2);

    in >> iTeams;

    for(int i = 0; i < iTeams; i++)
    {
        in >> Teams[i];
        qDebug() << "TeamStats::LoadTeamData: " << i << ": " << Teams[i].name;
    }

    file->close();

    qDebug() << "Team Stats: Data Loaded";
}

void TeamStats::refresh()
{
    LoadTeamData();
    TeamTable->clear();
    TeamTable->setRowCount(iTeams);
    TeamTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Team Number"));
    TeamTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Total Score"));
    TeamTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Wins"));
    TeamTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Losses"));
    TeamTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Win Percent"));
    TeamTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Lose Percent"));
    TeamTable->setHorizontalHeaderItem(6, new QTableWidgetItem("Ties"));
    TeamTable->setHorizontalHeaderItem(7, new QTableWidgetItem("Assists"));
    TeamTable->setHorizontalHeaderItem(8, new QTableWidgetItem("Catch Attempts"));
    TeamTable->setHorizontalHeaderItem(9, new QTableWidgetItem("Catch Percent"));
    TeamTable->setHorizontalHeaderItem(10, new QTableWidgetItem("Shot Attempts"));
    TeamTable->setHorizontalHeaderItem(11, new QTableWidgetItem("Shot Percents"));
    TeamTable->setHorizontalHeaderItem(12, new QTableWidgetItem("Blocks"));
    TeamTable->setHorizontalHeaderItem(13, new QTableWidgetItem("Penalty Points"));
    TeamTable->setHorizontalHeaderItem(14, new QTableWidgetItem("Trench Attempts"));
    TeamTable->setHorizontalHeaderItem(15, new QTableWidgetItem("Trench Percent"));

    for(int i = 0; i < iTeams; i++)
    {
        TeamTable->setItem(i, 0, new QTableWidgetItem(Teams[i].name));
        TeamTable->setItem(i, 1, new QTableWidgetItem(Teams[i].totalPoints));
        TeamTable->setItem(i, 2, new QTableWidgetItem(Teams[i].wins));
        TeamTable->setItem(i, 3, new QTableWidgetItem(Teams[i].losses));
        TeamTable->setItem(i, 4, new QTableWidgetItem(Teams[i].winPercent));
        TeamTable->setItem(i, 5, new QTableWidgetItem(Teams[i].losePercent));
        TeamTable->setItem(i, 6, new QTableWidgetItem(Teams[i].ties));
        TeamTable->setItem(i, 7, new QTableWidgetItem(Teams[i].assists));
        TeamTable->setItem(i, 8, new QTableWidgetItem(Teams[i].catchAttempts));
        TeamTable->setItem(i, 9, new QTableWidgetItem(Teams[i].catchPercent));
        TeamTable->setItem(i, 10, new QTableWidgetItem(Teams[i].shotAttempts));
        TeamTable->setItem(i, 11, new QTableWidgetItem(Teams[i].shotPercent));
        TeamTable->setItem(i, 12, new QTableWidgetItem(Teams[i].blocks));
        TeamTable->setItem(i, 13, new QTableWidgetItem(Teams[i].penaltyPoints));
        TeamTable->setItem(i, 14, new QTableWidgetItem(Teams[i].trussAttempts));
        TeamTable->setItem(i, 15, new QTableWidgetItem(Teams[i].trussPercent));
       }
}


void TeamStats::openWindow()
{
    qDebug() << "Team Stats: Opening Window";

    this->LoadTeamData();
    this->refresh();
    this->showMaximized();

    qDebug() << "Team Stats: Window Opened";
}
