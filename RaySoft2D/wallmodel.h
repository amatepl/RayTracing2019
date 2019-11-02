#ifndef WALLMODEL_H
#define WALLMODEL_H

#include <QObject>
#include <QWidget>

#include <usableobject.h>

class WallModel : public UsableObject, public QLine
{
    public:
        WallModel(int x1, int y1, int x2, int y2,
                  double relPerm = 0.0, double cond = 0.0);
        ~WallModel() {}

        map<string,int>* getIntValues();
        void setIntValues(map<string,int>* values);
        map<string,double>* getDoubleValues();
        void setDoubleValues(map<string,double>* values);

    private:
        map<string,int>* m_intProperties;
        map<string,double>* m_doubleProperties;
};

#endif // WALLMODEL_H
