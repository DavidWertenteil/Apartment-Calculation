#include "stdafx.h"
#include "Controller.h"
#include <stdexcept>

// This is how we split the payment
#define RENTER_A 1720
#define RENTER_B 1680
#define RENTER_C 1600


Controller::Controller() {
	// Add all renturs to vector
	m_renters.push_back(Renter{ "David", RENTER_A , m_renters.size() + 1 });
	m_renters.push_back(Renter{ "Dor" , RENTER_B , m_renters.size() + 1 });
	m_renters.push_back(Renter{ "Mali" , RENTER_C , m_renters.size() + 1 });
}


Controller::~Controller()
{
}

void Controller::run() {

	// Display list of renters
	std::cout << "Enter number of the paying renter:" << std::endl;
	for (auto renter = m_renters.begin(); renter != m_renters.end(); ++renter)
		std::cout << renter->getIndex() << ". " << renter->getName() << std::endl;

	// Receive index of the renter paying
	unsigned index;
	do {
		index = Utilities::cinDigits<unsigned>("Enter numbers between 1  to "
			+ std::to_string(m_renters.size()) + " only");
	} while (index < 1 || index > m_renters.size());

	m_payingRenter = getIterator(index);

	// Receive expenses
	std::vector<double> expenses;
	for (auto renter = m_renters.begin(); renter != m_renters.end(); ++renter) {
		std::cout << "Enter " << renter->getName() << "'s expenses:" << std::endl;
		expenses.push_back(Utilities::receiveExpenses() / m_renters.size());
	}

	// Add expanses to renters
	for (auto renter = m_renters.begin(); renter != m_renters.end(); ++renter) {
		for (size_t i = 1; i <= expenses.size(); ++i) {
			if (i == renter->getIndex()) continue;
			renter->setAmount(expenses[i - 1]);
		}
	}

	// Receive expanses between two renters
	for (auto i = m_renters.begin(); i != m_renters.end(); ++i) {
		for (auto j = m_renters.begin(); j != m_renters.end(); ++j) {
			if (i == j) continue;
			std::cout << "Enter expanses between " << i->getName() << " and " << j->getName() << std::endl;
			std::cout << "Expanses of " << i->getName() << ": " << std::endl;
			double expenes = Utilities::receiveExpenses() / 2;
			i->setAmount(-expenes);
			j->setAmount(expenes);
		}
	}

	// Display final payments
	for (auto i = m_renters.begin(); i != m_renters.end(); ++i) {
		if (i == m_payingRenter) continue;
		std::cout << i->getName() << " to " << m_payingRenter->getName() << ": " << i->getAmount() << std::endl;
	}
	std::cout << m_payingRenter->getName() << " expenses: " << m_payingRenter->getAmount();
}
//=====================================================================================
std::vector<Renter>::iterator Controller::getIterator(unsigned index) {
	// Find iterator by its index
	unsigned counter = 1;
	for (auto it = m_renters.begin(); it != m_renters.end(); ++it, ++counter)
		if (counter == index)
			return it;
	// If there was an error
	std::exit;
	return m_renters.begin();
}
