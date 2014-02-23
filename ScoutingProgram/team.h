#ifndef TEAM_H
#define TEAM_H

#include <QString>

struct Team
{
    QString name;
    int totalPoints, wins, losses, ties, assists, trussThrows, trussAttempts, catches, catchAttempts, shotsMade, shotAttempts, blocks, penaltyPoints;
    double winPercent, losePercent, trussPercent, catchPercent, shotPercent;
};

struct Match
{
   QString red1, red2, red3, blue1, blue2, blue3;
};

#endif // TEAM_H
