#include "NetworkClient.hpp"

using namespace network;


void chat(const autobahn::wamp_event& event)
{
    LOG(INFO) << "CHAT : " << event.argument<std::string>(0);
}

NetworkClient::NetworkClient(boot::Bootstrap *boot, engine::AbstractEngine *engine, int cid) : Game(boot, engine, cid), m_engine(this){

}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::load()
{
    game::Game::load();
}

void NetworkClient::start()
{

    m_handler();
    // async network : waiting for it to be available
    while(!m_handler.network_ready);
    m_handler.m_component->session()->subscribe("engine.update.global",
                                                boost::bind(&NetworkClient::subGlobal, this, _1));
    m_handler.m_component->session()->subscribe("engine.update.player",
                                                boost::bind(&NetworkClient::subPlayer, this, _1));
     m_handler.m_component->session()->subscribe("engine.update.now",
                                                boost::bind(&NetworkClient::subNowPlaying, this, _1));
    game::Game::start();



    LOG(DEBUG) << "Started " << std::this_thread::get_id();

//    std::tuple<std::string> arguments(std::string("Client joined the game"));
//    m_handler.m_component->session()->publish("game.chat", arguments);
}

void NetworkClient::syncRequest()
{
    while(!m_handler.network_ready);
    game::Game::syncRequest();
}

void NetworkClient::whoIsPlaying()
{
    game::Game::whoIsPlaying();
}

void NetworkClient::update(ObsType type)
{
    game::Game::update(type);
}

void NetworkClient::updateGlobal(state::Etat &e)
{
    LOG(DEBUG) << "Update Global";
//    std::tuple<std::string> arguments(std::string("Updating"));
//    m_handler.m_component->session()->publish("game.chat", arguments);
    game::Game::updateGlobal(e);
}

void NetworkClient::updateElement(state::Element &el)
{
    game::Game::updateElement(el);
}

void NetworkClient::updateTurn(int turn)
{
    game::Game::updateTurn(turn);
}

void NetworkClient::updatePlayer(engine::Player pl)
{
    game::Game::updatePlayer(pl);
}

void NetworkClient::updateGameEnd(int score)
{
    game::Game::updateGameEnd(score);
}

void NetworkClient::updateNowPlaying(int pid)
{
    game::Game::updateNowPlaying(pid);
}

void NetworkClient::canPlay(int pid)
{
    game::Game::canPlay(pid);
}

void NetworkClient::hasPlayed(int pid)
{
    game::Game::hasPlayed(pid);
}

void NetworkClient::sync(state::ElementList list)
{
    game::Game::sync(list);
}

void NetworkClient::handleUpdate()
{

    game::Game::handleUpdate();
}

void NetworkClient::run()
{
    LOG(DEBUG) << "Waiting for network... " << m_handler.network_ready;
    while(!m_handler.network_ready);
    //m_handler.session()->subscribe("game.chat", chat);
    game::Game::run();
}

engine::AbstractEngine* NetworkClient::getEngine()
{
    return &m_engine;
}

void NetworkClient::checkMoveMap()
{
    LOG(DEBUG) << "Check Move Map";
   getEngine()->getMap(1);
}

/**
 * Promise callback : Sync move map
 */
void NetworkClient::checkMoveMap(std::vector<std::vector<int> > map)
{
    LOG(DEBUG) << "Sync Move Map";
//    if (is_playing) m_game_scene.getInfos()->syncMoveMap(map);
//    else m_game_scene.getInfos()->resetMoveMap();
    LOG(DEBUG) << "End Sync Move Map";
}

void NetworkClient::subGlobal(const autobahn::wamp_event &event)
{
    LOG(DEBUG) << "Update GLOBAL thr WAMP";
    state::Etat e = event.argument<state::Etat>(0);
    game::Game::updateGlobal(e);
}

void NetworkClient::subPlayer(const autobahn::wamp_event &event)
{
    LOG(DEBUG) << "Update PLAYER thr WAMP";
    engine::Player pl = event.argument<engine::Player>(0);
    game::Game::updatePlayer(pl);
}



void NetworkClient::subNowPlaying(const autobahn::wamp_event &event)
{
    LOG(DEBUG) << "Update PLAYER thr WAMP";
    int pid = event.argument<uint64_t>(0);
    game::Game::updateNowPlaying(pid);
}
