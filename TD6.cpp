#include "affichage.h"

#include <QBrush>
#include <QString>

namespace Vue
{
    Vision::Vision(QWidget* parent) : QMainWindow(parent)
    {
        ui.setupUi(this);

        connect(ui.ajouterButton, &QPushButton::clicked, this, &Vision::ajouterArticle);
        connect(ui.retirerButton, &QPushButton::clicked, this, &Vision::retirerArticle);
        connect(ui.reinitialiserButton, &QPushButton::clicked, this, &Vision::reinitialiserCommande);

        ui.retirerButton->setEnabled(false);
    }

    Vision::~Vision() { }

    void Vision::ajouterArticle()
    {
        try {
            QString description = ui.descriptionLineEdit->text();
            double prix = ui.prixLineEdit->text().toDouble();
            bool taxable = ui.checkBox->isChecked();

            if (description.isEmpty())
            {
                throw std::invalid_argument("La description de l'article ne peut pas �tre vide.");
            }
            if (prix == 0.0)
            {
                throw std::invalid_argument("Le prix de l'article ne peut pas �tre z�ro.");
            }

            Modele::Article article = { description.toStdString(), prix, taxable };
            caisse.ajouterArticle(article);

            QString itemText = description + "\t" + QString::number(prix, 'f', 2) + "\t" + (taxable ? "Taxable" : "");
            ui.articlesList->addItem(itemText);
            mettreAJourTotaux();

            ui.descriptionLineEdit->clear();
            ui.prixLineEdit->clear();
            ui.checkBox->setChecked(false);

            ui.retirerButton->setEnabled(true);
        }
        catch (const std::invalid_argument& e)
        {
            afficherMessageErreur(e.what());
        }
    }

    void Vision::retirerArticle()
    {
        QListWidgetItem* item = ui.articlesList->currentItem();
        if (item) {
            QString description = item->text().split("\t")[0];
            caisse.retirerArticle(description.toStdString());

            delete item;
            mettreAJourTotaux();
        }

        ui.retirerButton->setEnabled(ui.articlesList->count() > 0);
    }

    void Vision::reinitialiserCommande()
    {
        caisse.reinitialiser();
        ui.articlesList->clear();
        mettreAJourTotaux();
        ui.retirerButton->setEnabled(false);
    }

    void Vision::mettreAJourTotaux()
    {
        double totalAvantTaxes = caisse.calculerTotalAvantTaxes();
        double totalTaxes = caisse.calculerTotalTaxes();
        double totalAPayer = caisse.calculerTotalAPayer();

        ui.totalAvantTaxesLabel->setText(QString::number(totalAvantTaxes, 'f', 2));
        ui.totalTaxesLabel->setText(QString::number(totalTaxes, 'f', 2));
        ui.totalAPayerLabel->setText(QString::number(totalAPayer, 'f', 2));
    }

    void Vision::afficherMessageErreur(const QString& message)
    {
        QMessageBox::critical(this, "Erreur", message);
    }
}
