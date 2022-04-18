
#pragma once

#include <string>

struct Medicine
{
private:
	std::string m_title;
	float m_price;
	float m_count;
	int m_expirationTime;

public:
	static const std::string NAME_PLACEHOLDER;

	static const Medicine& NULL_OBJECT;

	Medicine(const std::string& title, float price, float count, int expirationTime);

	Medicine();

	std::string GetTitle();

	float GetPrice();

	float GetCount();

	int GetExpirationTime();
};
