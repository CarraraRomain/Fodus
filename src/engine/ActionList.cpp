#include "ActionList.hpp"


ActionList::ActionList()
{

}
/*

ActionList::ActionList(const ActionList& list) : m_actions(std::move(list.m_actions))
{

}
*/

ActionList::~ActionList()
{
}

size_t ActionList::size() const
{
	return m_actions.size();
}

void ActionList::push_back(Action* elt)
{
	std::unique_ptr<Action> act(elt);
	m_actions.push_back(std::move(act));
}

void ActionList::clear()
{
	return m_actions.clear();
}

void ActionList::remove(int i)
{

	auto it = std::find(m_actions.begin(), m_actions.end(), m_actions[i]);
	if (it != m_actions.end())
		m_actions.erase(it);
}

std::unique_ptr<Action>& ActionList::operator[](size_t i)
{
	return m_actions[i];
}

const std::unique_ptr<Action>& ActionList::operator[](size_t i) const
{
	return m_actions[i];
}