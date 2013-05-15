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
const int iPort = 6668;
const char *cHost = "irc.atw-inter.net";

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

//IRC Identifizieren
void IRC_Identify()
{
	s2u("NICK JarvisBot\r\n");

	s2u("LOCALHOST 192.168.1.1");

	s2u("USER JarvisBot 0 0:JarvisBot\r\n");

	s2u("PASS JarvisPW123");

	s2u("PRIVMSG NickServ register JarvisPW123\r\n");

	s2u("PRIVMSG NickServ IDENTIFY JarvisPW123\r\n");

	s2u("JOIN #ircbottesting\r\n");

	s2u("PRIVMSG #ircbottesting : Hello\r\n");
}

//Nachricht senden
void SendMsg()
{

}

//IRC Still Connected Test -> IRCSCT
//IRC-Server Verbindungs Test
void IRCSCT()
{

}

//Nachrichten Empfangen
void GetMsg()
{

}

//Channel betrette
void ChannelConnect()
{

}

//BOT Funktionen
void BotFunctions()
{

}

void irc_parse(string buffer)
{
	if(buffer.find("\r\n") == buffer.length()-2)
	{
		buffer.erase(buffer.length()-2);
	}
	//ping_parse(buffer);
	//bot_functions(buffer);
}

//Programm Start
int main()
{
	IRC_Connect();
	printf("IRC Connected \n");
	IRC_Identify();
	printf("IRC Idnetify\n");

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
