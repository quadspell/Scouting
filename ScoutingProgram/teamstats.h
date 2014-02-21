#ifndef TEAMSTATS_H
#define TEAMSTATS_H

#include "team.h"

#include <QAction>
#include <QDialog>
#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QString>
#include <QTableWidget>

class TeamStats : public QDialog
{
    Q_OBJECT
public:
    TeamStats(QString eventName);

public slots:
    void refresh();
    void openWindow();

private:
    void CreateTeamStatsGroupBox();
    void CreateMenu();
    void InitTeamTable();
    void LoadTeamData();

    QGroupBox *TeamStatsGroupBox;
    QMenuBar *menuBar;
    QPushButton *Done, *Refresh;
    QTableWidget *TeamTable;
    Team Teams[100];
    QTableWidgetItem TeamTableItem[100];
    QString EventName;

    int iTeams, temp1, temp2;

    QMenu *fileMenu;
    QAction *exitAction;

};

#endif // TEAMSTATS_H
