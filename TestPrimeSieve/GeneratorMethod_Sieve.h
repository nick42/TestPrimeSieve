#pragma once

#include <boost/iterator_adaptors.hpp>

NAMESPACE_BEGIN(GeneratorMethod_Sieve)

class CSieveEntry
{
public:
	uintptr_t m_nSieveIndex;
	uintptr_t m_nPropertyIndicator;
	uintptr_t m_nMultipleValueWhichExceededBoundary;

public:
	constexpr bool IsMarkedAsComposite() const
	{
		return ((m_nPropertyIndicator & 0x01) == 0x01);
	}

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

class CPrimeResultIterator
	: public boost::iterator_facade<CPrimeResultIterator, uintptr_t const, boost::forward_traversal_tag>
{
private:
	friend class boost::iterator_core_access;

protected:
	const CProcessingAndResultData& m_oProcessingAndResultData;
	uintptr_t m_nSieveEntryVectorIndex;

protected:
	void OnInit_IncrementToFirstPrime()
	{
		while (m_nSieveEntryVectorIndex < 2)
		{
			m_nSieveEntryVectorIndex++;
		}

		while ((m_nSieveEntryVectorIndex < m_oProcessingAndResultData.m_oDataArray.size()) &&
			(m_oProcessingAndResultData.m_oDataArray[m_nSieveEntryVectorIndex].IsMarkedAsComposite()))
		{
			m_nSieveEntryVectorIndex++;
		}
	}

public:
	void increment()
	{
		while (m_nSieveEntryVectorIndex < 2)
		{
			m_nSieveEntryVectorIndex++;
		}
		m_nSieveEntryVectorIndex++;

		while ((m_nSieveEntryVectorIndex < m_oProcessingAndResultData.m_oDataArray.size()) &&
			(m_oProcessingAndResultData.m_oDataArray[m_nSieveEntryVectorIndex].IsMarkedAsComposite()))
		{
			m_nSieveEntryVectorIndex++;
		}
		// At this point, we should either be at the end of the array, or on a prime entry
	}

	bool equal(const CPrimeResultIterator& oOther) const
	{
		if (&m_oProcessingAndResultData != &oOther.m_oProcessingAndResultData)
		{
			return false;
		}
		if (m_nSieveEntryVectorIndex == oOther.m_nSieveEntryVectorIndex)
		{
			return true;
		}
		// If both indexes are "beyond" the array end, then they are both at the semantic "end", and equal
		if ((m_nSieveEntryVectorIndex >= m_oProcessingAndResultData.m_oDataArray.size()) &&
			(oOther.m_nSieveEntryVectorIndex >= oOther.m_oProcessingAndResultData.m_oDataArray.size()))
		{
			return true;
		}

		return false;
	}

	uintptr_t const& dereference() const
	{
		return m_oProcessingAndResultData.m_oDataArray[m_nSieveEntryVectorIndex].m_nSieveIndex;
	}

public:
	explicit CPrimeResultIterator(const CProcessingAndResultData& oProcessingAndResultData, uintptr_t nIndex = 0)
		: m_oProcessingAndResultData{ oProcessingAndResultData }
		, m_nSieveEntryVectorIndex{ nIndex }
	{
		OnInit_IncrementToFirstPrime();
	}
};

class CResultData
{
protected:
	const CProcessingAndResultData& m_oProcessingAndResultData;

public:
	CPrimeResultIterator begin() const
	{
		return CPrimeResultIterator{ m_oProcessingAndResultData, 2 };
	}
	CPrimeResultIterator end() const
	{
		return CPrimeResultIterator{ m_oProcessingAndResultData, m_oProcessingAndResultData.m_oDataArray.size() };
	}

public:
	explicit CResultData(const CProcessingAndResultData& oProcessingAndResultData)
		: m_oProcessingAndResultData{ oProcessingAndResultData }
	{}
};

NAMESPACE_END //(GeneratorMethod_Sieve)

class CGeneratorMethod_Sieve
{
public:
	GeneratorMethod_Sieve::CProcessingAndResultData m_oProcessingAndResultData;

public:
	HRESULT DoGeneration();

public:
	inline auto GetResultData() const
	{
		return GeneratorMethod_Sieve::CResultData{ m_oProcessingAndResultData };
	}

public:
	CGeneratorMethod_Sieve()
	{}
	~CGeneratorMethod_Sieve() = default;
};

