#include "ElementList.hpp"



ElementList::ElementList()
{
}

ElementList::ElementList(const ElementList&)
{
}

ElementList& ElementList::operator=(const ElementList&)
{
	return *this;
}


ElementList& ElementList::operator=(ElementList&&)
{
	return *this;
}

ElementList::~ElementList()
{
	for (Element* elt : m_elements) delete elt;
}

size_t ElementList::size() const
{
	return m_elements.size();
}

void ElementList::push_back(Element* elt)
{
	m_elements.push_back(elt);
}

void ElementList::clear()
{
	return m_elements.clear();
}

Element*& ElementList::operator[](size_t i)
{
	return m_elements[i];
}

const Element* ElementList::operator[](size_t i) const
{
	return m_elements[i];
}