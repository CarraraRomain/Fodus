#pragma once

#include "Element.h"
#include <vector>
#include <memory>


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
	void push_back(const Element& elt);
	void clear();

	std::unique_ptr<Element>& operator[](size_t i);
	const std::unique_ptr<Element>& operator[](size_t i) const;
	
private:
	std::vector<std::unique_ptr<Element> > m_elements;
};

