#ifndef TEAM_H
#define TEAM_H

#include <QString>

struct Team
{
    QString name;
    int totalPoints, wins, losses, ties, assists, trussThrows, trussAttempts, catches, catchAttempts, shotsMade, shotAttempts, blocks, penaltyPoints;
    double winPercent, losePercent, trussPercent, catchPercent, shotPercent;
};

#endif // TEAM_H
