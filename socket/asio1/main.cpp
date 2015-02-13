#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio ;

static const int PORT_NO = 8080;

boost::asio::io_service     io_;

void accept_handler(const boost::system::error_code& error)
{
    if (!error)
    {
        // Accept succeeded.
    }
}


ip::tcp::iostream               buf;
//    boost::asio::streambuf      buf;
ip::tcp::socket             socket1(io_);
ip::tcp::acceptor           accept1( io_, ip::tcp::endpoint(ip::tcp::v4(), PORT_NO ) );

void do_accept(){



    //*
//    accept1.async_accept( socket1, accept_handler );

    accept1.async_accept( *buf.rdbuf(), [](boost::system::error_code ec){

        cout << "async_accept" << std::endl;
        if (!accept1.is_open()) {
            return;
        }

        if(!ec) {
            std::string temp;

            cout << "accept!!" << std::endl;

            while (true) {
                buf >> temp;
                if (temp == "quit") {
                    buf << ">>bye" << std::endl;
                    break;
                }
                buf << ">>" << temp << std::endl;
            }
        }

        do_accept();
    } );
    //*/

    /*
    accept.async_accept( socket, [&buf,&socket](const boost::system::error_code &ec){

        async_read_until( socket, buf, '\n', [&buf](const boost::system::error_code &error, std::size_t size){
            std::string temp;
            std::iostream is(&buf);

            is >> temp;
            if (temp == "quit") {
                is << ">>bye" << std::endl;
//                break;
            }
            is << ">>" << temp << std::endl;

        } ) ;

//        do_accept();

    } );

*/

}

int main() {

//    boost::asio::io_service::work w( io_ );
    do_accept();

    io_.run();

    return 0;
}



/*
    boost::asio::io_service     io;
    ip::tcp::iostream           buf;
    ip::tcp::acceptor           accept( io, ip::tcp::endpoint(ip::tcp::v4(), PORT_NO ));

    accept.accept( *buf.rdbuf() );

    std::string temp;

    while(true) {
        buf >> temp;
        if( temp == "quit" ) {
            buf << ">>bye" << std::endl;
            break;
        }
        buf << ">>" << temp << std::endl;
    }
    return 0;
*/

