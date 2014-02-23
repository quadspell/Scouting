#include "overloads.h"

QDataStream &operator<<(QDataStream &out, Team &team)
{
    //Write Team Class To Stream
    out << team.name << team.totalPoints << team.wins << team.losses << team.ties << team.winPercent << team.losePercent << team.assists << team.trussThrows << team.trussAttempts << team.catches << team.catchAttempts << team.shotsMade << team.shotAttempts << team.blocks << team.penaltyPoints << team.trussPercent << team.catchPercent << team.shotPercent;
    return out;
}
QDataStream &operator>>(QDataStream &in, Team &team)
{
    //Read In Team Class
    in >> team.name >> team.totalPoints >> team.wins >> team.losses >> team.ties >> team.winPercent >> team.losePercent >> team.assists >> team.trussThrows >> team.trussAttempts >> team.catches >> team.catchAttempts >> team.shotsMade >> team.shotAttempts >> team.blocks >> team.penaltyPoints >> team.trussPercent >> team.catchPercent >> team.shotPercent;;
    return in;
}
