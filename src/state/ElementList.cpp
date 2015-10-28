#include "ElementList.hpp"



ElementList::ElementList()
{
}

ElementList::ElementList(ElementList const& list)
{
	m_elements = list.m_elements;
}

/*
 * Deep copy of each elt of the list
 */
ElementList& ElementList::operator=(const ElementList& list)
{
	if(this != &list)
	{
		for(Element* elt: list.m_elements)
		{
			Element* el = new Element;
			*el = *elt;
			m_elements.push_back(el);
		}
	}
	return *this;
}


ElementList& ElementList::operator=(ElementList&&)
{
	return *this;
}

ElementList::~ElementList()
{
	if(m_elements.size()>0)	for (Element* elt : m_elements) 
		delete elt;
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