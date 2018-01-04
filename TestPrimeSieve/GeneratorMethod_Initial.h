#pragma once

NAMESPACE_BEGIN(GeneratorMethod_Initial)

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

	inline void IncrementToNextMultiple()
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

class CProcessingAndResultData
{
public:
	std::multimap<uintptr_t, SPCPrimeEntry> m_oCurrentValueToPrimeEntryMap;
	std::list<SPCPrimeEntry> m_oOrderedPrimeEntryList;
};

NAMESPACE_END //(GeneratorMethod_Initial)

class CGeneratorMethod_Initial
{
public:
	GeneratorMethod_Initial::CProcessingAndResultData m_oProcessingAndResultData;

public:
	HRESULT DoGeneration();

public:
	CGeneratorMethod_Initial()
	{}
	~CGeneratorMethod_Initial() = default;
};

