#pragma once
#ifndef CAISSE_H
#define CAISSE_H

#include <vector>
#include <string>
#include <numeric>
#include <stdexcept>
#include <algorithm>

namespace Modele
{
	struct Article
	{
		std::string description;
		double prix;
		bool taxable;
	};

	class Caisse
	{
	public:
		void ajouterArticle(const Article& article)
		{
			if (article.description.empty())
			{
				throw std::invalid_argument("La description de l'article ne peut pas être vide.");
			}
			if (article.prix == 0.0)
			{
				throw std::invalid_argument("Le prix de l'article ne peut pas être zéro.");
			}

			articles_.push_back(article);
		}

		void retirerArticle(const std::string& description)
		{
			auto it = find_if(articles_.begin(), articles_.end(), [&description](const Article& article) { return article.description == description; });

			if (it != articles_.end())
			{
				articles_.erase(it);
			}
		}
		void reinitialiser()
		{
			articles_.clear();
		}
		double calculerTotalAvantTaxes() const
		{
			return std::accumulate(articles_.begin(), articles_.end(), 0.0, [](double total, const Article& article) { return total + article.prix; });
		}

		double calculerTotalTaxes() const
		{
			return std::accumulate(articles_.begin(), articles_.end(), 0.0, [](double total, const Article& article) { return total + (article.taxable ? article.prix * 0.14975 : 0.0); });

		}

		double calculerTotalAPayer() const
		{
			return calculerTotalAvantTaxes() + calculerTotalTaxes();
		}

	private:
		std::vector<Article> articles_;
	};
}

#endif