#pragma once
#include "Action.hpp"
#include <vector>

class ActionList
{
public:
	ActionList();
	~ActionList();
	ActionList(const ActionList&);
	ActionList& operator=(const ActionList&);
	ActionList(ActionList&&) noexcept;
	ActionList& operator=(ActionList&&);

	size_t size() const;
	void push_back(Action*);
	void clear();
	void remove(int i);
	std::unique_ptr<Action>& operator[](size_t i);
	const std::unique_ptr<Action>& operator[](size_t i) const;
private:
	std::vector<std::unique_ptr<Action>> m_actions;
};