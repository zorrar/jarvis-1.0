#include<sqlite3.h>
#include<string>
#include<list>

using namespace std;

//Erstellung der Datenbank Datei
#define DATABSE_FILE "Jarvis_db.sql"

//Tabellen erstellen
void CreateTable(sqlite3 *sq3DataBase, string sTableName)
{
	//Initialisiere & deklariere Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "CREATE TABLE " + sTableName + " (id integer primary key, Date text, SenderNick text, SenderUser text, Command text, ReceiverNick text, Message text)";

	//Query ausführen
	sqlite3_exec(sq3DataBase, sMessageSQL.c_str(), NULL, NULL, NULL);
}

//Eintrag in die Tabelle einfügen
void InsertData(sqlite3 *sq3DataBase,
		string sTableName,
		string sDate,
		string sSenderNick,
		string sSenderUser,
		string sCommand,
		string sReceiverNick,
		string sMessage)
{
	//Initialisiere & deklariere Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "INSERT INTO " + sTableName + " (Date, SenderNick, SenderUser, Command, ReceiverNick, Message) values ('"+sDate+"' ,'"+sSenderNick+"' ,'"+sSenderUser+"' ,'"+sCommand+"' ,'"+sReceiverNick+"' ,'"+sMessage+"');";

	//Query ausführen
	sqlite3_exec(sq3DataBase, sMessageSQL.c_str(), NULL, NULL, NULL);
}

//Ausgabe aller Datensätze
string PrintData(sqlite3 *sq3DataBase, string sTableName, int iEntry)
{
	//Initialisiere Rückgabe String
	string sReturnMessage;

	//Initialisiere SQL Statement Objekt
	sqlite3_stmt *sql3Statement;

	//Initialisiere & deklariere Query SQL-Message
	char *cMessageSQL;
	string sMessageSQL;


	cMessageSQL = sqlite3_mprintf("SELECT * FROM %s WHERE id = '%i'", sTableName.c_str(), iEntry);


	//Umwandelung des SQL Querys in byte-code
	sqlite3_prepare(sq3DataBase, cMessageSQL, strlen(cMessageSQL), &sql3Statement, NULL);

	//Datensätze durchgehen
	while(sqlite3_step(sql3Statement) != SQLITE_DONE)
	{
		string sBuffer[6];

		for(int i = 0; i <6; i++)
		{
			sBuffer[i] = reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, i+1));
		}

		sReturnMessage = sBuffer[0] + " " + sBuffer[1] + " " + sBuffer[2] + " " + sBuffer[3] + " " + sBuffer[4] + " " + sBuffer[5];



	}
	//Statement löschen
	sqlite3_finalize(sql3Statement);

	//Sendet Die Logdaten als String zurück
	return sReturnMessage;
}


int GetNumberEntrys(sqlite3 *sq3DataBase, string sTableName)
{

	int iNumberEntrys = 0;

	//Initialisiere SQL Statement Objekt
	sqlite3_stmt *sql3Statement;

	//Initialisiere & deklariere Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "SELECT * FROM " + sTableName + " WHERE id = (SELECT MAX (id) FROM " + sTableName + ")";

	//printf("%s\r\n", sMessageSQL.c_str());

	//Umwandelung des SQL Querys in byte-code
	sqlite3_prepare(sq3DataBase, sMessageSQL.c_str(), -1, &sql3Statement, NULL);

	//Datensätze durchgehen
	while(sqlite3_step(sql3Statement) != SQLITE_DONE)
	{
		//Gets the Number of Entrys
		iNumberEntrys = sqlite3_column_int(sql3Statement, 0);
	}
	//Statement löschen
	sqlite3_finalize(sql3Statement);

	//printf("NUMBER: %i\r\n", iNumberEntrys);

	return iNumberEntrys;
}


//Ausgabe eines Spezifischen Datensatzes
string PrintSelectedData(sqlite3 *sq3DataBase, string sTableName)
{
	//Initialisiere Rückgabe String
	string sReturnMessage;

	//Initialisiere SQL Statement Objekt
	sqlite3_stmt *sql3Statement;

	//Initialisiere & deklariere Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "SELECT * FROM " + sTableName + " WHERE id = (SELECT MAX (id)-1 FROM " + sTableName + ")";
	//sMessageSQL = "SELECT * FROM " + sTableName;

	//Umwandelung des SQL Querys in byte-code
	sqlite3_prepare(sq3DataBase, sMessageSQL.c_str(), -1, &sql3Statement, NULL);

	//Datensätze durchgehen
	while(sqlite3_step(sql3Statement) != SQLITE_DONE)
	{

		string sBuffer[6];

		for(int i = 0; i <6; i++)
		{
			sBuffer[i] = reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, i+1));
		}

		sReturnMessage = sBuffer[0] + " " + sBuffer[1] + " " + sBuffer[2] + " " + sBuffer[3] + " " + sBuffer[4] + " " + sBuffer[5];

	}
	//Statement löschen
	sqlite3_finalize(sql3Statement);

	//Sendet Die Logdaten als String zurück
	return sReturnMessage;

}

//Ausgabe eines Spezifischen Datensatzes
string PrintSelectedData2(sqlite3 *sq3DataBase, string sTableName, int iNumber)
{
	//Initialisiere Rückgabe String
	string sReturnMessage;

	//Initialisiere SQL Statement Objekt
	sqlite3_stmt *sql3Statement;

	//Initialisiere & deklariere Query SQL-Message
	string sMessageSQL;
	sMessageSQL = "SELECT * FROM " + sTableName + " WHERE id = (SELECT " + (char)iNumber + " FROM " + sTableName + ")";
	//sMessageSQL = "SELECT * FROM " + sTableName;

	//Umwandelung des SQL Querys in byte-code
	sqlite3_prepare(sq3DataBase, sMessageSQL.c_str(), sMessageSQL.length(), &sql3Statement, NULL);

	//Datensätze durchgehen
	while(sqlite3_step(sql3Statement) != SQLITE_DONE)
	{
		printf("FUCK ");
		//Ausgabe der Datenfelder als Text
		sReturnMessage += reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, 1));
		sReturnMessage += " ";
		sReturnMessage +=reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, 2));
		sReturnMessage += " ";
		sReturnMessage +=reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, 3));
		sReturnMessage += " ";
		sReturnMessage +=reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, 4));
		sReturnMessage += " ";
		sReturnMessage +=reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, 5));
		sReturnMessage += " ";
		sReturnMessage +=reinterpret_cast<const char*>(sqlite3_column_text(sql3Statement, 6));
		sReturnMessage += "\r\n";
		printf("THIS\r\n");
	}
	//Statement löschen
	sqlite3_finalize(sql3Statement);

	//Sendet Die Logdaten als String zurück
	return sReturnMessage;

}
