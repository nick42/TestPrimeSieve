#pragma once

#include <boost/iterator_adaptors.hpp>

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

class CPrimeResultIterator
	: public boost::iterator_facade<CPrimeResultIterator, uintptr_t const, boost::forward_traversal_tag>
{
private:
	friend class boost::iterator_core_access;

protected:
	std::list<SPCPrimeEntry>::const_iterator m_iterResultIndex;

public:
	void increment()
	{
		m_iterResultIndex++;
	}

	bool equal(const CPrimeResultIterator& oOther) const
	{
		return (m_iterResultIndex == oOther.m_iterResultIndex);
	}

	uintptr_t const& dereference() const
	{
		const auto& spPrimeEntry = *m_iterResultIndex;
		return spPrimeEntry->m_nPrime;
	}

public:
	explicit CPrimeResultIterator(const std::list<SPCPrimeEntry>::const_iterator& iterResultIndex)
		: m_iterResultIndex{ iterResultIndex }
	{}
};


class CResultData
{
protected:
	const CProcessingAndResultData& m_oProcessingAndResultData;

public:
	CPrimeResultIterator begin() const
	{
		return CPrimeResultIterator{ m_oProcessingAndResultData.m_oOrderedPrimeEntryList.begin() };
	}
	CPrimeResultIterator end() const
	{
		return CPrimeResultIterator{ m_oProcessingAndResultData.m_oOrderedPrimeEntryList.end() };
	}

public:
	explicit CResultData(const CProcessingAndResultData& oProcessingAndResultData)
		: m_oProcessingAndResultData{ oProcessingAndResultData }
	{}
};

NAMESPACE_END //(GeneratorMethod_Initial)

class CGeneratorMethod_Initial
{
public:
	GeneratorMethod_Initial::CProcessingAndResultData m_oProcessingAndResultData;

public:
	HRESULT DoGeneration();

public:
	inline auto GetResultData() const
	{
		return GeneratorMethod_Initial::CResultData{ m_oProcessingAndResultData };
	}

public:
	CGeneratorMethod_Initial()
	{}
	~CGeneratorMethod_Initial() = default;
};

