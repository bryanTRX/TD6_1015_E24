#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QGraphicsScene>
#include <QListWidget>
#include <QPushButton>
#include <QObject>
#include <sstream>
#include <QlineEdit>

#include "caisse.h"
#include "ui_affichage.h"

namespace Vue
{
    class Vision : public QMainWindow
    {
        Q_OBJECT

    public:
        Vision(QWidget* parent = nullptr);
        ~Vision();

    public slots:
        void ajouterArticle();
        void retirerArticle();
        void reinitialiserCommande();

    private:
        Ui::TD6_Class ui;

        Modele::Caisse caisse;

        void mettreAJourTotaux();
        void afficherMessageErreur(const QString& message);
    };
}
