
/**
 * This class is a adpater to the Engine methods the Game class calls
 * to support calling the network engine
 *
 */



#include "NetworkAdapterEngine.hpp"
#include "NetworkClient.hpp"

using namespace network;


NetworkAdapterEngine::NetworkAdapterEngine(NetworkClient* client): m_client(client)
{

}

NetworkAdapterEngine::~NetworkAdapterEngine()
{

}

int NetworkAdapterEngine::registerPlayer(int player)
{
    return 0;
}

void NetworkAdapterEngine::processCommandList()
{

}

state::Etat &NetworkAdapterEngine::getState()
{
    throw std::logic_error("Not implemented: State");
}

int NetworkAdapterEngine::registerPlayer(int player, engine::EngineObserver *obs)
{
   return 200;
}

int NetworkAdapterEngine::connect(int client)
{
    while(!m_client->m_handler.network_ready);
    autobahn::wamp_call_options call_options;
    call_options.set_timeout(std::chrono::seconds(10));

    std::tuple<uint64_t> arguments(m_client->CID);
    futures[1] = m_client->m_handler.m_component->session()->call("engine.player.connect", arguments, call_options).then(
            [&](boost::future<autobahn::wamp_call_result> result) {
                try {
                    uint64_t rc = result.get().argument<uint64_t>(0);
                    std::cerr << "call result: " << rc << std::endl;
                    //return rc;
                } catch (const std::exception& e) {
                    std::cerr << "call failed: " << e.what() << std::endl;
                    //return (uint64_t) 500;
                }

            });
return 200;
}

void NetworkAdapterEngine::start()
{

}

void NetworkAdapterEngine::run()
{

}

state::ElementList NetworkAdapterEngine::syncRequest()
{
    return state::ElementList();
}

void NetworkAdapterEngine::syncFull(int pid)
{
    LOG(DEBUG) << "Enter sync full";
    while(!m_client->m_handler.network_ready);
    autobahn::wamp_call_options call_options;
    call_options.set_timeout(std::chrono::seconds(10));

    std::tuple<uint64_t> arguments(m_client->CID);
    futures[1] = m_client->m_handler.m_component->session()->call("engine.sync.request", arguments, call_options).then(
            [&](boost::future<autobahn::wamp_call_result> result) {
                try {
                    LOG(DEBUG) << "Future sync full";
                    state::Etat e = result.get().argument<state::Etat>(0);

                    m_client->updateGlobal(e);
                    std::cerr << "call success " << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "call failed: " << e.what() << std::endl;
                    //return (uint64_t) 500;
                }

            });
    LOG(DEBUG) << "End sync full";
}

int NetworkAdapterEngine::whoIsPlaying()
{
    return 0;
}
/**
 * TODO Implementation
 */
std::vector<std::vector<int> > NetworkAdapterEngine::getMap(int uid)
{
    while(!m_client->m_handler.network_ready);
    autobahn::wamp_call_options call_options;
    call_options.set_timeout(std::chrono::seconds(10));

    std::tuple<uint64_t> arguments(uid);
    futures[1] = m_client->m_handler.m_component->session()->call("engine.unit.map", arguments, call_options).then(
            [&](boost::future<autobahn::wamp_call_result> result) {
                try {
                    LOG(DEBUG) << "Received Move Map";
                    std::vector<std::vector<int> > map = result.get().argument<std::vector<std::vector<int> > >(0);
                    m_client->checkMoveMap(map);
//                    state::Etat e = (result.get().arguments<std::array<state::Etat>>())[0];
                   // m_client->updateGlobal(e);
                    std::cerr << "call success " << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "call failed: " << e.what() << std::endl;
                    //return (uint64_t) 500;
                }
                LOG(DEBUG) << "End Received Move Map";
            });
    std::vector<std::vector<int> > vect;
    return vect;
}

std::map<int, engine::Player> &NetworkAdapterEngine::getPlayers()
{
//    throw std::logic_error("Not implemented");
}

engine::Player &NetworkAdapterEngine::getPlayer(int i)
{
//    throw std::logic_error("Not implemented");
}

void NetworkAdapterEngine::propagate(int x, int y, int valeur, int uid)
{

}

int NetworkAdapterEngine::getMapValue(int x, int y, int uid)
{
    return 0;
}

void NetworkAdapterEngine::handleCommand(engine::Command *com)
{
    LOG(DEBUG) << "Enter Handle Command";
//    while(!m_client->m_handler.network_ready);
    autobahn::wamp_call_options call_options;
    call_options.set_timeout(std::chrono::seconds(10));

if(com->type == Move){
    std::tuple<CommandType , engine::MoveCommand> arguments(com->type, *dynamic_cast<engine::MoveCommand*>(com));
    futures[2] = m_client->m_handler.m_component->session()->call("engine.command.add", arguments, call_options).then(
            [&](boost::future<autobahn::wamp_call_result> result) {
                try {
                    LOG(DEBUG) << "Future handled command";
                    std::cerr << "call success " << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "call failed: " << e.what() << std::endl;

                }

            });
}

else
{
    std::tuple<CommandType , engine::SkillCommand> arguments(com->type, *dynamic_cast<engine::SkillCommand*>(com));
    futures[2] = m_client->m_handler.m_component->session()->call("engine.command.add", arguments, call_options).then(
            [&](boost::future<autobahn::wamp_call_result> result) {
                try {
                    LOG(DEBUG) << "Future handled command";
                    std::cerr << "call success " << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "call failed: " << e.what() << std::endl;

                }

            });
}




}
