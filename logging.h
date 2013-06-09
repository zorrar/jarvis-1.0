#include<sqlite3.h>
#include<string>

using namespace std;

//Erstellung der Datenbank Datei
#define DATABSE_FILE "Jarvis_db.sql"

//Tabellen erstellen
void CreateTable(sqlite3 *sq3DataBase, string sTableName)
{
	string sMessageSQL;
	sMessageSQL = "CREATE TABLE " + sTableName + " (id integer primary key, Date text, SenderUser text, SenderNick text, ReceiverUser text, ReceiverNick text, Command text, Message text)";
	sqlite3_exec(sq3DataBase, sMessageSQL.c_str(), NULL, NULL, NULL);
}

//Eintrag in die Tabelle einfügen
void InsertData(sqlite3 *sq3DataBase, 
		string sTableName, 
		string sDate, 
		string sSenderUser, 
		string sSenderNick, 
		string sReceiverUser, 
		string sReceiverNick, 
		string sCommand, 
		string sMessage)
{
	string sMessageSQL;
	sMessageSQL = "INSERT INTO " + sTableName + " (Date, SenderUser, SenderNick, ReceiverUser, ReceiverNick, Command, Message) values ('"+sDate+"' ,'"+sSenderUser+"' ,'"+sSenderNick+"' ,'"+sReceiverUser+"' ,'"+sReceiverNick+"' ,'"+sCommand+"' ,'"+sMessage+"');";
	sqlite3_exec(sq3DataBase, sMessageSQL.c_str(), NULL, NULL, NULL);
}
