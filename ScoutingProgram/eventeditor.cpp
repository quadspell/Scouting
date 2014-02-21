#include "eventeditor.h"

#include <QDebug>

#include <QBoxLayout>

EventEditor::EventEditor(QString eventName)
{
    qDebug() << "EventEditor: Initializing";

    EventName = eventName;

    CreateMenu();
    CreateEventsGroupBox();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    Done = new QPushButton(tr("Done"));

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(EditEvents);
    mainLayout->addWidget(Done);

    QWidget::connect(Done, SIGNAL(clicked()), this, SLOT(close()));

    setLayout(mainLayout);
    this->setWindowTitle(eventName);

    qDebug() << "EventEditor: Created";
}

void EventEditor::CreateEventsGroupBox()
{
    qDebug() << "EventEditor: Creating Events Group Box";

    EditEvents = new QGroupBox(tr("Event Editor"));
    EditTeams = new QPushButton(tr("Edit Teams"));
    EnterScoutingMode = new QPushButton(tr("Scouting Mode"));
    ViewTeamStats = new QPushButton(tr("Team Stats"));
    OpenSchedule = new QPushButton(tr("Schedule"));

    teamEditor = new TeamEditor(EventName);
    scoutingMode = new ScoutingMode(EventName);
    teamStats = new TeamStats(EventName);
    schedule = new Schedule(EventName);

    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(EditTeams);
    layout->addWidget(EnterScoutingMode);
    layout->addWidget(ViewTeamStats);
    layout->addWidget(OpenSchedule);

    QWidget::connect(EditTeams, SIGNAL(clicked()), teamEditor, SLOT(show()));
    QWidget::connect(EnterScoutingMode, SIGNAL(clicked()), scoutingMode, SLOT(show()));
    QWidget::connect(ViewTeamStats, SIGNAL(clicked()), teamStats, SLOT(openWindow()));

    QWidget::connect(OpenSchedule,SIGNAL(clicked()), schedule, SLOT(begin()));

    EditEvents->setLayout(layout);

    qDebug() << "EventEditor: Events Group Box Created";
}

void EventEditor::CreateMenu()
{
    qDebug() << "EventEditor: Creating Menu";

    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    QWidget::connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

    qDebug() << "EventEditor: Menu created";
}
