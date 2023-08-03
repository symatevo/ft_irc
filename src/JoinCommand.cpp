#include "../inc/Commands.hpp"

JoinCommand::JoinCommand(Server *server) : Command(server) {}

JoinCommand::~JoinCommand() {}

void JoinCommand::exec(Client *client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->GetNickname(), "PASS"));
        return;
    }

    std::string channelName = args[0];
    std::string pass;
    pass = args.size() > 1 ? args[1] : "";
    Channel *channel = client->getChannel();

    // if (channel)
    // {
    //     client->reply(ERR_TOOMANYCHANNELS(client->GetNickname(), channelName));
    //     return;
    // }
    channel = _server->getChannel(channelName);
    if (!channel)
        channel = _server->createChannel(channelName, pass, client);

    if (channel->GetMaxClients() > 0 && channel->GetNumberOfClients() >= channel->GetMaxClients())
    {
        client->reply(ERR_CHANNELISFULL(client->GetNickname(), channelName));
        return;
    }

    if (channel->GetPassword() != pass)
    {
        client->reply(ERR_BADCHANNELKEY(client->GetNickname(), channelName));
        return;
    }

    client->JoinChanel(channel);
}

// missing getChannel from CLient