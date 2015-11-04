#pragma once

#include "LegacyElement.hpp"
#include <vector>
#include <memory>


class LegacyElementList
{
public:
	LegacyElementList();
	LegacyElementList(const LegacyElementList&);
	LegacyElementList& operator=(const LegacyElementList&);
	LegacyElementList(LegacyElementList&&) noexcept;
	LegacyElementList& operator=(LegacyElementList&&);
	~LegacyElementList();
	
	size_t size() const;
	void push_back(const LegacyElement& elt);
	void clear();

	std::unique_ptr<LegacyElement>& operator[](size_t i);
	const std::unique_ptr<LegacyElement>& operator[](size_t i) const;
	
private:
	std::vector<std::unique_ptr<LegacyElement> > m_elements;
};

