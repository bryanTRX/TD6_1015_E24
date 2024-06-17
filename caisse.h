#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <stdexcept>
#include <algorithm>

namespace Modele
{
	// Structure représentant un article
	struct Article
	{
		std::string description;
		double prix;
		bool taxable;
	};

	class Caisse
	{
	public:
		// Methodes ---------------------------------------------------------------------------------

		// Méthode pour ajouter un article
		void ajouterArticle(const Article& article)
		{
			// Vérifie si la description de l'article est vide
			if (article.description.empty())
			{
				throw std::invalid_argument("La description de l'article ne peut pas être vide.");
			}

			// Vérifie si le prix de l'article est zéro
			if (article.prix <= 0.0)
			{
				throw std::invalid_argument("Le prix de l'article ne peut pas être inférieur ou égal à zéro.");
			}
			articles_.push_back(article);
		}

		// Méthode pour retirer un ou plusieurs articles en fonction de leur description
		void retirerArticle(const std::vector<std::string>& descriptions)
		{
			for (const auto& description : descriptions)
			{
				auto it = std::remove_if(articles_.begin(), articles_.end(), [&description](const Article& article) { return article.description == description; });

				if (it != articles_.end())
				{
					articles_.erase(it, articles_.end());
				}
			}
		}

		// Méthode pour réinitialiser la liste des articles
		void reinitialiser()
		{
			articles_.clear();
		}

		// Méthode pour calculer le total avant taxes
		double calculerTotalAvantTaxes() const
		{
			return std::accumulate(articles_.begin(), articles_.end(), 0.0, [](double total, const Article& article) { return total + article.prix; });
		}

		// Méthode pour calculer le total des taxes
		double calculerTotalTaxes() const
		{
			return std::accumulate(articles_.begin(), articles_.end(), 0.0, [](double total, const Article& article) { return total + (article.taxable ? article.prix * 0.14975 : 0.0); });

		}

		// Méthode pour calculer le total à payer
		double calculerTotalAPayer() const
		{
			return calculerTotalAvantTaxes() + calculerTotalTaxes();
		}

	private:
		std::vector<Article> articles_;
	};
}