#pragma once

#include <QString>
#include <QObject>
#include <QlineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QGraphicsScene>

#include "caisse.h"
#include "ui_affichage.h"

namespace Vue
{
    // Déclaration de la classe Vision qui hérite de QMainWindow
    class Vision : public QMainWindow
    {
        Q_OBJECT

    public:
        // Constructeurs ----------------------------------------------------------------------------

        Vision(QWidget* parent = nullptr);

        // Destructeurs -----------------------------------------------------------------------------

        ~Vision();

    public slots:
        // Slots pour gérer les interactions avec les boutons
        void ajouterArticle();
        void retirerArticle();
        void reinitialiserCommande();

    private:
        // Interface utilisateur générée par Qt Designer
        Ui::TD6_Class ui;

        // Modèle représentant la caisse enregistreuse
        Modele::Caisse caisse;

        // Méthodes utilitaires pour mettre à jour les totaux et afficher des messages d'erreur
        void mettreAJourTotaux();
        void afficherMessageErreur(const QString& message);
    };
}