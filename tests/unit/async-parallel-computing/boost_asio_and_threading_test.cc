// http://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock
//
// https://www.quantnet.com/threads/c-multithreading-in-boost.10028/
//
// Lock != mutex и может строится на разных примитивах

#include <gtest/gtest.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <vector>
#include <iostream>

using boost::thread;
using std::vector;
using boost::shared_ptr;

// http://stackoverflow.com/questions/4260209/creating-not-copyable-but-movable-objects-in-c
// thread - movable
class callable {  // must be copyable
public:
  callable() {}  // step 1
  void operator()() {  // можно и с аргументами
    // boost::this_thread::disable_interruption di;
    // можно запрещать и разреашать прерывание потока

    return;
  }
private:
  //callable& operator=(const callable& val);  // not protect
  //callable(const callable& r);  // step 1  // this protect
};

static boost::thread copies_are_safe() {
  callable x;
  return boost::thread(x);  // create copy
}

void f()
{
  boost::thread some_thread=copies_are_safe();
  some_thread.join();
}


TEST(Parallel, ExecutionExceptionsAndInterraption) {
  // http://www.boost.org/doc/libs/1_55_0/doc/html/thread/thread_management.html
  // Watch - interruption points
  f();
  //TODO: interrupt() - не сразу, а в точке, но как быть с исключениями

  thread t = copies_are_safe();
}

TEST(Parallel, SyncLocks) {
  // !! http://home.roadrunner.com/~hinnant/mutexes/locking.html
  // Locable

  // TimeLocable

  // SharedLocable - MRd-Single Wr

  // UpgradeLocable
  // http://stackoverflow.com/questions/7378266/upgrading-boostshared-lock-to-exclusive-lock
  // http://stackoverflow.com/questions/4203467/multiple-readers-single-writer-locks-in-boost?rq=1
  // http://stackoverflow.com/questions/6752880/how-to-upgrade-mutex-ownership-from-shared-to-upgrade
}

TEST(Parallel, Multilock) {
    // http://www.justsoftwaresolutions.co.uk/threading/acquiring-multiple-locks-without-deadlock.html
}

TEST(Parallel, CondVars) {

}

TEST(Parallel, Barrier) {

}

// Asio
// http://stackoverflow.com/questions/11191028/boostasio-how-to-interrupt-a-blocked-tcp-server-thread
void startAccept( boost::asio::ip::tcp::acceptor& );

void serverThreadFunc( boost::asio::io_service& io_service )
{
  using boost::asio::ip::tcp;
  using boost::asio::ip::udp;
  tcp::acceptor acceptor( io_service, tcp::endpoint( tcp::v4(), 8080 ) );

  // Add a job to start accepting connections.
  startAccept( acceptor );

  // Process event loop.
  io_service.run();

  std::cout << "Server thread exiting." << std::endl;
}

void handleAccept( const boost::system::error_code& error,
                   boost::shared_ptr< boost::asio::ip::tcp::socket > socket,
                   boost::asio::ip::tcp::acceptor& acceptor )
{
  // If there was an error, then do not add any more jobs to the service.
  if ( error )
  {
    std::cout << "Error accepting connection: " << error.message()
              << std::endl;
    return;
  }

  // Otherwise, the socket is good to use.
  std::cout << "Doing things with socket..." << std::endl;

  // Perform async operations on the socket.

  // Done using the socket, so start accepting another connection.  This
  // will add a job to the service, preventing io_service::run() from
  // returning.
  std::cout << "Done using socket, ready for another connection."
            << std::endl;
  startAccept( acceptor );
}

void startAccept( boost::asio::ip::tcp::acceptor& acceptor )
{
  using boost::asio::ip::udp;
  using boost::asio::ip::tcp;
  boost::shared_ptr< tcp::socket > socket(
                                new tcp::socket( acceptor.get_io_service() ) );

  // Add an accept call to the service.  This will prevent io_service::run()
  // from returning.
  std::cout << "Waiting on connection" << std::endl;
  acceptor.async_accept( *socket,
    boost::bind( handleAccept,
      boost::asio::placeholders::error,
      socket,
      boost::ref( acceptor ) ) );
}

