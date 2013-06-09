#include<sqlite3.h>
#include<string>

using namespace std;

//Erstellung der Datenbank Datei
#define DATABSE_FILE "Jarvis_db.sql"

//Tabellen erstellen
void CreateTable(sqlite3 *sq3DataBase, string sTableName)
{
	//Create Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "CREATE TABLE " + sTableName + " (id integer primary key, Date text, SenderUser text, SenderNick text, ReceiverUser text, ReceiverNick text, Command text, Message text)";
	
	//Query Execution Interface
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
	//Create Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "INSERT INTO " + sTableName + " (Date, SenderUser, SenderNick, ReceiverUser, ReceiverNick, Command, Message) values ('"+sDate+"' ,'"+sSenderUser+"' ,'"+sSenderNick+"' ,'"+sReceiverUser+"' ,'"+sReceiverNick+"' ,'"+sCommand+"' ,'"+sMessage+"');";

	//Query Execution Interface
	sqlite3_exec(sq3DataBase, sMessageSQL.c_str(), NULL, NULL, NULL);
}

//Ausgabe aller Datensätze
void PrintData(sqlite3 *sq3DataBase, string sTableName)
{
	//initialize SQL Statement Object
	sqlite3_stmt *sql3Statement;
	
	//Create Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "SELECT * FROM " + sTableName;

	//Umwandelung des SQL Querys in byte-code
	sqlite3_prepare(sq3DataBase, sMessageSQL.c_str(), -1, &sql3Statement, NULL);

	//Ausgabe aller Datensätze
	while(sqlite3_step(sql3Statement) != SQLITE_DONE)
	{
		//Ausgabe der Datenfelder als Text
		printf("%s %s %s %s %s %s %s\r\n", sqlite3_column_text(sql3Statement, 1), sqlite3_column_text(sql3Statement, 2), sqlite3_column_text(sql3Statement, 3), sqlite3_column_text(sql3Statement, 4), sqlite3_column_text(sql3Statement, 5), sqlite3_column_text(sql3Statement, 6), sqlite3_column_text(sql3Statement, 7));
	}

	//Statement löschen
	sqlite3_finalize(sql3Statement);
}
