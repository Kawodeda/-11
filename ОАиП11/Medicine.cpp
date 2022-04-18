
#include "Medicine.h"

const std::string Medicine::NAME_PLACEHOLDER = "strange pills";

const Medicine& Medicine::NULL_OBJECT = Medicine();

Medicine::Medicine(const std::string& title, float price, float count, int expirationTime)
{
	m_title = title;
	m_price = price;
	m_count = count;
	m_expirationTime = expirationTime;
}

Medicine::Medicine() : Medicine(NAME_PLACEHOLDER, 0.f, 0.f, 0) {}

std::string Medicine::GetTitle()
{
	return m_title;
}

float Medicine::GetPrice()
{
	return m_price;
}

float Medicine::GetCount()
{
	return m_count;
}

int Medicine::GetExpirationTime()
{
	return m_expirationTime;
}
