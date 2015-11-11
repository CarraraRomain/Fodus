#pragma once

#include "Element.h"
#include "perso.hpp"
#include <vector>
#include <memory>
#include <string>


class ElementList
{
public:
	ElementList();
	ElementList(const ElementList&);
	ElementList& operator=(const ElementList&);
	ElementList(ElementList&&) noexcept;
	ElementList& operator=(ElementList&&);
	~ElementList();
	
	size_t size() const;
	void push_back(Element& elt);
	void clear();

	std::unique_ptr<Element>& operator[](size_t i);
	const std::unique_ptr<Element>& operator[](size_t i) const;

	void setAttribute(std::string attribut, int valeur, int uid);
	void setAttribute(std::string attribut, std::string valeur, int uid);

	int getAttribute(std::string attribute, int uid);

	int findUid(int uid);

private:
	std::vector<std::unique_ptr<Element> > m_elements;
};

