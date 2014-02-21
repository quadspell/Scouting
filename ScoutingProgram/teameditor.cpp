#include "teameditor.h"
#include "overloads.h"

TeamEditor::TeamEditor(QString eventName)
{
    qDebug() << "Creating Team Editor";

    EventName = eventName;

    CreateTeamGroupBox();
    CreateMenu();
    LoadTeamData();
    InitTeamList();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(TeamGroupBox);
    mainLayout->addWidget(Done);

    setLayout(mainLayout);
    setWindowTitle(tr("Team Editor"));

    qDebug() << "Team Editor Created";
}




void TeamEditor::CreateMenu()
{
    qDebug() << "Team Editor: Creating Menu";

    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    QWidget::connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

    qDebug() << "Team Editor Menu Created";
}


void TeamEditor::CreateTeamGroupBox()
{
    qDebug() << "Team Editor: Creating Group Box";

    TeamGroupBox = new QGroupBox(tr("Enter Teams"));
    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;

    addTeams = new QPushButton(tr("Add Team"));
    RemoveTeam = new QPushButton(tr("Remove Team"));
    TeamInput = new QLineEdit("Add Team Number");
    TeamList = new QTextEdit;
    Done = new QPushButton(tr("Done"));
    Clear = new QPushButton(tr("Clear"));

    TeamList->setReadOnly(true);

    hLayout->addWidget(TeamInput);
    hLayout->addWidget(addTeams);
    hLayout->addWidget(RemoveTeam);
    vLayout->addWidget(TeamList);
    vLayout->addWidget(Clear);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(Done);

    QWidget::connect(TeamInput, SIGNAL(selectionChanged()), TeamInput, SLOT(clear()));
    QWidget::connect(addTeams, SIGNAL(clicked()), this, SLOT(addTeam()));
    QWidget::connect(RemoveTeam, SIGNAL(clicked()), this, SLOT(removeTeam()));
    QWidget::connect(Done, SIGNAL(clicked()), this, SLOT(done()));
    QWidget::connect(Clear, SIGNAL(clicked()), this, SLOT(clearTeams()));

    TeamGroupBox->setLayout(hLayout);

    qDebug() << "Team Editor: Group Box Created";
}



void TeamEditor::addTeam()
{
    Teams[iTeams].name = TeamInput->text();
    TeamList->append(Teams[iTeams].name);
    TeamInput->clear();
    iTeams++;
}

void TeamEditor::InitTeamList()
{
    qDebug() << "Team Editor: Initializing Team List";

    TeamList->clear();
    for(int i = 0; i < iTeams; i++)
    {
        TeamList->append(Teams[i].name);
    }

    qDebug() << "Team Editor: Team List Initialized";
}


void TeamEditor::LoadTeamData()
{
    qDebug() << "Team Editor: Loading Team Data";

    QFile *file = new QFile(EventName);

    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "TeamEditor::LoadTeamData(): Could not open read file";
        return;
    }

    QDataStream in(file);
    in.setVersion(QDataStream::Qt_5_2);

    in >> iTeams;

    for(int i = 0; i < iTeams; i++)
    {
        in >> Teams[i];
    }

    file->close();

    qDebug() << "Team Editor: Team Data Loaded";
}



void TeamEditor::removeTeam()
{
    TeamList->clear();
    iTeams--;
    Teams[iTeams].name = "";
    for(int i = 0; i<iTeams; i++)
    {
        TeamList->append(Teams[i].name);
    }
}


void TeamEditor::done()
{
    this->saveTeams();
    this->close();
}


void TeamEditor::clearTeams()
{
    for(int i = 0; i < iTeams; i++)
    {
        Teams[i].name = "";
    }

    iTeams = 0;
    TeamList->clear();
}

void TeamEditor::saveTeams()
{
    qDebug() << "Team Editor: Saving Teams";

    QFile *file = new QFile(EventName);

    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Team Editor: Could not open write file";
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

    qDebug() << "Team Editor: Teams Saved";
}

void TeamEditor::openWindow()
{
    qDebug() << "Team Editor: Opening Window";

    this->LoadTeamData();
    this->InitTeamList();
    this->show();

    qDebug() << "Team Editor: Window Opened";
}
