#include "formation.h"

Formation::Formation()
{
    Id="";
    Nom="";
    Type="";
    Horaire="";
    Duree="";
    Lieu="";
    Capacite="";
    Tarif="";

}
void Formation::setId(QString n){Id=n;}
void Formation::setNom(QString n){Nom=n;}
void Formation::setType(QString n){Type=n;}
void Formation::setHoraire(QString n){Horaire=n;}
void Formation::setDuree(QString n){Duree=n;}
void Formation::setLieu(QString n){Lieu=n;}
void Formation::setCapacite(QString n){Capacite=n;}
void Formation::setTarif(QString n){Tarif=n;}

QString Formation::get_Id(){return Id;}
QString Formation::get_Nom(){return Nom;}
QString Formation::get_Type(){return Type;}
QString Formation::get_Horaire(){return Horaire;}
QString Formation::get_Duree(){return Duree;}
QString Formation::get_Lieu(){return Lieu;}
QString Formation::get_Capacite(){return Capacite;}
QString Formation::get_Tarif(){return Id;}






