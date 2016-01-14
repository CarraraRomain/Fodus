#include "NetworkEngine.hpp"
#include "../game/Game.hpp"
#include "../engine/EndTurnCommand.hpp"

using namespace network;


NetworkEngine::NetworkEngine(boot::Bootstrap* boot): engine::Engine(boot)
{

}

NetworkEngine::~NetworkEngine()
{

}


void NetworkEngine::notifyGlobal()
{
    LOG(DEBUG) << "Notify Global thr WAMP";
    std::tuple<state::Etat> arguments(getState());
    m_handler.m_component->session()->publish("engine.update.global", arguments);
    // looping through players
    engine::Player pl = m_players[current_player_uid];
    std::tuple<engine::Player> arg(pl);
    m_handler.m_component->session()->publish("engine.update.player", arg);


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
    LOG(DEBUG) << "Notify Now Playing thr WAMP";
    std::tuple<uint64_t> arguments(pid);
    m_handler.m_component->session()->publish("engine.update.now", arguments);

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


void NetworkEngine::start()
{
    LOG(DEBUG) << "NETWORKENGINE: Starting";

    m_handler();

    // async network : waiting for it
    while(!m_handler.network_ready);

    engine::Engine::start();
    // register RPC
    m_handler.m_component->session()->provide("engine.command.add",
                                              boost::bind(&NetworkEngine::handleCommand, this, _1));
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
/**
 * RPC : engine.sync.request
 */
void NetworkEngine::syncRequest(autobahn::wamp_invocation invocation)
{
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

/**
 * RPC : engine.unit.map
 */
void NetworkEngine::getMap(autobahn::wamp_invocation invocation)
{
    int uid = invocation->argument<int>(0);
    std::vector<std::vector<int> > map =  engine::Engine::getMap(uid);

    invocation->result(std::make_tuple(map));
}

std::map<int, engine::Player> &NetworkEngine::getPlayers()
{
    return engine::Engine::getPlayers();
   // throw std::logic_error("Not implemented, get players");
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
    engine::Engine::processCommandList();
}

/**
 * RPC : engine.player.get
 */
void NetworkEngine::getPlayer(autobahn::wamp_invocation invocation)
{
    int uid = invocation->argument<int>(0);
    engine::Player pl =  engine::Engine::getPlayer(uid);

    invocation->result(pl);
}



/**
 * RPC engine.player.connect
 */
void NetworkEngine::connect(autobahn::wamp_invocation invocation)
{
    LOG(DEBUG) << "NETWORKENGINE: Player Connected! ";
    invocation->result(std::make_tuple(200));
}


/**
 * RPC engine.command.add
 */
void NetworkEngine::handleCommand(autobahn::wamp_invocation invocation)
{
    LOG(DEBUG) << "Command recvd from WAMP";
//    CommandType type = invocation->argument<>(0)[0];
//        LOG(DEBUG) << "receved com type :" << type;
//    engine::Command* com = invocation->argument<engine::Command*>(0);
    CommandType type = invocation->argument<CommandType>(0);

    if(type == Move){
        engine::MoveCommand com = invocation->argument<engine::MoveCommand>(1);
        engine::Engine::handleCommand(&com);

    }
    else if(type == EndTurn){
        engine::EndTurnCommand com = invocation->argument<engine::EndTurnCommand>(1);
        engine::Engine::handleCommand(&com);

    }
    else{
        engine::SkillCommand com = invocation->argument<engine::SkillCommand>(1);
        engine::Engine::handleCommand(&com);
    }

//    delete(com);
    invocation->result(std::make_tuple(200));
}
