
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio ;

class Server : public boost::noncopyable
{
private:
     io_service&io_;
     ip::tcp::acceptor acceptor_;
     boost::asio::streambuf buf_;
     ip::tcp::socket socket_;
public:

    Server(io_service& io, const short port)
       : io_(io), acceptor_(io, ip::tcp::endpoint(ip::tcp::v4(), port)), socket_(io) {
         do_accept();
    }



    void do_accept() {
         acceptor_.async_accept(
             socket_,
               [this](const boost::system::error_code &e){
                   std::cout << "accept_ok" << std::endl;
                   do_read();
               } );
    }


    void do_read()
    {
         async_read_until( socket_, buf_, '\n', [this](const boost::system::error_code e, std::size_t length){

             std::iostream ios(&buf_);

             std::string tmp;
             ios >> tmp;


             if( tmp == "quit" ){
                 ios << ">>bye" <<std::endl;
                 async_write( socket_, buf_, std::bind(&Server::do_accept, this ));
                 socket_.close();

             } else {
                 ios << ">>" << tmp <<std::endl;
                 async_write( socket_, buf_, std::bind(&Server::do_read, this ));
             }

         });

     }



} ;
    


int main(int argc, char* argv[])
{
    boost::asio::io_service io;

    Server s( io,8080 );

    io.run();

    return 0;
}