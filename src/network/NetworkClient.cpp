#include "NetworkClient.hpp"

using namespace network;

NetworkClient::NetworkClient(boot::Bootstrap *boot, engine::AbstractEngine *engine, int cid) : Game(boot, engine, cid){

    realm = "fodus";
    bool debug = true;
    endpoint.reset(new boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address::from_string("127.0.0.1"), 9999));
    autobahn.reset(new autobahn::wamp_tcp_component(
                    io_service, *endpoint, realm, debug));
}

NetworkClient::~NetworkClient()
{
        stopped = autobahn->stop().then([&](boost::future<void>) {
            LOG(WARNING) << "Autobahn stopped";
            io_service.stop();
        });
}

void chat(const autobahn::wamp_event& event)
{
    LOG(INFO) << "CHAT : " << event.argument<std::string>(0);
}

void NetworkClient::load()
{
    game::Game::load();
}

void NetworkClient::start()
{
    LOG(DEBUG) << "Network Client starting : " << getpid();
try{
    started = autobahn->start().then(
            boost::launch::any, [&](boost::future<void>) {
        auto session = autobahn->session();
        std::tuple<std::string> arguments(std::string("hello"));
        session->subscribe("game.chat", &chat);
        session->publish("game.chat", arguments);
        std::cerr << "published event" << std::endl;

//        stopped = autobahn->stop().then([&](boost::future<void>) {
//            LOG(FATAL) << "AutoBahn stopped";
//            io_service.stop();
//        });
    });
    boost::thread bt(boost::bind(&boost::asio::io_service::run, &io_service));
//    io_service.run();
    //stopped.wait();
}  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return;
}
    game::Game::start();
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
    autobahn->session()->publish("game.chat", arguments);
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
        stopped = autobahn->stop().then([&](boost::future<void>) {
            LOG(FATAL) << "AutoBahn stopped";
            io_service.stop();
        });
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
