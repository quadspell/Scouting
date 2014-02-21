#include "overloads.h"

QDataStream &operator<<(QDataStream &out, Team &team)
{
    //Write Team Class To Stream
    out << team.name << team.totalPoints << team.wins << team.losses << team.ties << team.winPercent << team.losePercent;
    return out;
}

QDataStream &operator>>(QDataStream &in, Team &team)
{
    //Read In Team Class
    in >> team.name >> team.totalPoints >> team.wins >> team.losses >> team.ties >> team.winPercent >> team.losePercent;
    return in;
}
