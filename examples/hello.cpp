#include <iostream>

#include "coros/async/thread_pool.h"
#include "coros/io/monitor.h"
#include "coros/network/server.h"

#include "coros_fcgi/app.h"
#include "coros_fcgi/handler.h"
#include "coros_fcgi/application/request.h"
#include "coros_fcgi/application/response.h"

class HelloHandler : public coros::fcgi::FcgiHandler {
    public:
        coros::base::AwaitableFuture process_request(coros::fcgi::Request& request,
                                                     coros::fcgi::Response& response) {
            for (auto& kv : request.variables) {
                std::cout << kv.first << ": " << kv.second << std::endl;
            }
            std::cout << "-------------------" << std::endl;
            co_await response.println("content-length: 18");
            co_await response.println("content-type: text/html\r\n");
            co_await response.print("welcome to fastcgi");
        }
};

void start_server(coros::base::Server& server) {
    try {
        server.start();
        std::getchar();
        server.shutdown();
    } catch (std::runtime_error error) {
        std::cerr << error.what() << std::endl;
    }
}

int main() {
    coros::base::ThreadPool thread_pool;
    coros::base::IoEventMonitor io_monitor(thread_pool);
    HelloHandler handler;
    coros::fcgi::FcgiApplication fcgi_app(thread_pool, handler);
    coros::base::Server hello_server(9000, fcgi_app, io_monitor, thread_pool);
    std::cout << "Starting FCGI Server..." << std::endl;
    start_server(hello_server);
    return 0;
}
