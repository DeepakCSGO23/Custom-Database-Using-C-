#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
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
        if (table.tableName.compare(tableName) == 0)
        {
            // inserting the row with id and name into the table
            table.rows.push_back({id, name});
            // making the file path
            std::string filePath = "database/" + tableName + ".csv";
            // for inserting rows to ensure new rows are added to the end of the file (appending at end of the file)
            std::ofstream outFile(filePath, std::ios::app);
            if (outFile.is_open())
            {
                // csv format
                outFile << id << "," << name << "\n";
                outFile.close();
            }
            std::cout << "Row inserted successfully!\n";
            return;
        }
    }
    std::cout << "Table not found! Enter correct table name\n";
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
    std::cout << "Table not found! Enter correct table name\n";
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
    std::string folderName = "database";
    // if folder exists
    if (std::filesystem::exists(folderName))
    {
        std::cout << "Folder already exists\n";
    }
    // creating folder
    else
    {
        std::filesystem::create_directory(folderName);
    }
    int option, id;
    std::string tableName, name;
    while (true)
    {
        std::cout << "Enter your option :\n 1.Create Table\n 2.Insert Row into Table\n 3.Drop a Table\n 4.Print All Table\n 5.Exit Program";
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
            std::cin >> tableName;
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
        // exit the program
        case 5:
            return 0;
        default:
            return 0;
        }
    }
    return 0;
}