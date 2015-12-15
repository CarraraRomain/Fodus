#include "CommandList.hpp"

using namespace engine;

CommandList::CommandList()
{
}


CommandList::~CommandList()
{
}

bool CommandList::empty() const {
 return m_queue.empty();
}

int CommandList::size() const {
 return int( m_queue.size());
}

void CommandList::push(Command* com) {
 std::unique_ptr<Command> ptr(com->clone());
m_queue.push(std::move(ptr));
}

void CommandList::pop() {
 m_queue.pop();
}

Command* CommandList::front() {
 return m_queue.front().get();
}

const Command* CommandList::front() const {
 return m_queue.front().get();
}
