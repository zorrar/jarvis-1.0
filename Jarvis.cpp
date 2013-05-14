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
const int iPort =6667;
const char *cHost = "irc.insiderZ.DE";

//Globale Variablen
#ifdef WIN32
SOCKET sockfd;
#else
int sockfd;
#endif

//IRC Verbinden
void IRC_Connect()
{
	
}

//IRC Trennen
void IRC_Disconnect()
{
	
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

//Programm Start
int main()
{
	printf("Hello World \n");
}
