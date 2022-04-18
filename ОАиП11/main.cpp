
#include "Medicine.h"
#include "QueryingGeneric.h"
#include <iostream>

void PrintMedicine(Medicine& medicine)
{
	std::cout << medicine.GetTitle() << ":\nPrice "
		<< medicine.GetPrice() << "\nCount "
		<< medicine.GetCount() << "\nExpiration time (months) "
		<< medicine.GetExpirationTime() << '\n' << std::endl;
}

int main()
{
	size_t count = 10;
	Medicine* storage = new Medicine[count]
	{
		Medicine("Perflufradil", 149.99f, 23.f, 3),
		Medicine("Gadonabacasan", 389.99f, 1.f, 1),
		Medicine("Arilotilate", 99.98f, 3.255f, 1),
		Medicine("Guanikefagatran", 999.99f, 20.f, 4),
		Medicine("Calciavinspirone", 490.f, 38.f, 18),
		Medicine("Activated carbon", 39.99f, 160.f, 80),
		Medicine("Somidralazine", 249.f, 16.f, 2),
		Medicine("Estramesine", 379.f, 18.f, 2),
		Medicine("Vingrelithiazide", 599.f, 20.f, 3),
		Medicine("Pegprosticaine", 599.f, 30.f, 1)
	};

	std::cout << "Medicine storage:\n\n";
	for (size_t i = 0; i < count; ++i)
	{
		PrintMedicine(storage[i]);
	}

	float (*priceSelector) (Medicine&) = [](Medicine& m) { return m.GetPrice(); };

	Medicine& mostExpensive = qry::GetMax<Medicine, float>(storage, count, priceSelector);
	std::cout << "-------------------------------\n\nThe most expensive medicine: " 
		<< mostExpensive.GetTitle() << " Price " << mostExpensive.GetPrice() << std::endl;

	Medicine& cheapest = qry::GetMin<Medicine, float>(storage, count, priceSelector);
	std::cout << "\nThe cheapest medicine: " << cheapest.GetTitle()
		<< " with price " << cheapest.GetPrice() << std::endl;

	std::cout << "\nTotal medicines: " << count << std::endl;

	Medicine more3MonthsExpiration;
	if (qry::TryFind<Medicine>(storage, count, [](Medicine& m) { return m.GetExpirationTime() > 3;}, more3MonthsExpiration))
	{
		std::cout << "\nMedicine with more than 3 months expiration time: " << more3MonthsExpiration.GetTitle();
	}
	else
	{
		std::cout << "\nCould not find medicine with more than 3 months expiration time";
	}
	std::cout << std::endl;

	float (*totalPriceSelector) (Medicine&) = [](Medicine& m) { return m.GetCount() * m.GetPrice(); };

	std::cout << "\nTotal price of all medicines: " 
		<< qry::Sum<Medicine, float>(storage, count, totalPriceSelector) << std::endl;

	delete[] storage;

	return 0;
}
