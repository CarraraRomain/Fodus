#include "ElementList.hpp"
#include <iostream>
#include "Case.hpp"


ElementList::ElementList()
{
	
}

ElementList::ElementList(const ElementList& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		std::unique_ptr<Element> ptr;
		ptr.reset(list[i]->clone());
		m_elements.push_back(std::move(ptr));
	}
	
}

ElementList::ElementList(ElementList&& list)
{
	m_elements = std::move(list.m_elements);
}

ElementList& ElementList::operator=(const ElementList& list)
{
	m_elements.resize(0);
	for (int i = 0; i < list.size(); i++)
	{
		std::unique_ptr<Element> ptr;
		ptr.reset(list[i]->clone());
		m_elements.push_back(std::move(ptr));
	}
	return *this;
}


ElementList& ElementList::operator=(ElementList&& list)
{
	m_elements.resize(0);
	for (int i = 0; i < list.size(); i++)
	{
		m_elements.push_back(std::move(list[i]));
	}
	return *this;
}

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

Competence * ElementList::getSkill(int uid, int index)
{
	if (findUid(uid) >= 0) return m_elements[findUid(uid)]->getSkill(index);
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

void ElementList::erase(int uid)
{
	int i = findUid(uid);
	m_elements.erase(m_elements.begin()+i);
}

ElementList::iterator ElementList::begin()
{
	return m_elements.begin();
}

ElementList::iterator ElementList::end()
{
	return m_elements.end();
}

ElementList::const_iterator ElementList::begin() const
{
	return m_elements.begin();
}

ElementList::const_iterator ElementList::cbegin() const
{
	return m_elements.cbegin();
}

ElementList::const_iterator ElementList::end() const
{
	return m_elements.end();
}

ElementList::const_iterator ElementList::cend() const
{
	return m_elements.cend();
}