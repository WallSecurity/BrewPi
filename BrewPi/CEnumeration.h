#ifndef CENUMERATION_H
#define CENUMERATION_H

#include <QObject>

class EnumerationClass
{
    Q_GADGET
public:


    enum RecipeEnum {Number, Name, Date, Amount, BrewDura, StartTemp, StartDura,
        FerulaTemp, FerulaDura, ProteaseTemp, ProteaseDura, MaltoseTemp,
        MaltoseDura, SugarTemp, SugarDura, EndTemp, EndDura
    };

    Q_ENUM(RecipeEnum)

private:
    explicit EnumerationClass();
};

typedef EnumerationClass::RecipeEnum Enumeration;

#endif // CENUMERATION_H
