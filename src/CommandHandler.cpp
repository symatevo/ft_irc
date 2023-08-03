#include "../inc/CommandHandler.hpp"
CommandHandler::CommandHandler(Server *server) : _server(server)
{
    _cmds["JOIN"] = new JoinCommand(_server);
    _cmds["KICK"] = new KickCommand(_server);
    _cmds["MODE"] = new ModeCommand(_server);
    _cmds["NICK"] = new NickCommand(_server, false);
    _cmds["NOTICE"] = new NoticeCommand(_server);
    _cmds["PART"] = new PartCommand(_server);
    _cmds["PASS"] = new PassCommand(_server, false);
    _cmds["PING"] = new PingCommand(_server);
    _cmds["PONG"] = new PongCommand(_server);
    _cmds["PRIVMSG"] = new PrivMsgCommand(_server);
    _cmds["QUIT"] = new QuitCommand(_server, false);
    _cmds["USER"] = new UserCommand(_server, false);

}        
        
CommandHandler::~CommandHandler()
{
    for(std::map<std::string, Command*>::iterator it = _cmds.begin(); it != _cmds.end(); it++)
        delete it->second;
}

std::string CommandHandler::trim(const std::string& str)
{
    std::string WHITESPACE = " \n\r\t\f\v";
    std::string result = "";

    size_t  start = str.find_first_not_of(WHITESPACE);
    if (start != std::string::npos)
        result = str.substr(start);

    size_t  end = result.find_last_not_of(WHITESPACE);
    if (end != std::string::npos)
        result = result.substr(0, end + 1);

    return result;
}

void CommandHandler::invoke(Client *client, const std::string& message)
{
    std::stringstream ssMessage(message);
	std::string syntax;

    while(std::getline(ssMessage, syntax))
    {
        syntax = trim(syntax);
        std::string name = syntax.substr(0, syntax.find(' '));

        try
        {
            Command *command = _cmds.at(name);
            std::vector<std::string> arguments;
            std::string buffer;
            std::stringstream ss(syntax.substr(name.length(), syntax.length()));

            while (ss >> buffer)
            {
                arguments.push_back(buffer);
            }
            if (!client->isRegistered() && command->authRequired())
            {
                client->reply(ERR_NOTREGISTERED(client->GetNickname()));
                return;
            }
            command->exec(client, arguments);
        }
        catch(const std::exception& e)
        {
            client->reply(ERR_UNKNOWNCOMMAND(client->GetNickname(), name));
        }
        
    }
}