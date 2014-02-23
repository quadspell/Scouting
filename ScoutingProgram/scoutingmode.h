#ifndef SCOUTINGMODE_H
#define SCOUTINGMODE_H

#include "team.h"
#include "schedule.h"

#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QString>
#include <QComboBox>
#include <QLabel>
#include <QMenuBar>
#include <QFile>
#include <QLineEdit>
#include <QMenu>
#include <QTextEdit>
#include <QBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include <QComboBox>

class ScoutingMode : public QDialog
{
    Q_OBJECT

public:
    ScoutingMode(QString eventName);

private:
    void createScoutingGroupBox();
    void createMenu();
    void saveData(); // Saves changes to all rounds
    void loadData(); // Loads all round data
    void populateCombo();

    QAction *exitAction;
    QComboBox *select;
    QGroupBox *scoutingBox;
    QMenu *fileMenu;
    QMenuBar *menuBar;
    QPushButton *Done, *nextMatch, *enter;
    QString EventName;
    QLineEdit *redInfo1, *redInfo2, *redInfo3, *blueInfo1, *blueInfo2, *blueInfo3;
    QLabel *redDisp1, *redDisp2, *redDisp3, *blueDisp1, *blueDisp2, *blueDisp3;

    int iTeams;
    int roundNum;

    Match Matches[200];

    Team *redTeam1, *redTeam2, *redTeam3, *blueTeam1, *blueTeam2, *blueTeam3, Teams[];

public slots:
    void advanceMatch();
    void enterInfo();
};

#endif // SCOUTINGMODE_H
