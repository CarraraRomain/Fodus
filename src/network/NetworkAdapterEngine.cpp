
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
    while(!m_client->m_handler.network_ready);
    autobahn::wamp_call_options call_options;
    call_options.set_timeout(std::chrono::seconds(10));

    std::tuple<uint64_t> arguments(m_client->CID);
    futures[1] = m_client->m_handler.m_component->session()->call("engine.sync.request", arguments, call_options).then(
            [&](boost::future<autobahn::wamp_call_result> result) {
                try {

                    state::Etat e = result.get().argument<state::Etat>(0);

//                    state::Etat e = (result.get().arguments<std::array<state::Etat>>())[0];
                    m_client->updateGlobal(e);
                    std::cerr << "call success " << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "call failed: " << e.what() << std::endl;
                    //return (uint64_t) 500;
                }

            });
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

                    std::vector<std::vector<int> > map = result.get().argument<std::vector<std::vector<int> > >(0);
                    m_client->checkMoveMap(map);
//                    state::Etat e = (result.get().arguments<std::array<state::Etat>>())[0];
                   // m_client->updateGlobal(e);
                    std::cerr << "call success " << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "call failed: " << e.what() << std::endl;
                    //return (uint64_t) 500;
                }

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

}
