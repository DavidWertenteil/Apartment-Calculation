#pragma once
#include <vector>
#include <string>
#include <iostream>

/*****************************************************************
				Renter Class
		
		Fields:
			m_name - Renters name.
			m_amount - The amount the Renter will need to pay.
			m_index - Index of current renter (id perhaps).

******************************************************************/
class Renter {
public:
	// c-tor
	Renter(const std::string& name, int amount = 0, size_t index = 0)
		:m_name(name), m_amount(amount), m_index(index) {}

	// get
	const std::string& getName()const { return m_name; }
	size_t getIndex()const { return m_index; }

	// get, set- amount
	void setAmount(double add) { m_amount += add; }
	double getAmount()const { return m_amount; }

private:
	std::string m_name;
	size_t m_index;
	double m_amount;
};
/*****************************************************************
				Controller Class
		
		Fields:
			m_payingRenter - The renter whoes paying this current mounth.
			m_renters - Vector with all renters.

******************************************************************/
class Controller
{
public:
	Controller();
	~Controller();

	void run();

	std::vector<Renter>::iterator getIterator(unsigned);
private:
	std::vector<Renter> m_renters;
	std::vector<Renter>::iterator m_payingRenter;

};
/*****************************************************************
			Utilities Class

******************************************************************/

class Utilities {
public:

	template<typename T>
	static T cinDigits(const std::string& msg) {
		T digit;
		while (!(std::cin >> digit))
		{
			std::cout << msg << std::endl;
			std::cin.clear();  // reset the failed state
			std::cin.ignore(); // delete argument from buffer
		}
		return digit;
	}
	//--------------------------------------------------------
	static double receiveExpenses() {
		std::string msg{ "Enter positive numbers only!" };
		double sum = 0;
		double expens = 1;
		do {
			expens = Utilities::cinDigits<double>(msg);
			if (expens < 0) {
				std::cout << msg << std::endl;
				continue;
			}
			sum += expens;
		} while (expens != 0);

		return sum;
	}

};
