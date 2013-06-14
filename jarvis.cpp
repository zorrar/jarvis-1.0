#include"jarvislib.h"
//Programm Start
int main()
{
	//Loads the Settings from a external confic file
	LoadData();

	//Shows the current Settings
	ShowData();

	//Sets the configs per user input
	SetData();

	//Save Configs
	SaveData();

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
