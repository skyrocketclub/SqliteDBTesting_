// SqliteDBTesting_.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;
 
//function declarations
static int createDB(const char* s);
static int createTable(const char* s);
static int deleteData(const char* s);
static int insertData(const char* s);
static int updateData(const char* s);
static int selectData(const char* s);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);

int main()
{
    //the double slash is important so that the folder can be in keeping the universal naming conventions of paths
    const char* dir = "c:\\users\\user\\desktop\\sqlitedbtesting_\students.db";
    sqlite3* db;

    createDB(dir);
    createTable(dir);


    //updateData(dir);
    //cout << "After Updating the data\n";
    //selectData(dir);
    //deleteData(dir);
   
     cout << "After Deleting from the data\n";
    selectData(dir);
    cout << "After reinserting values into the data\n";

    //insertData(dir);  
    selectData(dir);

    return 0;
}

static int createDB(const char* s) {
    sqlite3* DB;
    int exit = 0;

    //I try to open the DB and if it does not exist, it will be created
    exit = sqlite3_open(s, &DB);
    sqlite3_close(DB);

    return 0;
}

static int createTable(const char* s) {
    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS GRADES("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "NAME       TEXT NOT NULL, "
        "LNAME      TEXT NOT NULL, "
        "AGE        INT  NOT NULL, "
        "ADDRESS    CHAR(50), "
        "GRADE      CHAR(1) );";

    //error handling
    try {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messageError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK) {
            cerr << "Error Creating Table" << endl;
            sqlite3_free(messageError);
        }
        else {
            cout << "Table created Successfully" << endl;
            sqlite3_close(DB);
        }
    }
    catch (const exception & e) {
        cerr << e.what();
    }
    return 0;
}

static int insertData(const char* s) {
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);
    string sql("INSERT INTO GRADES (NAME,LNAME,AGE,ADDRESS,GRADE) VALUES('Alice', 'Chapa', 35, 'Tampa', 'A');"
        "INSERT INTO GRADES (NAME,LNAME,AGE,ADDRESS,GRADE) VALUES('Bob', 'Lee', 20, 'Dallas', 'B');"
        "INSERT INTO GRADES (NAME,LNAME,AGE,ADDRESS,GRADE) VALUES('Fred', 'Cooper', 24, 'New York', 'C');");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error Inserting" << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Records created Successfully!" << endl;
    }
    return 0;
}

static int selectData(const char* s) {
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB); 

    //This implies that you want all the grades  
    string sql = "SELECT * FROM GRADES;";

    //arguments are -> open DB,sql to be evaluated, callback function, 1st argument to callback, Error message 
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
    return 0;
}

/*
argc: holds the number of results
azColumn: holds each column returned in an array
argv: Holds each value in aray
*/
static int callback(void* NotUsed, int argc, char** argv, char** azColumn)
{
    for (int i{ 0 }; i < argc; i++) {
        //coolumn name and value
        cout << azColumn[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}

static int updateData(const char* s) {
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);
    
    //Table name is GRADES
    //Where clause prevents you from updating all the data entries

    string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper' ");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Records created Successfully!" << endl;
    }

    return 0;
}

static int deleteData(const char* s) {
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);

    //Delete everything from DB
    string sql = "DELETE FROM GRADES;";
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
