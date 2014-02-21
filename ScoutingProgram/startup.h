#ifndef STARTUP_H
#define STARTUP_H

#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QString>

class Startup : public QDialog
{
    Q_OBJECT
public:
    Startup();

private:
    void CreateOptionsGroupBox();
    void CreateMenu();
    void createNewEvent();
    void populateEvents();

    QAction *exitAction;
    QComboBox *Events;
    QGroupBox *Options;
    QLineEdit *Name;
    QMenu *fileMenu;
    QMenuBar *menuBar;
    QPushButton *Open, *New, *Done;
    QString EventNames[111], SelectedEventName;

    int EventAmount, SelectedEventNum;

public slots:
    void openEvent();
    void loadEvent();
    void addEvent();
};

#endif // STARTUP_H
