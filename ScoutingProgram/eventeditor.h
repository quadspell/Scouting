#ifndef EVENTEDITOR_H
#define EVENTEDITOR_H

#include "teameditor.h"
#include "scoutingmode.h"
#include "teamstats.h"
#include "schedule.h"

#include <QDialog>
#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QString>

class EventEditor : public QDialog
{
    Q_OBJECT
public:
    EventEditor(QString eventName);

private:
    void CreateEventsGroupBox();
    void CreateMenu();

    QAction *exitAction;
    QGroupBox *EditEvents;
    QMenu *fileMenu;
    QMenuBar *menuBar;
    QPushButton *EditTeams, *ViewTeamStats, *EnterScoutingMode, *Done, *OpenSchedule;
    QString EventName;

    TeamEditor *teamEditor;
    ScoutingMode *scoutingMode;
    TeamStats *teamStats;
    Schedule *schedule;

};

#endif // EVENTEDITOR_H
