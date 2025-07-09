#include "third_library/oatpp/src/oatpp/web/server/HttpConnectionHandler.hpp"
#include "third_library/oatpp/src/oatpp/network/Server.hpp"
#include "third_library/oatpp/src/oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "third_library/oatpp/src/oatpp/web/server/HttpRouter.hpp"
#include "third_library/oatpp/src/oatpp/json/ObjectMapper.hpp"
#include "oatpp_data_controller.hpp"

void run() {

    auto router = oatpp::web::server::HttpRouter::createShared();
    auto object_mapper = std::make_shared<oatpp::json::ObjectMapper>();

    auto controller = std::make_shared<Controller>(object_mapper);
    
    router->addController(controller);

    auto conn_handler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    auto address = oatpp::network::Address({"localhost", 8080, oatpp::network::Address::IP_4});
    auto conn_provider = oatpp::network::tcp::server::ConnectionProvider::createShared(address);

    oatpp::network::Server server(conn_provider, conn_handler);

    OATPP_LOGi("MyApp", "File Management API Server running on " + conn_provider->getProperty("host").std_str() + ":" + conn_provider->getProperty("port").std_str());
    OATPP_LOGi("POST", "http://" + conn_provider->getProperty("host").std_str() + ":" + conn_provider->getProperty("port").std_str() + "/api/files - Insert file");
    OATPP_LOGi("GET1", "http://" + conn_provider->getProperty("host").std_str() + ":" + conn_provider->getProperty("port").std_str() + "/api/files - Query all files");
    OATPP_LOGi("GET2", "http://" + conn_provider->getProperty("host").std_str() + ":" + conn_provider->getProperty("port").std_str() + "/api/files/user/{userId} - Query files by user");
    OATPP_LOGi("GET3", "http://" + conn_provider->getProperty("host").std_str() + ":" + conn_provider->getProperty("port").std_str() + "/api/files/name/{fileName} - Get file by name");
    OATPP_LOGi("PUT", "http://" + conn_provider->getProperty("host").std_str() + ":" + conn_provider->getProperty("port").std_str() + "/api/files/{fileName} - Update file");
    OATPP_LOGi("DELETE", "http://" + conn_provider->getProperty("host").std_str() + ":" + conn_provider->getProperty("port").std_str() + "/api/files/{fileName} - Delete file");

    server.run();
}

int main() {

    oatpp::Environment::init();
    run();
    oatpp::Environment::destroy();

    return 0;
}
