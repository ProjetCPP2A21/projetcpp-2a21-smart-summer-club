#ifndef APPRENANT_H
#define APPRENANT_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QRegularExpression>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollBar>
#include <QComboBox>
#include <QSpinBox>


class apprenant : public QObject
{
    Q_OBJECT

    QString nom, prenom, email;
    QDate date_naiss;
    int id_apprenant;

public slots:
    // 🆕 CHATBOT SLOTS
    void on_pushButton_CHATBOT_clicked();
    void on_pushButton_TOGGLE_CHATBOT_clicked();
    // 🆕 GROUPES SLOTS
    void on_pushButton_CREER_GROUPES_clicked();
    void on_pushButton_AFFICHER_GROUPE_clicked();
    void on_pushButton_EXPORTER_GROUPES_clicked();
    void on_pushButton_TOGGLE_GROUPES_clicked();

public:
    // Constructeurs
    apprenant(int, QString, QString, QDate, QString);  // Constructeur paramétré

    // Getters
    int getid_apprenant(){return id_apprenant;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QDate getdate_naiss(){return date_naiss;}
    QString getemail(){return email;}

    // Setters
    void setid_apprenant(int id){id_apprenant=id;}
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setdate_naiss(QDate d){date_naiss=d;}
    void setemail(QString e){email=e;}

    // Fonctionnalités CRUD
    bool ajouter();
    bool ajouter_apprenant(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email);
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool modifier(int id_apprenant, const QString &nom, const QString &prenom, const QDate &date_naiss, const QString &email);

    // Méthodes pour les métiers basiques
    QSqlQueryModel *trier_par_date();
    void exporter_vers_word();
    void statistiques_ages(QWidget *parent);

    explicit apprenant(QObject *parent = nullptr);
    ~apprenant();
    // 🆕 CHATBOT METHODS
    void creerInterfaceChatbot(QWidget *parent);
    QString traiterQuestionChatbot(const QString &question);
    QString getNombreApprenants();
    QString getServicesDisponibles();
    QString getApprenantsRecents();
    QString construireReponseServices(QSqlQuery &query);
    QString construireReponseApprenants(QSqlQuery &query, const QString &format);
    void debugTables();
    // 🆕 GROUPES METHODS
    void creerInterfaceGroupes(QWidget *parent);
    QMap<QString, QList<int>> creerGroupesEquilibres(int nombreGroupes);
    double calculerAgeMoyenGroupe(const QList<int>& idsApprenants);
    QSqlQueryModel* afficherGroupe(const QList<int>& idsApprenants);
    void exporterGroupesWord(const QMap<QString, QList<int>>& groupes);
    QSqlQueryModel* getGroupeModel(const QString& groupeName);
    QString rechercher_beneficier(int id_apprenant);

signals:
    // 🆕 SIGNAL TO REQUEST GROUP DISPLAY
    void groupeAAfficher(QSqlQueryModel *model);

private:
    static const QRegularExpression EMAIL_REGEX;
    // 🆕 CHATBOT VARIABLES
    QTextEdit *textEdit_chat;
    QLineEdit *lineEdit_question;
    QPushButton *pushButton_CHATBOT;
    QPushButton *pushButton_TOGGLE_CHATBOT;
    QFrame *frameChatbot;
    // 🆕 GROUPES VARIABLES
    QMap<QString, QList<int>> groupesActuels;
    QPushButton *pushButton_CREER_GROUPES;
    QPushButton *pushButton_AFFICHER_GROUPE;
    QPushButton *pushButton_EXPORTER_GROUPES;
    QComboBox *comboBox_GROUPES;
    QSpinBox *spinBox_NB_GROUPES;
    QLabel *labelStatutGroupe;
    QPushButton *pushButton_TOGGLE_GROUPES;
    QFrame *frameGroupes;


};

#endif // APPRENANT_H
