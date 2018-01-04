#include "stdafx.h"
#include "GeneratorMethod_Initial.h"

#include <assert.h>

HRESULT CGeneratorMethod_Initial::DoGeneration()
{
	auto& oCurrentValueToPrimeEntryMap = m_oProcessingAndResultData.m_oCurrentValueToPrimeEntryMap;
	auto& oOrderedPrimeEntryList = m_oProcessingAndResultData.m_oOrderedPrimeEntryList;

	// "prime" the map...
	//{
	//	auto spPrimeEntry = std::make_shared<GeneratorMethod_Initial::CPrimeEntry>(2);
	//	oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));
	//	m_oOrderedPrimeEntryList.push_back(spPrimeEntry);
	//}
	{
		auto spPrimeEntry = std::make_shared<GeneratorMethod_Initial::CPrimeEntry>(3);
		oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));
		oOrderedPrimeEntryList.push_back(spPrimeEntry);
	}

	const auto& spPrimeEntry_LastPreset = oOrderedPrimeEntryList.back();
	uintptr_t nCurrentTestValue{ spPrimeEntry_LastPreset->m_nPrime };

	while (oCurrentValueToPrimeEntryMap.size() < 1000000)
	{
		assert(nCurrentTestValue % 2 == 1);
		nCurrentTestValue += 2;

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
			continue;
		}

		// Current value is a new prime
		auto spPrimeEntry = std::make_shared<GeneratorMethod_Initial::CPrimeEntry>(nCurrentTestValue);
		oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));
		oOrderedPrimeEntryList.push_back(spPrimeEntry);
	}

	{
		auto spPrimeEntry = std::make_shared<GeneratorMethod_Initial::CPrimeEntry>(2);
		oCurrentValueToPrimeEntryMap.insert(std::make_pair(spPrimeEntry->GetCurrentMultipleValue(), spPrimeEntry));
		oOrderedPrimeEntryList.push_front(spPrimeEntry);
	}

	return S_OK;
}
