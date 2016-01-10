#include "NetworkEngine.hpp"
#include "../game/Game.hpp"

using namespace network;


NetworkEngine::NetworkEngine(boot::Bootstrap* boot): engine::Engine(boot)
{

}

NetworkEngine::~NetworkEngine()
{

}


void NetworkEngine::notifyGlobal()
{
    m_handler.m_component->session()->publish("engine.update.global");
    // looping through players

    m_handler.m_component->session()->publish("engine.update.player");


    //engine::Engine::notifyGlobal();
}

void NetworkEngine::notifySingle(int pid)
{
//    engine::Engine::notifySingle(pid);
}

void NetworkEngine::notifyElement(state::Element &el)
{
//    engine::Engine::notifyElement(el);
}

void NetworkEngine::notifyTurn(int turn)
{
//    engine::Engine::notifyTurn(turn);
}

void NetworkEngine::notifyNowPlaying(int pid)
{
//    engine::Engine::notifyNowPlaying(pid);
}

void NetworkEngine::notifyCanPlay(int pid)
{
//    engine::Engine::notifyCanPlay(pid);
}

void NetworkEngine::notifyPlayer(engine::Player pl)
{
//    engine::Engine::notifyPlayer(pl);
}

void NetworkEngine::notifyHasPlayed(int pid)
{
//    engine::Engine::notifyHasPlayed(pid);
}

void NetworkEngine::connect(autobahn::wamp_invocation invocation)
{
 LOG(DEBUG) << "NETWORKENGINE: Player Connected! ";
    invocation->result(std::make_tuple(200));
}

void NetworkEngine::start()
{
    LOG(DEBUG) << "NETWORKENGINE: Starting";

    m_handler();

    engine::Engine::start();
    // async network : waiting for it
    while(!m_handler.network_ready);

    // register RPC
    m_handler.m_component->session()->provide("engine.sync.request",
                                              boost::bind(&NetworkEngine::syncRequest, this, _1));
    m_handler.m_component->session()->provide("engine.player.get",
                                              boost::bind(&NetworkEngine::getPlayer, this, _1));
    m_handler.m_component->session()->provide("engine.unit.map",
                                              boost::bind(&NetworkEngine::getMap, this, _1));
    m_handler.m_component->session()->provide("engine.player.connect",
                                              boost::bind(&NetworkEngine::connect, this, _1));



    // msgpack serialization test
//    std::stringstream ss;
//    msgpack::pack(ss, *(getState().getList()));
//    //std::cout << ss.str() << std::endl;
//    msgpack::unpacked unp;
//    msgpack::unpack(unp, ss.str().data(), ss.str().size());
//    msgpack::object obj = unp.get();
//    std::cout << obj << std::endl;
//    state::ElementList el = obj.as<state::ElementList>();

   // assert(obj.as<state::ElementList>() == getState().getList());
    LOG(DEBUG) << "NETWORKENGINE: Started";
}

void NetworkEngine::syncRequest(autobahn::wamp_invocation invocation)
{
//    msgpack::sbuffer buffer;
//    msgpack::pack(buffer, );
    state::Etat e = getState();
    invocation->result(std::make_tuple(e));
}

void NetworkEngine::syncFull(int pid)
{
 throw std::logic_error("Not implemented : Sync");
}

int NetworkEngine::whoIsPlaying()
{
    throw std::logic_error("Not implemented: Who");
}

void NetworkEngine::getMap(autobahn::wamp_invocation invocation)
{
    int uid = invocation->argument<int>(0);
    std::vector<std::vector<int> > map =  engine::Engine::getMap(uid);

    invocation->result(map);
}

std::map<int, engine::Player> &NetworkEngine::getPlayers()
{
    return engine::Engine::getPlayers();
   // throw std::logic_error("Not implemented, get players");
}

void NetworkEngine::getPlayer(autobahn::wamp_invocation invocation)
{
    int uid = invocation->argument<int>(0);
    engine::Player pl =  engine::Engine::getPlayer(uid);

    invocation->result(pl);
}

int NetworkEngine::getMapValue(int x, int y, int uid)
{
    return engine::Engine::getMapValue(x,y,uid);
}

void NetworkEngine::notifyGameEnd(engine::Player pl, int score)
{
    engine::Engine::notifyGameEnd(pl, score);
}

int NetworkEngine::registerPlayer(int player)
{
    return 0;
}

void NetworkEngine::registerPlayer(autobahn::wamp_invocation invocation)
{

}

void NetworkEngine::processCommandList()
{

}
