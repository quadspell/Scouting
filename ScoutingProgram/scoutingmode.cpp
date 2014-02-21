#include "scoutingmode.h"
#include "overloads.h"
#include "schedule.h"

ScoutingMode::ScoutingMode(QString eventName)
{
    qDebug() << "ScoutingMode: Initianlizing";

    EventName = eventName;

    createMenu();
    createScoutingGroupBox();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(scoutingBox);
    mainLayout->addWidget(Done);

    setLayout(mainLayout);

    populateCombo();

    redTeam1 = new Team;
    redTeam2 = new Team;
    redTeam3 = new Team;
    blueTeam1 = new Team;
    blueTeam2 = new Team;
    blueTeam3 = new Team;

    QWidget::connect(Done, SIGNAL(clicked()), this, SLOT(close()));
    qDebug() << "ScoutingMode: created";
}

void ScoutingMode::createScoutingGroupBox()
{
    qDebug() << "ScoutingMode: creating GroupBox";

    scoutingBox = new QGroupBox(tr("EventName"));

    redDisp1 = new QLabel(EventName);
    redDisp2 = new QLabel(tr("redTeam2"));
    redDisp3 = new QLabel(tr("redTeam3"));
    blueDisp1 = new QLabel(tr("blueTeam1"));
    blueDisp2 = new QLabel(tr("blueTeam2"));
    blueDisp3 = new QLabel(tr("blueTeam3"));

    redInfo1 = new QLineEdit();
    redInfo2 = new QLineEdit();
    redInfo3 = new QLineEdit();
    blueInfo1 = new QLineEdit();
    blueInfo2 = new QLineEdit();
    blueInfo3 = new QLineEdit();

    enter = new QPushButton(tr("Enter"));
    nextMatch = new QPushButton(tr("Next Match"));
    Done = new QPushButton(tr("Done"));

    select = new QComboBox();

    QVBoxLayout *vlayout1 = new QVBoxLayout;
    QVBoxLayout *vlayout2 = new QVBoxLayout;
    QVBoxLayout *vlayout3 = new QVBoxLayout;
    QVBoxLayout *vlayout4 = new QVBoxLayout;
    QVBoxLayout *vlayout5 = new QVBoxLayout;

    QHBoxLayout *hlayout1 =  new QHBoxLayout;
    QHBoxLayout *hlayout2 =  new QHBoxLayout;

    vlayout1->addWidget(redDisp1);
    vlayout1->addWidget(redDisp2);
    vlayout1->addWidget(redDisp3);

    vlayout4->addWidget(redInfo1);
    vlayout4->addWidget(redInfo2);
    vlayout4->addWidget(redInfo3);

    vlayout2->addWidget(blueDisp1);
    vlayout2->addWidget(blueDisp2);
    vlayout2->addWidget(blueDisp3);

    vlayout5->addWidget(blueInfo1);
    vlayout5->addWidget(blueInfo2);
    vlayout5->addWidget(blueInfo3);

    hlayout1->addLayout(vlayout1);
    hlayout1->addLayout(vlayout4);
    hlayout1->addLayout(vlayout2);
    hlayout1->addLayout(vlayout5);

    hlayout2->addWidget(select);
    hlayout2->addWidget(enter);

    vlayout3->addLayout(hlayout1);
    vlayout3->addLayout(hlayout2);
    vlayout3->addWidget(nextMatch);

    QWidget::connect(nextMatch, SIGNAL(clicked()), this, SLOT(advanceMatch()));
    QWidget::connect(enter, SIGNAL(clicked()), this, SLOT(enterInfo()));

    scoutingBox->setLayout(vlayout3);
    qDebug() << "ScoutingMode: GroupBox created";
}

void ScoutingMode::createMenu()
{
    qDebug() << "ScoutingMode: Creating Menu";

    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    QWidget::connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

    qDebug() << "ScoutingMode: Menu Created";
}

void ScoutingMode::advanceMatch()
{
    qDebug() << "Round" << roundNum << "completed";

    //saveData();
    //updateTeamStats();
    roundNum ++;
    qDebug() << "Round" << roundNum << "started";

}

void ScoutingMode::updateTeamStats()
{
    qDebug() << "ScoutingMode: Updating Team Stats";

    qDebug() << "ScoutingMode: Team Stats Updated";
}

void ScoutingMode::loadData()
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

