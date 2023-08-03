#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

class CommandHandler;
#include "Commands.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

class CommandHandler
{
private:
    Server *_server;
    std::map<std::string, Command *> _cmds;

public:
    CommandHandler(Server *server);
    ~CommandHandler();
    void invoke(Client *client, const std::string &msg);
    std::string trim(const std::string &str);
};

#endif