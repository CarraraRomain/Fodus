#pragma once

#include "Element.h"
#include <vector>


class ElementList
{
public:
	ElementList();
	//ElementList(const ElementList&);
	ElementList(ElementList const& ElementList);
	ElementList& operator=(const ElementList&);
	//ElementList(ElementList&&) noexcept;
	ElementList& operator=(ElementList&&);
	~ElementList();
	
	size_t size() const;
	void push_back(Element* elt);
	void clear();

	Element*& operator[](size_t i);
	const Element* operator[](size_t i) const;

private:
	std::vector<Element*> m_elements;
};