void ScoutingMode::saveData()
{
    qDebug() << "Scouting Mode: Saving";

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

void ScoutingMode::populateCombo()
{
    select->addItem("Points");
    select->addItem("Assists");
    select->addItem("Trench throws");
    select->addItem("Trench Throw Attemts");
    select->addItem("Catches");
    select->addItem("Catch Attemts");
    select->addItem("Shot Attempts");
    select->addItem("Shots Made");
    select->addItem("Blocks");
    select->addItem("Penatly Points");

}

void ScoutingMode::enterInfo()
{
    switch(select->currentIndex() + 1)
    {
        case 1:
            redTeam1->totalPoints += redInfo1->text().toInt();
            redTeam2->totalPoints += redInfo2->text().toInt();
            redTeam3->totalPoints += redInfo3->text().toInt();
            blueTeam1->totalPoints += blueInfo1->text().toInt();
            blueTeam2->totalPoints += blueInfo2->text().toInt();
            blueTeam3->totalPoints += blueInfo3->text().toInt();

            int redTeam, blueTeam;

            redTeam = redInfo1->text().toInt() + redInfo2->text().toInt() + redInfo3->text().toInt();
            blueTeam = blueInfo1->text().toInt() + blueInfo2->text().toInt() + blueInfo3->text().toInt();

            if(redTeam > blueTeam)
            {
                redTeam1->wins += 1;
                redTeam2->wins += 1;
                redTeam3->wins += 1;
                qDebug() << "Red Team Wins!";
            }
            else if(redTeam < blueTeam)
            {
                blueTeam1->wins += 1;
                blueTeam2->wins += 1;
                blueTeam3->wins += 1;
                qDebug() << "Blue Team Wins!";
            }
            else if(redTeam == blueTeam)
            {
                redTeam1->ties += 1;
                redTeam2->ties += 1;
                redTeam3->ties += 1;
                blueTeam1->ties += 1;
                blueTeam2->ties += 1;
                blueTeam3->ties += 1;
                qDebug() << "They Tied";
            }
            qDebug() << "total points added";          
            break;
        case 2:
            redTeam1->assists += redInfo1->text().toInt();
            redTeam2->assists += redInfo1->text().toInt();
            redTeam3->assists += redInfo1->text().toInt();
            blueTeam1->assists += redInfo1->text().toInt();
            blueTeam2->assists += redInfo1->text().toInt();
            blueTeam3->assists += redInfo1->text().toInt();
            qDebug() << "assists added";
            break;
        case 3:
            redTeam1->trussThrows += redInfo1->text().toInt();
            redTeam2->trussThrows += redInfo1->text().toInt();
            redTeam3->trussThrows += redInfo1->text().toInt();
            blueTeam1->trussThrows += redInfo1->text().toInt();
            blueTeam2->trussThrows += redInfo1->text().toInt();
            blueTeam3->trussThrows += redInfo1->text().toInt();
            qDebug() << "assists added";
            break;
        case 4:
            redTeam1->trussAttempts += redInfo1->text().toInt();
            redTeam2->trussAttempts += redInfo1->text().toInt();
            redTeam3->trussAttempts += redInfo1->text().toInt();
            blueTeam1->trussAttempts += redInfo1->text().toInt();
            blueTeam2->trussAttempts += redInfo1->text().toInt();
            blueTeam3->trussAttempts += redInfo1->text().toInt();
            qDebug() << "assists added";
            break;
        case 5:
            redTeam1->catches += redInfo1->text().toInt();
            redTeam2->catches += redInfo1->text().toInt();
            redTeam3->catches += redInfo1->text().toInt();
            blueTeam1->catches += redInfo1->text().toInt();
            blueTeam2->catches += redInfo1->text().toInt();
            blueTeam3->catches += redInfo1->text().toInt();
            qDebug() << "catches added";
            break;
        case 6:
            redTeam1->catchAttempts += redInfo1->text().toInt();
            redTeam2->catchAttempts += redInfo1->text().toInt();
            redTeam3->catchAttempts += redInfo1->text().toInt();
            blueTeam1->catchAttempts += redInfo1->text().toInt();
            blueTeam2->catchAttempts += redInfo1->text().toInt();
            blueTeam3->catchAttempts += redInfo1->text().toInt();
            qDebug() << "catch attempts added";
            break;
        case 7:
            redTeam1->shotAttempts += redInfo1->text().toInt();
            redTeam2->shotAttempts += redInfo1->text().toInt();
            redTeam3->shotAttempts += redInfo1->text().toInt();
            blueTeam1->shotAttempts += redInfo1->text().toInt();
            blueTeam2->shotAttempts += redInfo1->text().toInt();
            blueTeam3->shotAttempts += redInfo1->text().toInt();
            qDebug() << "shot attempts added";
            break;
        case 8:
            redTeam1->shotsMade += redInfo1->text().toInt();
            redTeam2->shotsMade += redInfo1->text().toInt();
            redTeam3->shotsMade += redInfo1->text().toInt();
            blueTeam1->shotsMade += redInfo1->text().toInt();
            blueTeam2->shotsMade += redInfo1->text().toInt();
            blueTeam3->shotsMade += redInfo1->text().toInt();
            qDebug() << "shots made added";
            break;
        case 9:
            redTeam1->blocks += redInfo1->text().toInt();
            redTeam2->blocks += redInfo1->text().toInt();
            redTeam3->blocks += redInfo1->text().toInt();
            blueTeam1->blocks += redInfo1->text().toInt();
            blueTeam2->blocks += redInfo1->text().toInt();
            blueTeam3->blocks += redInfo1->text().toInt();
            qDebug() << "blocks added";
            break;
        case 10:
            redTeam1->penaltyPoints += redInfo1->text().toInt();
            redTeam2->penaltyPoints += redInfo1->text().toInt();
            redTeam3->penaltyPoints += redInfo1->text().toInt();
            blueTeam1->penaltyPoints += redInfo1->text().toInt();
            blueTeam2->penaltyPoints += redInfo1->text().toInt();
            blueTeam3->penaltyPoints += redInfo1->text().toInt();
            qDebug() << "penalty points added";
            break;
    }
}
