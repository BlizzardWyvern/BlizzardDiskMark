#include "ScoreLabel.h"
#include <QQmlEngine>

ScoreLabel::ScoreLabel(QObject *parent) :
    QObject(parent),
    m_meter(0)
{
}

ScoreLabel* ScoreLabel::qmlAttachedProperties(QObject *object)
{
    return new ScoreLabel(object);
}