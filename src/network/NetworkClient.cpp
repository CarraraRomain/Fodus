#include "NetworkClient.hpp"

using namespace network;


void chat(const autobahn::wamp_event& event)
{
    LOG(INFO) << "CHAT : " << event.argument<std::string>(0);
}

NetworkClient::NetworkClient(boot::Bootstrap *boot, engine::AbstractEngine *engine, int cid) : Game(boot, engine, cid){

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

    game::Game::start();



    LOG(DEBUG) << "Started " << std::this_thread::get_id();
//    std::tuple<std::string> arguments(std::string("Client joined the game"));
//    m_handler.m_component->session()->publish("game.chat", arguments);
}

void NetworkClient::syncRequest()
{
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
    LOG(DEBUG) << "Publishing";
    std::tuple<std::string> arguments(std::string("Updating"));
    m_handler.m_component->session()->publish("game.chat", arguments);
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
