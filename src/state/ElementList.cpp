#include "ElementList.hpp"
#include <iostream>


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

void ElementList::push_back(Element* elt)
{
	std::unique_ptr<Element> ptr(elt);
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

void ElementList::setAttribute(std::string attribut, int valeur, int uid)
{
	int i = findUid(uid);
	m_elements[i]->setAttribute(attribut,valeur);
}

void ElementList::setAttribute(std::string attribut, std::string valeur, int uid)
{
	int i = findUid(uid);
	m_elements[i]->setAttribute(attribut, valeur);
}

int ElementList::getAttribute(std::string attribute, int uid)
{
	if(findUid(uid)>= 0) return m_elements[findUid(uid)]->getAttribute(attribute);
}

int ElementList::findUid(int uid) {

	int i;

	for (i = 0; i < m_elements.size(); i++)
	{
		if (m_elements[i]->getUid() == uid) {
			
			return i;
		}
	}
	return -1;
}
