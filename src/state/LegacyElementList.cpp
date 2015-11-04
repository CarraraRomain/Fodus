#include "LegacyElementList.hpp"



LegacyElementList::LegacyElementList()
{
	
}
/*

LegacyElementList::LegacyElementList(const LegacyElementList& list) : m_elements(std::move(list.m_elements))
{
	
}
*/

LegacyElementList::~LegacyElementList()
{
}

size_t LegacyElementList::size() const
{
	return m_elements.size();
}

void LegacyElementList::push_back(const LegacyElement& elt)
{
	std::unique_ptr<LegacyElement> ptr;
	ptr.reset(new LegacyElement(elt));
	m_elements.push_back(std::move(ptr));
}

void LegacyElementList::clear()
{
	return m_elements.clear();
}

std::unique_ptr<LegacyElement>& LegacyElementList::operator[](size_t i)
{
	return m_elements[i];
}

const std::unique_ptr<LegacyElement>& LegacyElementList::operator[](size_t i) const
{
	return m_elements[i];
}
