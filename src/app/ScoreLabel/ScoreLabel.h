#ifndef SCORELABEL_H
#define SCORELABEL_H

#include <QObject>
#include <QtQml>

class ScoreLabel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double meter MEMBER m_meter NOTIFY meterChanged)

public:
    explicit ScoreLabel(QObject *parent = nullptr);

    static ScoreLabel* qmlAttachedProperties(QObject *object);

signals:
    void meterChanged();

private:
    double m_meter;
};

QML_DECLARE_TYPE(ScoreLabel)
QML_DECLARE_TYPEINFO(ScoreLabel, QML_HAS_ATTACHED_PROPERTIES)

#endif // SCORELABEL_H