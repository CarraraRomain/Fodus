#include "ElementList.hpp"



ElementList::ElementList()
{
	
}
/*

ElementList::ElementList(const ElementList& list) : m_elements(std::move(list.m_elements))
{
	
}
*/

ElementList::~ElementList()
{
}

size_t ElementList::size() const
{
	return m_elements.size();
}

void ElementList::push_back(const Element& elt)
{
	std::unique_ptr<Element> ptr;
	ptr.reset(new Element(elt));
	m_elements.push_back(std::move(ptr));
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