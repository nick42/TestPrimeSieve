#pragma once

NAMESPACE_BEGIN(GeneratorMethod_Sieve)

class CSieveEntry
{
public:
	uintptr_t m_nSieveIndex;
	uintptr_t m_nPropertyIndicator;
	uintptr_t m_nMultipleValueWhichExceededBoundary;

public:
	constexpr CSieveEntry()
		: m_nSieveIndex{ 0 }
		, m_nPropertyIndicator{ 0 }
		, m_nMultipleValueWhichExceededBoundary{ 0 }
	{}
};

class CProcessingAndResultData
{
public:
	std::vector<CSieveEntry> m_oDataArray;
};

NAMESPACE_END //(GeneratorMethod_Sieve)

class CGeneratorMethod_Sieve
{
public:
	GeneratorMethod_Sieve::CProcessingAndResultData m_oProcessingAndResultData;

public:
	HRESULT DoGeneration();

public:
	CGeneratorMethod_Sieve()
	{}
	~CGeneratorMethod_Sieve() = default;
};

