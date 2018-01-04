// TestPrimeSieve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <WinBase.h>

#include <assert.h>
#include <iostream>
#include <fstream>

#include "GeneratorMethod_Initial.h"
#include "GeneratorMethod_Sieve.h"

void DoGeneration_InitialMethod()
{
	CGeneratorMethod_Initial oGeneratorMethod;
	oGeneratorMethod.DoGeneration();

	std::ofstream fOutputStream;
	fOutputStream.open("primes.txt", std::ios_base::out | std::ios_base::trunc);
	assert(fOutputStream.is_open());

	for (const auto& spPrimeEntry : oGeneratorMethod.m_oProcessingAndResultData.m_oOrderedPrimeEntryList)
	{
		fOutputStream << "Prime: " << spPrimeEntry->m_nPrime << std::endl;
	}
}

void DoGeneration_SieveMethod()
{
	CGeneratorMethod_Sieve oGeneratorMethod_Sieve;
	oGeneratorMethod_Sieve.DoGeneration();

	std::ofstream fOutputStream;
	fOutputStream.open("primes.txt", std::ios_base::out | std::ios_base::trunc);
	assert(fOutputStream.is_open());

	for (const auto& oSieveEntry : oGeneratorMethod_Sieve.m_oProcessingAndResultData.m_oDataArray)
	{
		if (oSieveEntry.m_nSieveIndex < 2)
		{
			continue;
		}
		if (oSieveEntry.m_nPropertyIndicator != 0)
		{
			continue;
		}
		fOutputStream << "Prime: " << oSieveEntry.m_nSieveIndex << std::endl;
	}
}

int main()
{
	auto nTickCount_Start = ::GetTickCount64();

	//DoGeneration_InitialMethod();
	DoGeneration_SieveMethod();

	auto nTickCount_End = ::GetTickCount64();

	std::cout << "Done." << std::endl;
	char cValue;
	std::cin >> cValue;

	return 0;
}
