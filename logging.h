#include<sqlite3.h>
#include<string>

using namespace std;

//Erstellung der Datenbank Datei
#define DATABSE_FILE "sqlite3_db.sql"

//Tabellen erstellen
void CreateTable(sqlite3 *ptr, string sTableName)
{
	string buffer;
	buffer = "CREATE TABLE " + sTableName + " (id integer primary key, name text, vorname text)";


	sqlite3_exec(ptr, buffer.c_str(), NULL, NULL, NULL);
}
