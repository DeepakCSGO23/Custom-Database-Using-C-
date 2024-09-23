#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
// structure for the row data
struct Row
{
    // row id
    int id;
    // student name
    std::string name;
};
// structure for the table data
struct Table
{
    // table name
    std::string tableName;
    // storing all rows in a table
    std::vector<Row> rows;
};
// storing all table in a database
std::vector<Table> database;
// function to create table
void createTable(std::string tableName)
{
    // creating a table in database with name tableName
    database.push_back({tableName, {}});
    std::cout << "Table created successfully!\n";
    return;
}
// function to insert row in a table
void insertIntoTable(std::string tableName, int id, std::string name)
{
    for (auto &table : database)
    {
        // found the table
        if (table.tableName == tableName)
        {
            // inserting the row with id and name into the table
            table.rows.push_back({id, name});
            std::cout << "Data inserted successfully!\n";
            return;
        }
    }
}
// function to drop table from database
void dropTableFromDatabase(std::string tableName)
{
    // ? ITERATOR=points the current element and other elements , REFERENCE=points only to the current element
    for (auto it = database.begin(); it != database.end(); it++)
    {
        // deleting table
        if (it->tableName == tableName)
        {
            database.erase(it);
            std::cout << "Table dropped from database successfully!\n";
            return;
        }
    }
}
// saving current data in database
void saveDatabase()
{
    std::ofstream outFile("database.csv");
    for (auto const &table : database)
    {
        outFile << "Table : " << table.tableName << "\n";
        for (auto const &row : table.rows)
        {
            outFile << row.id << ',' << row.name << "\n";
        }
    }
}
// printing all table along with its data in a database
void printAllTables()
{
    for (const auto &i : database)
    {
        // table name
        std::cout << "Table name is : " << i.tableName << "\n";
        for (const auto &j : i.rows)
        {
            std::cout << "row id : " << j.id << " student name : " << j.name << " ";
        }
        std::cout << "\n";
    }
}
int main()
{
    int option, id;
    std::string tableName, name;
    while (true)
    {
        std::cout << "Enter your option :\n 1.Create Table\n 2.Insert Row into Table\n 3.Drop a Table\n 4.Print All Table";
        std::cin >> option;
        switch (option)
        {
        // create new table
        case 1:
            std::cout << "Enter the table name : ";
            std::cin >> tableName;
            createTable(tableName);
            break;
        // insert row into table
        case 2:
            std::cout << "Enter the table name : ";
            std::cin >> name;
            std::cout << "Enter the id : ";
            std::cin >> id;
            std::cout << "Enter the name : ";
            std::cin >> name;
            insertIntoTable(tableName, id, name);
            break;
        // drop a table from database
        case 3:
            std::cout << "Enter the table name : ";
            std::cin >> tableName;
            dropTableFromDatabase(tableName);
            break;
        // print all tables in database
        case 4:
            printAllTables();
            break;
        default:
            break;
        }
    }
    return 0;
}