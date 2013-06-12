#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<time.h>
#include<stdio.h>
#include"logging.h"

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
char cHost[256] = "localhost";//"PA.EnterTheGame.Com";
int iPort = 6667;
char cBotName[256] = "JarvisMK10";
char cUserName[256] = "Stark";
char cChannelName[256] = "ircbottesting";


bool bLogChat = true;
string sTableName = "Log";
sqlite3 *db_handler;



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
	printf("CHANNEL NAME: %s \r\n", cChannelName);
	printf("BOT NAME: %s \r\n", cBotName);
	printf("USER NAME: %s \r\n", cUserName);
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
				printf("CHANNEL NAME: "); 	scanf("%s", cChannelName);fflush(stdin);
				printf("BOT NAME: "); 		scanf("%s", cBotName);fflush(stdin);
				printf("USER NAME: "); 		scanf("%s", cUserName);fflush(stdin);
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

	printf("\r\n%i\r\n", sockfd);
	if(connect(sockfd, (sockaddr*) &sin, sizeof(sin)) == -1)
	{
		printf("\r\n%i\r\n", sockfd);
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
	
	sChannel = cChannelName;
	sName = cBotName;

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

	sNick = cBotName;
	sUser = cUserName;

	buffer = "NICK " + sNick + "\r\n";	
	s2u(buffer.c_str());	
	
	buffer = "USER " + sUser + " 0 * :" + sUser + "\r\n";
	s2u(buffer.c_str());
	
	//s2u("LOCALHOST");
	s2u("PRIVMSG NickServ REGISTER\r\n");
	s2u("PRIVMSG NickServ IDENTIFY\r\n");	
	

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

//Message Infomation
struct InfoMSG
{
	string sDate;
	string sCommand;
	string sNickSender;
	string sNickUser;
	string sMessage;
};

//Zeitausgabe ausgabe
string DateOutput()
{
	InfoMSG Info;

	time_t timer;
	time(&timer);
	struct tm * time2;
	time2 = localtime(&timer);

	string stime = asctime(time2);
	stime.erase(stime.length()-1);

	Info.sDate = stime.c_str();
	//printf("%s: ", stime.c_str());

	return stime.c_str();
}

//Filter Messages for Keywards
void Search(string sKeyword, const string Message)
{
	
	size_t MSG = Message.find(sKeyword.c_str());
	
	if(MSG != string::npos)
	{
		int Value = MSG;
		string sDate;
		sDate = DateOutput();

		string sSenderNick;
		int iSenderNickStringPos = Message.find(":", 0)+1;
		int iSenderNickStringEnd = Message.find("!", 2);
		int iSenderNickLength = iSenderNickStringEnd - iSenderNickStringPos;
		for(int i = 0; i < iSenderNickLength; i++)
		{
			sSenderNick = sSenderNick + Message[iSenderNickStringPos + i];	
		}

		string sSenderUser;
		int iSenderUserStringPos = Message.find("!", 0)+1;
		int iSenderUserStringEnd = Message.find("@", 2);
		int iSenderUserLength = iSenderUserStringEnd - iSenderUserStringPos;
		for(int i = 0; i < iSenderUserLength; i++)
		{
			sSenderUser = sSenderUser + Message[iSenderUserStringPos + i];
		}

		string sCommand;
		sCommand = sKeyword;

		int iNickStringPos = MSG + (int)sKeyword.length()+1;
		int iNickStringEnd = Message.find(":", 2);
		int iNickLength = iNickStringEnd - iNickStringPos;
		string sReceiverNick;
		for(int i = 0; i < iNickLength; i++)
		{
			sReceiverNick = sReceiverNick + Message[iNickStringPos + i];	
		}
		

		string sMessage;
		for(int i = 0; i < Message.length()-iNickStringEnd; i++)
		{
			sMessage = sMessage + Message[iNickStringEnd + i];	
		}

		
		printf("%s ", sDate.c_str());//OK
		
		printf("%s ", sSenderNick.c_str());//OK

		printf("%s ", sSenderUser.c_str());//OK
		
		printf("%s ", sCommand.c_str());//OK
		
		printf("%s ", sReceiverNick.c_str());//OK
		
		printf("%s ", sMessage.c_str());//OK
		
		if(bLogChat == true)
		{
			InsertData(	db_handler, 
					sTableName,
					DateOutput(),  
					sSenderNick.c_str(),
					sSenderUser.c_str(), 
					sCommand.c_str(), 
					sReceiverNick.c_str(), 
					sMessage.c_str());
		}
	}
}

//Messages Incoming
void GetMSG(const string &buffer)
{
	string sKeyword;
	
	InfoMSG Info;
	string sDate = Info.sDate;

	sKeyword = "JOIN";
	Search(sKeyword, buffer);
	
	sKeyword = "QUIT";
	Search(sKeyword, buffer);

	sKeyword = "PRIVMSG";
	Search(sKeyword, buffer);

	sKeyword = "NOTICE";
	Search(sKeyword, buffer);
}

//Prints the ChatLog
void ShowLog()
{
	printf("LOG: \r\n");
	PrintData(db_handler, sTableName);
	printf("END LOG \r\n\r\n");
}

//Frag ob der Chat geloggt werden soll
void AskLogging()
{
	char sAnswer[4];
	for(bool bLogLoop = true; bLogLoop == true;)
	{
		printf("Do you want to log the Channel?\r\n");
		printf("(Y)es / (N)o?\r\n");
		scanf("%s", sAnswer);
		fflush(stdin);
		if(YesNoCheck().YesCheck(sAnswer))
		{
			bLogLoop = false;
			bLogChat = true;
			printf("The Chat is now being logged\r\n");
		}
		else if(YesNoCheck().NoCheck(sAnswer))
		{
			bLogLoop = false;
			bLogChat = false;
			printf("The Chat is not being logged\r\n");
		}
		else
		{
			bLogLoop = true;
			bLogChat = false;
			printf("Please only answere with (Y)es or (N)o\r\n");
		}
	}
}

//CHAT Loggen
void StartChatLogging()
{
	if(bLogChat == true)
	{
		string buffer;
		string sChannel;
		sChannel = cChannelName;
		buffer = "Start logging Channel: " + sChannel;

		InsertData(	db_handler,
				sTableName,
				DateOutput(),
				cBotName,
				cUserName,
				"-",
				"-",
				buffer);
	}
}

//BOT Funktionen
void BotFunctions(string buffer)
{
	//s2u("PRIVMSG Zorrar :Hello");
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

	//Ask the user if he wants to log the channel
	AskLogging();

	if(bLogChat == true)
	{
		sqlite3_open(DATABSE_FILE, &db_handler);
		CreateTable(db_handler, sTableName);
	}

	//Verbindung herstellen
	IRC_Connect();
	
	//Beim Server identifizieren
	IRC_Identify();

	//Channel betretten
	ChannelConnect();
	
	//Channel Loggen
	StartChatLogging();

	if(bLogChat == true)
	{
		//Log ausgeben
		ShowLog();
	}
	
	for(;;)
	{
	
		char buffer[iMaxLine+1] = {0};
		if(recv(sockfd, buffer, iMaxLine*sizeof(char), 0)<0)
		{
			printf("BUFFER: %c blub\r\n", buffer[0]);
			perror("recv()\r\n");
			IRC_Disconnect();
			exit(1);
		}
		//cout << buffer;
		irc_parse(buffer);
		GetMSG(buffer);
	}
	IRC_Disconnect();
	exit(1);
}
