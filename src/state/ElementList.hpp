#pragma once

#include "Element.h"
#include "Perso.hpp"
#include <vector>
#include <memory>
#include <string>


class ElementList
{
public:
	typedef std::vector<std::unique_ptr<Element>>::iterator iterator;
	typedef std::vector<std::unique_ptr<Element>>::const_iterator const_iterator;

	ElementList();
	ElementList(const ElementList&);
	ElementList(ElementList&&);
	ElementList& operator=(const ElementList&);
	ElementList& operator=(ElementList&&);
	~ElementList();
	
	size_t size() const;
	void push_back(Element* elt);
	void clear();

	std::unique_ptr<Element>& operator[](size_t i);
	const std::unique_ptr<Element>& operator[](size_t i) const;

	void setAttribute(std::string attribut, int valeur, int uid);
	void setAttribute(std::string attribut, std::string valeur, int uid);

	int getAttribute(std::string attribute, int uid);

	Competence* getSkill(int uid, int index);

	int findUid(int uid);

	void erase(int uid);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator cbegin() const;
	const_iterator end() const ;
	const_iterator cend() const ;

private:
	std::vector<std::unique_ptr<Element> > m_elements;
};

