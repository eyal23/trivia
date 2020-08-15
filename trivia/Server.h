#pragma once

class Server
{
public:
    static Server& getInstance()
    {
        static Server instance;
        return instance;
    }

    void run();

    Server(Server const&) = delete;
    void operator=(Server const&) = delete;

private:
    Server() {}
};
