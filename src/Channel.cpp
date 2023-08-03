#include "../inc/Channel.hpp"
#include "../inc/Client.hpp"
#include "../utils.hpp"
#include <algorithm>

Channel::Channel(const std::string &name, const std::string &password, Client* admin )
{
    m_name = name;
    m_password = password;
    m_admin = admin; 
    m_noExt = false;
}

Channel::~Channel()
{
    //default destructor
}
 

//getters
std::string Channel::GetName() const
{
    return m_name;
}

std::string Channel::GetTopic() const
{
    return m_topic;
}

std::string Channel::GetPassword() const
{
    return m_password;    
}

int Channel::GetNumberOfClients() const
{
    // get current number of clients
    return m_clients.size();
}

int Channel::GetMaxClients() const
{
    //gett maximum size of clients
    return m_max_clients;
}

std::vector<std::string> Channel::GetNicknames()
{
    std::vector<std::string> nicknames;
    for (std::vector<Client*>::iterator it = m_clients.begin();
                    it != m_clients.end(); it++)
    {
        Client *client = it.operator*();
        nicknames.push_back((m_admin == client ? "@" : "") + (*it)->GetNickname());
    }
    return nicknames;
}

bool Channel::GetNoExt() const
{
    return m_noExt;
}

//setters
void Channel::SetName(const std::string &name)
{
    m_name = name;
}

void Channel::SetTopic(const std::string &topic)
{
    m_topic = topic;
}

void Channel::SetPassword(const std::string &key)
{
    m_password = key;
}

void Channel::SetMaxClients(const int max_clients)
{
    m_max_clients = max_clients;
}

// working with clinets
void Channel::AddClient(Client* client)
{
        //Adding client
        m_clients.push_back(client);
}

void Channel::RemoveClient(Client* client)
{
    //remove client
    std::vector<Client*>::iterator it = std::find(m_clients.begin(), m_clients.end(), client);
    if (it != m_clients.end())
    {
        m_clients.erase(it);
    }
    client->SetChannel(nullptr);

    if (m_clients.empty())
		return;

	if (m_admin == client)
    {
		m_admin = m_clients.begin().operator*();

		char message[100];
		sprintf(message, "%s is now admin of channel %s.", m_admin->GetNickname().c_str(), m_name.c_str());
		ft_log(message);
	}

}

void Channel::BroadcastMessage(const std::string& message)
{
    //not sure how this should be work
    //brodcast message that will be shown all users.
    for(std::vector<Client*>::iterator it = m_clients.begin();
        it != m_clients.end();
        it++)
        (*it)->write(message);
}

void Channel::BrodcastMessage(const std::string& message, Client *except )
{
    //brodcast message that will be shown for all users.
    for (std::vector<Client*>::iterator it = m_clients.begin();
                    it != m_clients.end(); it++)
        if (*it != except)
    (*it)->write(message);
}

void Channel::Kick(Client* admin, Client *client, std::string s_reason)
{
    BroadcastMessage(RPL_KICK(admin->GetPrefix(), m_name, client->GetNickname(), s_reason));
    RemoveClient(client);

    char message[100];
    sprintf(message, "%s kicked %s from channel %s.",
        admin->GetNickname().c_str(), client->GetNickname().c_str(), m_name.c_str());
    ft_log(message);
}

Client *Channel::getAdmin() const {
    return m_admin;
}

void Channel::SetNoExt(bool state) {
    m_noExt=state;
}