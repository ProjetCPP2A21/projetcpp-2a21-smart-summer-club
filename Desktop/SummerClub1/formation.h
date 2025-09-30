#ifndef FORMATION_H
#define FORMATION_H
#include<QString>

class Formation
{
public:
    void setId(QString n);
    void setNom(QString n);
    void setType(QString n);
    void setHoraire(QString n);
    void setDuree(QString n);
    void setLieu(QString n);
    void setCapacite(QString n);
    void setTarif(QString n);
    QString get_Id();
    QString get_Nom();
    QString get_Type();
    QString get_Horaire();
    QString get_Duree();
    QString get_Lieu();
    QString get_Capacite();
    QString get_Tarif();

    Formation();
private:
    QString Id, Nom, Type, Horaire, Duree, Lieu, Capacite, Tarif;

};

#endif // FORMATION_H
