#include "stdafx.h"
#include "GeneratorMethod_Sieve.h"

#include <ppl.h>

HRESULT CGeneratorMethod_Sieve::DoGeneration()
{
	auto& oDataArray = m_oProcessingAndResultData.m_oDataArray;

	oDataArray.resize(16000000);
	{
		uintptr_t nSieveIndex = 0;
		for (auto& oSieveEntry : oDataArray)
		{
			oSieveEntry.m_nSieveIndex = nSieveIndex++;
		}
	}

	Concurrency::parallel_for_each(oDataArray.begin(), oDataArray.end(), [&oDataArray](GeneratorMethod_Sieve::CSieveEntry& oSieveEntry)
	{
		if (oSieveEntry.m_nSieveIndex < 2)
		{
			return;
		}
		if (oSieveEntry.IsMarkedAsComposite())
		{
			// If this number is already marked as a composite, then there's no point in filtering for it; 
			// all the multiple values will be marked by the previous number(s) for which this is a multiple.
			return;
		}
		if (oSieveEntry.m_nSieveIndex * 2 >= oDataArray.size())
		{
			// No multiple will be in range of array
			return;
		}

		auto nCurrentMultiple = 2 * oSieveEntry.m_nSieveIndex;
		while (nCurrentMultiple < oDataArray.size())
		{
			auto& oMultipleSieveEntry = oDataArray[nCurrentMultiple];
			oMultipleSieveEntry.m_nPropertyIndicator |= 0x01;
			nCurrentMultiple += oSieveEntry.m_nSieveIndex;
		}

		oSieveEntry.m_nMultipleValueWhichExceededBoundary = nCurrentMultiple;
	});

	return S_OK;
}
