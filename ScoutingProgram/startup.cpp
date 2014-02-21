#include "startup.h"
#include "eventeditor.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QLayout>

Startup::Startup()
{
    qDebug() << "Startup: Initializing";

    EventAmount = 0;

    CreateOptionsGroupBox();
    CreateMenu();

    QVBoxLayout *mainLayout = new QVBoxLayout;

    Done = new QPushButton(tr("Done"));

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(Options);
    mainLayout->addWidget(Done);

    QWidget::connect(Done, SIGNAL(clicked()), this, SLOT(close()));

    setLayout(mainLayout);
    setWindowTitle(tr("Scouter"));

    qDebug() << "Startup: Initialization Complete";
}

void Startup::CreateOptionsGroupBox()
{
    qDebug() << "Startup: Creating Options Group Box";

    New = new QPushButton(tr("New Event"));
    Open = new QPushButton(tr("Open Existing Event"));
    Name = new QLineEdit(tr("Name Event"));
    Events = new QComboBox();

    Options = new QGroupBox(tr("Options"));

    populateEvents();

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    QVBoxLayout *vLayout2 = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    vLayout1->addWidget(Name);
    vLayout1->addWidget(Events);
    vLayout2->addWidget(New);
    vLayout2->addWidget(Open);
    hLayout->addLayout(vLayout1);
    hLayout->addLayout(vLayout2);

    QWidget::connect(New, SIGNAL(clicked()), this, SLOT(addEvent()));
    QWidget::connect(Open, SIGNAL(clicked()), this, SLOT(openEvent()));

    Options->setLayout(hLayout);

    qDebug() << "Startup: Options Group Box Created";
}

void Startup::CreateMenu()
{
    qDebug() << "Startup: Creating Menu";

    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    QWidget::connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

    qDebug() << "Startup: Menu created";
}

void Startup::addEvent()
{
    qDebug() << "Startup: Adding Event";

    createNewEvent();

    EventAmount++;
    qDebug() << EventAmount;
    EventNames[EventAmount] = Name->text();

    QFile *file = new QFile("eventList");
    QDataStream out(file);

    out.setVersion(QDataStream::Qt_5_2);

    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Startup::addEvent(): Could not open write file";
        return;
    }

    out << EventAmount;

    for(int i = 0; i < EventAmount; i++)
    {
        out << EventNames[i];
    }

    qDebug() << "Adding Event: " << EventNames[EventAmount];


    file->close();

    qDebug() << "Startup: Event " << EventNames[EventAmount] << " added";

    SelectedEventName = EventNames[EventAmount];
    loadEvent();
}

void Startup::createNewEvent()
{
    qDebug() << "Startup: Creating New Event";

    EventNames[EventAmount] = Name->text();

    QFile *file = new QFile(EventNames[EventAmount]);
    QDataStream out(file);

    out.setVersion(QDataStream::Qt_5_2);

    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Startup::createNewEvent(): Could not open write file";
        return;
    }

    out << 0;

    file->flush();
    file->close();

    qDebug() << "Startup: Event " << EventNames[EventAmount] << " created";
}

void Startup::populateEvents()
{
    qDebug() << "Startup: Populating Events";

    Events->clear();

    QFile *file = new QFile("eventList");
    QDataStream in(file);

    in.setVersion(QDataStream::Qt_5_2);

    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Startup::populateEvents: Could not open read file";
        return;
    }

    in >> EventAmount;

    qDebug() << "There are " << EventAmount << " events saved";

    for(int i = 0; i < EventAmount; i++)
    {
        in >> EventNames[i];
        qDebug() << i << ": " << EventNames[i];
        Events->addItem(EventNames[i]);
    }

    file->close();


    qDebug() << "Startup: Events Populated";
}

void Startup::openEvent()
{

    SelectedEventName = EventNames[Events->currentIndex()];
    qDebug() << "Startup: Loaded " << Events->currentIndex();
    loadEvent();

    qDebug() << "Event Loaded";
}

void Startup::loadEvent()
{
    qDebug() << "Startup: Loading Event";

    EventEditor *newEvent = new EventEditor(SelectedEventName);
    newEvent->show();

    qDebug() << SelectedEventName << " Loaded";

    this->close();
}
