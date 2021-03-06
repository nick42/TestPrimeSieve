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
	CGeneratorMethod_Initial oGeneratorMethod_Initial;
	oGeneratorMethod_Initial.DoGeneration();

	std::ofstream fOutputStream;
	fOutputStream.open("primes.txt", std::ios_base::out | std::ios_base::trunc);
	assert(fOutputStream.is_open());

	const auto& oResultData = oGeneratorMethod_Initial.GetResultData();
	for (const auto& nPrime : oResultData)
	{
		fOutputStream << nPrime << std::endl;
	}
}

void DoGeneration_SieveMethod()
{
	CGeneratorMethod_Sieve oGeneratorMethod_Sieve;
	oGeneratorMethod_Sieve.DoGeneration();

	std::ofstream fOutputStream;
	fOutputStream.open("primes.txt", std::ios_base::out | std::ios_base::trunc);
	assert(fOutputStream.is_open());

	const auto& oResultData = oGeneratorMethod_Sieve.GetResultData();
	for (const auto& nPrime : oResultData)
	{
		fOutputStream << nPrime << std::endl;
	}
}

int main()
{
	auto nTickCount_Start = ::GetTickCount64();

	DoGeneration_InitialMethod();
	//DoGeneration_SieveMethod();

	auto nTickCount_End = ::GetTickCount64();

	std::cout << "Done." << std::endl;
	char cValue;
	std::cin >> cValue;

	return 0;
}
