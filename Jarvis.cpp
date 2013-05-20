#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cstring>

#ifdef WIN32
#include<winsock2.h>
#else
#include<sys/socket.h>
//#include<sys/trypes.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#endif

//Namespace
using namespace std;

//Konstanten
const unsigned int iMaxLine = 1024;
const int iPort = 6667;
const char *cHost = "PA.EnterTheGame.Com";

//Globale Variablen
#ifdef WIN32
SOCKET sockfd;
#else
int sockfd;
#endif

//IRC Trennen
void IRC_Disconnect()
{
	printf("Disconnect...");
	#ifdef WIN32
	{
		//Windows-SOcket freigeben
		closesocket(sockfd);
		WSACleanup();
		printf("Disconnected");
		exit(1);
	}
	#else
	{
		close(sockfd);
		printf("Disconnected");
		exit(1);
	}
	#endif
}

//IRC Verbinden
void IRC_Connect()
{


	//Windows-Socket initialisieren
	#ifdef WIN32
	WSADATA wsa:
	if(WSAStartup(MAKEWORLD(2,0),&wsa != 0)
	{
		exit(1);
	}
	#endif

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(static_cast<int>(sockfd) < 0)
	{
		perror("socket()");
		IRC_Disconnect();
		exit(1);
	}
	
	hostent *hp = gethostbyname(cHost);
	if(!hp)
	{
		printf("gethostbyname()");
		IRC_Disconnect();
		exit(1);
	}

	sockaddr_in sin;
	memset((char*)&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	memcpy((char*)&sin.sin_addr,hp->h_addr, hp->h_length);
	sin.sin_port = htons(iPort);
	memset(&(sin.sin_zero), 0, 8*sizeof(char));

	if(connect(sockfd, (sockaddr*) &sin, sizeof(sin)) == -1)
	{
		perror("connect()");
		IRC_Disconnect();
		exit(1);
	}
}

void s2u(const char *msg)
{
	send(sockfd, msg, strlen(msg), 0);
}

//Channel betretten
void ChannelConnect()
{
	//sleep(3);
	printf("Channel Entering...\r\n");
	s2u("JOIN #ircbottesting\r\n");
	s2u("NOTICE #ircbottesting THE_BOT_JarvisMK1_HAS_JOINED_THE_CHANNEL!\r\n");
	s2u("PRIVMSG Zorrar Hello_here_I_am\r\n");
	s2u("PRIVMSG #ircbottesting Hello_I_am_a_Bot_in_testing\r\n");
	printf("Channel Entered\r\n");
}

//IRC Identifizieren
void IRC_Identify()
{
	s2u("NICK JarvisMK1\r\n");
	s2u("USER Jarvis 0 * :JarvisMK1Bot\r\n");
	//s2u("LOCALHOST");
	s2u("PRIVMSG NickServ REGISTER\r\n");
	s2u("PRIVMSG NickServ IDENTIFY\r\n");	
	
	//printf("Waiting for 5 seconds to let the bot connect to the server\r\n");
	//sleep(5);
	//printf("Continue...\r\n");

	//s2u("SERVER ircnet.eversible.com");
	
	//s2u("PRIVMSG NickServ IDENTIFY JarvisPW123\r\n");
	//ChannelConnect();
}

//IRC Still Connected Test -> IRCSCT
//IRC-Server Verbindungs Test
void IRCSCT(const string &buffer)
{
	size_t pingPos = buffer.find("PING");
	if(pingPos != string::npos)
	{
		string pong("PONG"+buffer.substr(pingPos+4)+"\r\n");
		//cout << pong\r\n;
		printf("pong\r\n");
		s2u(pong.c_str());
	}
}


//BOT Funktionen
void BotFunctions(string buffer)
{
	s2u("PRIVMSG Zorrar Hello");
}

void irc_parse(string buffer)
{
	if(buffer.find("\r\n") == buffer.length()-2)
	{
		buffer.erase(buffer.length()-2);
	}
	IRCSCT(buffer);
	BotFunctions(buffer);
}

//Programm Start
int main()
{
	//Verbindung herstellen
	printf("IRC Connecting \n");	
	IRC_Connect();
	printf("IRC Connected \n");
	
	

	//Beim Server identifizieren
	printf("IRC Identify \n");
	IRC_Identify();
	printf("IRC Identifed \n");

	//char buffer2[iMaxLine+1] = {0};
	//irc_parse(buffer2);

	//Channel betretten
	ChannelConnect();
	
	for(;;)
	{
	
		char buffer[iMaxLine+1] = {0};
		if(recv(sockfd, buffer, iMaxLine*sizeof(char), 0)<0)
		{
			perror("recv()");
			IRC_Disconnect();
			exit(1);
		}
		cout << buffer;
		irc_parse(buffer);
		
	}
	IRC_Disconnect();
	exit(1);
}
