// TestPrimeSieve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <assert.h>
#include <list>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>

class CPrimeEntry
{
public:
	uintptr_t m_nPrime;
	uintptr_t m_nCurrentMultipleValue;

public:
	constexpr const auto& GetCurrentMultipleValue() const
	{
		return m_nCurrentMultipleValue;
	}

	void IncrementToNextMultiple()
	{
		m_nCurrentMultipleValue += m_nPrime;
	}

public:
	constexpr CPrimeEntry(uintptr_t nPrime)
		: m_nPrime{ nPrime }
		, m_nCurrentMultipleValue{ nPrime }
	{}
	constexpr CPrimeEntry()
		: CPrimeEntry{ 0 }
	{}
};
typedef std::shared_ptr<CPrimeEntry> SPCPrimeEntry;

int main()
{
	std::multimap<uintptr_t, SPCPrimeEntry> oCurrentValueToPrimeEntryMap;
	std::list<SPCPrimeEntry> m_oOrderedPrimeEntryList;

	// "prime" the map...
	{
		auto spPrimeEntry = std::make_shared<CPrimeEntry>(2);
		oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));
		m_oOrderedPrimeEntryList.push_back(spPrimeEntry);
	}
	{
		auto spPrimeEntry = std::make_shared<CPrimeEntry>(3);
		oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));
		m_oOrderedPrimeEntryList.push_back(spPrimeEntry);
	}

	const auto& spPrimeEntry_LastPreset = m_oOrderedPrimeEntryList.back();
	uintptr_t nCurrentTestValue{ spPrimeEntry_LastPreset->m_nPrime + 2 };

	while (oCurrentValueToPrimeEntryMap.size() < 1000000)
	{
		// Note: Optimization: skip even numbers...
		if (nCurrentTestValue % 2 == 0)
		{
			nCurrentTestValue++;
			continue;
		}

		auto iterSmallestPrimeMultiple = oCurrentValueToPrimeEntryMap.begin();
		while (iterSmallestPrimeMultiple->first < nCurrentTestValue)
		{
			auto spPrimeEntry = iterSmallestPrimeMultiple->second;
			oCurrentValueToPrimeEntryMap.erase(iterSmallestPrimeMultiple);
			spPrimeEntry->IncrementToNextMultiple();
			oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));

			iterSmallestPrimeMultiple = oCurrentValueToPrimeEntryMap.begin();
		}

		if (iterSmallestPrimeMultiple->first == nCurrentTestValue)
		{
			// Current value is a multiple of a prime... keep going
			nCurrentTestValue++;
			continue;
		}

		// Current value is a new prime
		auto spPrimeEntry = std::make_shared<CPrimeEntry>(nCurrentTestValue++);
		oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));
		m_oOrderedPrimeEntryList.push_back(spPrimeEntry);
	}

	//std::map<uintptr_t, SPCPrimeEntry> oCurrentValueToPrimeEntryMap_OrderedByPrimes;
	//for (const auto& oMapPair : oCurrentValueToPrimeEntryMap)
	//{
	//	oCurrentValueToPrimeEntryMap_OrderedByPrimes[oMapPair.second->m_nPrime] = oMapPair.second;
	//}

	std::ofstream fOutputStream;
	fOutputStream.open( "primes.txt", std::ios_base::out | std::ios_base::trunc );
	assert(fOutputStream.is_open());

	for (const auto& spPrimeEntry : m_oOrderedPrimeEntryList)
	{
		fOutputStream << "Prime: " << spPrimeEntry->m_nPrime << std::endl;
	}

	std::cout << "Done." << std::endl;
	char cValue;
	std::cin >> cValue;

	return 0;
}
