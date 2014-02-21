#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "team.h"

#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QString>

class Schedule : public QDialog
{
    Q_OBJECT
public:
    Schedule(QString eventName);


private:
    void createScheduleGroupBox();
    void createMenu();
    void updateRoundInfo(); // Loads round info
    void saveData(); // Saves changes to all rounds
    void loadData(); // Loads all round data
    void populateComboBoxes();

    QAction *exitAction;
    QComboBox *selectRound, *redTeam1, *redTeam2, *redTeam3, *blueTeam1, *blueTeam2, *blueTeam3;
    QGroupBox *schedule;
    QLabel *redAlliance, *blueAlliance;
    QMenu *fileMenu;
    QMenuBar *menuBar;
    QPushButton *Done;
    QString EventName;

    Team *RedAlliance[200][3];
    Team *BlueAlliance[200][3];
    Team Teams[100];

    int eventSize;
    int iTeams;
    int roundNum;

signals:

public slots:
    void roundChanged(); // Updates round info when selectRound is changed
    void begin();
};

#endif // SCHEDULE_H
