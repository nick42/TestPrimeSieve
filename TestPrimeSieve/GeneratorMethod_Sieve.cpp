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
