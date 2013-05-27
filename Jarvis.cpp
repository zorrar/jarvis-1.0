#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<time.h>
#include<stdio.h>

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

//Bot Settings
const unsigned int iMaxLine = 1024;
char cHost[] = "localhost";//"PA.EnterTheGame.Com";
int iPort = 6667;
char sBotName[] = "Jarvis MK0";
char sUserName[] = "Jarvis";
char sChannelName[] = "ircbottesting";

//Globale Variablen
#ifdef WIN32
SOCKET sockfd;
#else
int sockfd;
#endif

//Settings Laden
void LoadData()
{

}

//Settings Anzeigen
void ShowData()
{
	printf("\r\n");
	printf("Welcome and thank you for using Jarvis the IRCBot.\r\n");
	printf("The current Bot settings are as followed:\r\n");
	printf("\r\n");
	printf("SERVER: %s \r\n", cHost);
	printf("PORT: %i \r\n", iPort);
	printf("CHANNEL NAME: %s \r\n", sChannelName);
	printf("BOT NAME: %s \r\n", sBotName);
	printf("USER NAME: %s \r\n", sUserName);
	printf("\r\n");
}

//Check for yes or no answers
struct YesNoCheck
{

	bool YesCheck(char cAnswer[4])
	{
		if(	cAnswer[0] == 'y' && cAnswer[1] == 0 ||
			cAnswer[0] == 'Y' && cAnswer[1] == 0 ||
			cAnswer[0] == 'y' && cAnswer[1] == 'e' && cAnswer[2] == 's' 
			&& cAnswer[3] == 0 ||
			cAnswer[0] == 'Y' && cAnswer[1] == 'e' && cAnswer[2] == 's' 
			&& cAnswer[3] == 0 ||
			cAnswer[0] == 'Y' && cAnswer[1] == 'E' && cAnswer[2] == 'S' 
			&& cAnswer[3] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool NoCheck(char cAnswer[4])
	{
		if(	cAnswer[0] == 'n' && cAnswer[1] == 0 ||
			cAnswer[0] == 'N' && cAnswer[1] == 0 ||
			cAnswer[0] == 'n' && cAnswer[1] == 'o' && cAnswer[2] == 0 ||
			cAnswer[0] == 'N' && cAnswer[1] == 'o' && cAnswer[2] == 0 ||
			cAnswer[0] == 'N' && cAnswer[1] == 'O' && cAnswer[2] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

//Settings einstellen
void SetData()
{
	char cAnswer[4];
	bool bLoop = true;

	printf("Would you like to change the current settings?\r\n");
	
	
	for(; bLoop == true;)
	{
		printf("(Y)es / (N)o?\r\n");
		scanf("%s", cAnswer);
		fflush(stdin);

		if(YesNoCheck().YesCheck(cAnswer))
		{
			bLoop = false;
			fflush(stdin);
			for(bool bLoop2 = true; bLoop2 == true;)
			{
				printf("\r\n");
				char cAnswerLoop2[4];

				printf("Edit settings\r\n");
				printf("SERVER: "); 		scanf("%s", cHost);fflush(stdin);
				printf("PORT: "); 		scanf("%i", &iPort);fflush(stdin);
				printf("CHANNEL NAME: "); 	scanf("%s", sChannelName);fflush(stdin);
				printf("BOT NAME: "); 		scanf("%s", sBotName);fflush(stdin);
				printf("USER NAME: "); 		scanf("%s", sUserName);fflush(stdin);
				printf("\r\n");
				printf("Is everything alright?\r\n");
				printf("(Y)es / (N)o?\r\n");
				scanf("%s", cAnswerLoop2);
				fflush(stdin);

				if(YesNoCheck().YesCheck(cAnswerLoop2))
				{
					bLoop2 = false;
					printf("\r\n");
					printf("Continue...\r\n");
					printf("\r\n");
				}
				else if(YesNoCheck().NoCheck(cAnswerLoop2))
				{
					bLoop2 = true;
					printf("\r\n");
					printf("Please correct the settings then.\r\n");
					printf("\r\n");
				}
				else
				{
					

					for(bool bLoop3 = true; bLoop3 == true;)
					{
						char cAnswerLoop3[4];
						printf("\r\n");
						printf("Please only answere with (Y)es or (N)o\r\n");
						printf("Is everything alright?\r\n");
						printf("(Y)es / (N)o?\r\n");
						scanf("%s", cAnswerLoop3);
						fflush(stdin);
						if(YesNoCheck().YesCheck(cAnswerLoop3))
						{
							bLoop3 = false;
							bLoop2 = false;
							printf("\r\n");
							printf("Continue...\r\n");
							printf("\r\n");
						}
						else if(YesNoCheck().NoCheck(cAnswerLoop3))
						{
							bLoop3 = false;
							bLoop2 = true;
							printf("\r\n");
							printf("Please correct the settings then.\r\n");
							printf("\r\n");
						}
						else
						{
							bLoop3 = true;
						}
					}
				}
			}
		}
		else if(YesNoCheck().NoCheck(cAnswer))
		{
			bLoop = false;
			printf("\r\n");
			printf("Continue...\r\n");
			printf("\r\n");
		}
		else
		{
			bLoop = true;
			printf("\r\n");
			printf("Please only answere with (Y)es or (N)o\r\n");
		}
	}
}

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
	printf("IRC connecting... \r\n");

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

	printf("IRC connected \r\n");
}

void s2u(const char *msg)
{
	send(sockfd, msg, strlen(msg), 0);
}

//Channel betretten
void ChannelConnect()
{
	string buffer;
	string sChannel;
	string sName;

	printf("Channel entering...\r\n");
	
	sChannel = sChannelName;
	sName = sBotName;

	buffer = "JOIN #" + sChannel;
	s2u(buffer.c_str());
	s2u("\r\n");
	
	

	buffer = "NOTICE #" + sChannel + " :THE BOT " + sName + " HAS JOINED THE CHANNEL\r\n";
	s2u(buffer.c_str());

	buffer = "PRIVMSG #" + sChannel + " :Hello I am " + sName + " a Bot\r\n";
	s2u(buffer.c_str());

	//s2u("NOTICE #ircbottesting :THE BOT JarvisMK1 HAS JOINED THE CHANNEL!\r\n");
	//s2u("PRIVMSG #ircbottesting :Hello I am a Bot in testing\r\n");
	
	printf("Channel entered\r\n\r\n");
}

//IRC Identifizieren
void IRC_Identify()
{
	printf("IRC identifing...\r\n");
	

	string buffer;
	string sNick;
	string sUser;

	sNick = sBotName;
	sUser = sUserName;

	buffer = "NICK " + sNick + "\r\n";	
	s2u(buffer.c_str());	
	
	buffer = "USER " + sUser + " 0 * :" + sUser + "\r\n";
	s2u(buffer.c_str());

	//s2u("NICK " + sBotName.c_str() + "\r\n");
	//s2u("USER %s 0 * :%s\r\n", sUserName, sUserName);
	
	//s2u("LOCALHOST");
	s2u("PRIVMSG NickServ REGISTER\r\n");
	s2u("PRIVMSG NickServ IDENTIFY\r\n");	
	
	//s2u(sBotName.c_str());
	//printf("Waiting for 5 seconds to let the bot connect to the server\r\n");
	//sleep(5);
	//printf("Continue...\r\n");

	//s2u("SERVER ircnet.eversible.com");
	
	//s2u("PRIVMSG NickServ IDENTIFY JarvisPW123\r\n");
	//ChannelConnect();

	printf("IRC identifed\r\n");
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
		printf("PONG\r\n");
		s2u(pong.c_str());
	}
}

//Messages Incoming
void GetMSG(const string &buffer)
{
	size_t MSG = buffer.find("#");//"BLUB\r\n\r\n\r\n";
	//buffer.find("PRIVMSG");
	if(MSG != string::npos)
	{
		//printf("%lu\r\n", MSG);
		int Value = MSG;
		//string sMSG("%s",buffer);// buffer.substr(MSG+16) + "\r\n");

		time_t timer;
		//asctime(localtime(timer));
		time(&timer);
		struct tm * time2;
		time2 = localtime(&timer);
		//string stime = asctime(time);
		//for(int i; i < ctime.lengue; i++)
		//{
			string stime = asctime(time2);
			stime.erase(stime.length()-1);
			printf("%s: ", stime.c_str());
		//}
		
		for(int i = MSG; i < buffer.length(); i++)
		{
			printf("%c", buffer[i]);
		}
		//printf("\r\n");
	}
	//printf("%s", MSG.c_str());
}

//CHAT Loggen
void LogChat()
{
	//s2u("LOG");
}

//BOT Funktionen
void BotFunctions(string buffer)
{
	s2u("PRIVMSG Zorrar :Hello");
}

void irc_parse(string buffer)
{
	if(buffer.find("\r\n") == buffer.length()-2)
	{
		buffer.erase(buffer.length()-2);
		//printf("BUFFERERASE! BUFFER: %s - END\r\n", buffer.c_str());
	}
	IRCSCT(buffer);
	//BotFunctions(buffer);
}

//Programm Start
int main()
{
	//Loads the Settings from a external confic file
	LoadData();

	//Shows the current Settings
	ShowData();

	//Sets the configs per user input
	SetData();

	//Verbindung herstellen
	IRC_Connect();
	
	//Beim Server identifizieren
	IRC_Identify();

	//Channel betretten
	ChannelConnect();
	
	LogChat();

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
		GetMSG(buffer);
	}
	IRC_Disconnect();
	exit(1);
}
