#include "../inc/Commands.hpp"

QuitCommand::QuitCommand(Server *server, bool authRequired) : Command(server, authRequired) {}
QuitCommand::~QuitCommand() {}

void QuitCommand::exec(Client *client, std::vector<std::string> args)
{
	std::string reason = args.empty() ? "Leaving:(" : args.at(0);
	reason = reason.at(0) == ':' ? reason.substr(1) : reason;

    client->reply(RPL_QUIT(client->GetPrefix(), reason));
}