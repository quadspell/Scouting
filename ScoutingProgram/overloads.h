#ifndef OVERLOADS_H
#define OVERLOADS_H

#include "team.h"

#include <QtCore>

QDataStream &operator<<(QDataStream &out, Team &team);
QDataStream &operator>>(QDataStream &in, Team &team);

#endif // OVERLOADS_H
