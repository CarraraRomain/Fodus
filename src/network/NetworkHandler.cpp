#include "NetworkHandler.hpp"

using namespace network;


void NetworkHandler::operator()(){
    start();
}


void NetworkHandler::test(const autobahn::wamp_event& event)
{
    LOG(INFO) << "CHAT TEST: " << event.argument<std::string>(0);
}

void NetworkHandler::start()
{
    try{

        LOG(DEBUG) << "Network Client starting : " << std::this_thread::get_id();
        f_started = m_component->start().then(
                boost::launch::any, [&](boost::future<void>) {
            auto session = m_component->session();
            std::cerr << "published event" << std::endl;
//
//
          session->subscribe("game.chat", boost::bind(&NetworkHandler::test, this, _1));
//        stopped = autobahn->stop().then([&](boost::future<void>) {
//            LOG(FATAL) << "AutoBahn stopped";
//            io_service.stop();
//        });
            network_ready = true;
            LOG(DEBUG) << "Future start: " << std::this_thread::get_id();
        });
        LOG(DEBUG) << "Network Client started: " << std::this_thread::get_id();
//        m_io_service.run();
        bt.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service)));

    }  catch (const std::exception& e) {
        LOG(DEBUG) << "Network Client failed: " << std::this_thread::get_id();
        std::cerr << e.what() << std::endl;
    }

}

NetworkHandler::~NetworkHandler()
{
    LOG(FATAL) << "Destroying Network";
    f_stopped = m_component->stop().then([&](boost::future<void>) {
        LOG(WARNING) << "Autobahn stopped";
        m_io_service.stop();
    });
}

NetworkHandler::NetworkHandler()
{
    realm = "fodus";
    debug = true;
    network_ready = false;
    m_endpoint.reset(new boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address::from_string("127.0.0.1"), 9999));
    m_component.reset(new autobahn::wamp_tcp_component(
            m_io_service, *m_endpoint, realm, debug));

}
