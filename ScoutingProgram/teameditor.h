#ifndef TEAMEDITOR_H
#define TEAMEDITOR_H

#include "team.h"

#include <QComboBox>
#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>

class TeamEditor : public QDialog
{
    Q_OBJECT
public:
    TeamEditor(QString eventName);

private:
    void CreateTeamGroupBox();
    void CreateMenu();
    void LoadTeamData();
    void InitTeamList();
    void LoadTeamLists();
    void SaveTeamLists();

    QString teamListNames[111], EventName;
    QMenuBar *menuBar;
    QPushButton *addTeams, *RemoveTeam, *Done, *Clear;
    QLineEdit *TeamInput;
    QTextEdit *TeamList;
    Team Teams[100];
    QGroupBox *TeamGroupBox;
    int iTeams;

    QMenu *fileMenu;
    QAction *exitAction;

public slots:
    void addTeam();
    void removeTeam();
    void done();
    void clearTeams();
    void saveTeams();
    void openWindow();

};

#endif // TEAMEDITOR_H