TEST(Parallel, AsioTerminate)
{
  using boost::asio::ip::tcp;

  // Create io service.
  boost::asio::io_service io_service;

  // Create server thread that will start accepting connections.
  boost::thread server_thread( serverThreadFunc, boost::ref( io_service ) );

  // Sleep for 10 seconds, then shutdown the server.
  std::cout << "Stopping service in 10 seconds..." << std::endl;
  boost::this_thread::sleep( boost::posix_time::seconds( 3 ) );
  std::cout << "Stopping service now!" << std::endl;

  // Stopping the io_service is a non-blocking call.  The threads that are
  // blocked on io_service::run() will try to return as soon as possible, but
  // they may still be in the middle of a handler.  Thus, perform a join on
  // the server thread to guarantee a block occurs.
  io_service.stop();

  std::cout << "Waiting on server thread..." << std::endl;
  server_thread.join();
  std::cout << "Done waiting on server thread." << std::endl;
}

// http://www.boost.org/doc/libs/1_35_0/doc/html/boost_asio/tutorial/tutdaytime6.html
// http://stackoverflow.com/questions/4808848/boost-asio-stopping-io-service
using boost::asio::ip::udp;
class udp_server {
public:
  udp_server(boost::asio::io_service& io_service)
    :
      m_socket(io_service, udp::endpoint(udp::v4(), 1032)) // bind
  {
    start_receive();
  }

  ~udp_server() {
    // http://stackoverflow.com/questions/15027268/how-to-close-boost-asio-server-socket-with-all-client-sockets-connected
    //m_socket.shutdown();
    m_socket.close();
  }

private:
  void start_receive() {
    shared_ptr<vector<char> > pVector(new vector<char>(1024, 0));
    m_socket.async_receive_from
        (
        boost::asio::buffer(&(*pVector)[0], pVector->size()), m_remoteEndpoint,
        boost::bind(&udp_server::handle_receive, this, pVector,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive(
      boost::shared_ptr<vector<char> > pBuffer
      , const boost::system::error_code& error
      , std::size_t bytes_transferred) {
    if (!error || error == boost::asio::error::message_size) {
      // process request

      // make response
      boost::shared_ptr<std::string> message(new std::string());

      m_socket.async_send_to  // async_send not compiled
          (boost::asio::buffer(*message), m_remoteEndpoint,
          boost::bind(&udp_server::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

      start_receive();
    }
  }
  void handle_send(
      boost::shared_ptr<std::string> /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/) { }

  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
};

void serverThreadUdpFunc( boost::asio::io_service& io_service ) {
  udp_server server(io_service);
  io_service.run();  // blocked if work loaded?
}

TEST(Parallel, Udp) {
  // http://stackoverflow.com/questions/4702512/stopping-threaded-server-loop-using-boostasio
  // http://stackoverflow.com/questions/15027268/how-to-close-boost-asio-server-socket-with-all-client-sockets-connected
  boost::asio::io_service io_service;
  // Create server thread that will start accepting connections.
  boost::thread server_thread( serverThreadUdpFunc, boost::ref( io_service ) );

  // Sleep for 10 seconds, then shutdown the server.
  std::cout << "Stopping service in 10 seconds..." << std::endl;
  boost::this_thread::sleep( boost::posix_time::seconds( 3 ) );
  std::cout << "Stopping service now!" << std::endl;

  // Stopping the io_service is a non-blocking call.  The threads that are
  // blocked on io_service::run() will try to return as soon as possible, but
  // they may still be in the middle of a handler.  Thus, perform a join on
  // the server thread to guarantee a block occurs.
  io_service.stop();

  std::cout << "Waiting on server thread..." << std::endl;
  server_thread.join();
  std::cout << "Done waiting on server thread." << std::endl;
}
