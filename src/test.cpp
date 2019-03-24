#include<iostream>
#include <Poco/Util/Util.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>
#include <hotel.h>

class HelloRequestHandler:public Poco::Net::HTTPRequestHandler{
    void handleRequest(Poco::Net::HTTPServerRequest &request,
            Poco::Net::HTTPServerResponse &response)override{
        Poco::Util::Application &app=Poco::Util::Application::instance();

        app.logger().information("Request from %s",request.clientAddress()
                .toString());

        response.setChunkedTransferEncoding(true);
        response.setContentType("text/html");

        response.send()<<"<html>"
            <<"<head><title>Hello</title></head>"
            <<"<body><h1>Hello from the POCO web Server</h1></body>"
            <<"</html>";
    }
};


class Trolol:public Poco::Net::HTTPRequestHandler{
    void handleRequest(Poco::Net::HTTPServerRequest &request,
            Poco::Net::HTTPServerResponse &response)override{
    
        response.send()<<"<html>"
            <<"<head><title>TROLLING</title></head>"
            <<"<body><h1>TROLLING IS GANGSTER</h1></body>"
            <<"</html>";
    }
};


class HelloRequestHandlerFactory:public Poco::Net::HTTPRequestHandlerFactory{
    Poco::Net::HTTPRequestHandler *createRequestHandler
         (const Poco::Net::HTTPServerRequest &request)override{
        
        if(request.getURI()=="/hello"){
            return new HelloRequestHandler();
        }
        return new Trolol();
    }
};


class WebServerApp:public Poco::Util::ServerApplication{
    void initialize(Poco::Util::Application &self){
        loadConfiguration();
        ServerApplication::initialize(self);
    }


    int main(const std::vector<std::string> &cmds){
        try{
            Poco::UInt16 port=static_cast<Poco::UInt16>(
                    config().getUInt("port",9986));

            Poco::Net::HTTPServer srv(new HelloRequestHandlerFactory,port);
            srv.start();
            logger().information("HTTP Server started on port %hu",port);
            waitForTerminationRequest();
            logger().information("Stopping HTTP Server...");
            srv.stop();

            return EXIT_OK;
        }catch(Poco::Exception &ex){
            std::cout<<ex.message()<<std::endl;
        }
        return EXIT_FAILURE;
    }

};


int main(int argc, char **argv){
    std::cout<<"POCO TEST"<<std::endl;
    WebServerApp app;
    return app.run(argc,argv);  
}
