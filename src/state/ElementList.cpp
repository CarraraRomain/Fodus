#include "ElementList.hpp"



ElementList::ElementList()
{
	
}

ElementList::~ElementList()
{
}

size_t ElementList::size() const
{
	return m_elements.size();
}

void ElementList::push_back(std::unique_ptr<Element> elt)
{
	m_elements.push_back(std::move(elt));
}

void ElementList::clear()
{
	return m_elements.clear();
}

std::unique_ptr<Element>& ElementList::operator[](size_t i)
{
	return m_elements[i];
}

const std::unique_ptr<Element>& ElementList::operator[](size_t i) const
{
	return m_elements[i];
}