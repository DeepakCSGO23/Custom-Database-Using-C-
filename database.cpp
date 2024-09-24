#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <regex>
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
    std::cout << "table name is : " << tableName << " id is : " << id << " name is : " << name;
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
void dropTable(std::string tableName)
{
    // ? ITERATOR=points the current element and other elements , REFERENCE=points only to the current element
    for (auto it = database.begin(); it != database.end(); it++)
    {
        // deleting table
        if (it->tableName == tableName)
        {
            database.erase(it);
            // delete that table from local storage
            if (std::filesystem::remove("database/" + tableName + ".csv"))
            {
                std::cout << "Table file removed from local storage!\n";
            }
            else
            {
                std::cout << "Failed to remove table file from local storage!\n";
            }
            std::cout << "Table dropped from database successfully!\n";
            return;
        }
    }
    std::cout << "Table not found! Enter correct table name\n";
}
// truncate table from database (remove all rows in the table but dont delete the table)
void truncateTable(std::string tableName)
{
    std::ofstream outFile("database/" + tableName + ".csv", std::ios::trunc);
    if (outFile.is_open())
    {
        // closing the file immediately after opening the file in truncate mode
        outFile.close();
        std::cout << tableName << " table is truncated successfully!\n";
    }
    else
    {
        std::cout << "Failed to open the file!\n";
    }
}
// printing all table along with its data in a database
void printAllTables()
{
    if (database.size() == 0)
    {
        std::cout << "No table present!\n";
        return;
    }
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
// Function to parse and handle the CREATE TABLE command
void parseCreateTableCommand(const std::string &command)
{
    std::cout << command << "\n";
    std::stringstream s(command);
    std::string word, result, tableName, name;
    int id;
    while (s >> word)
    {
        // valid custom db commands so that we can easily know what operations to do
        if (word == "create" || word == "insert" || word == "truncate" || word == "drop")
        {
            result += word[0];
        }
        // table name
        else if (word.substr(0, 2) == "t_")
        {
            tableName = word;
        }
        // if the command has inserting operation
        // ! IMPROVE HERE
        else if (word[0] == '(')
        {
            // row id
            id = word[1] - '0';
            // row string
            int indexOfComma = word.find(',');
            name = word.substr(indexOfComma + 2, word.length() - 4);
            std::cout << name << " ";
        }
    }
    // creating just a table example: create "table name"
    if (tableName.size() > 0 && result == "c")
    {
        createTable(tableName);
    }
    // drop table example: drop "table name"
    else if (tableName.size() > 0 && result == "d")
    {
        dropTable(tableName);
    }
    // truncate table example: truncate "table name"
    else if (tableName.size() > 0 && result == "t")
    {
        truncateTable(tableName);
    }
    // insert values into table example: insert "table name" (1,"Deepak")
    else if (tableName.size() > 0 && result == "i")
    {
        insertIntoTable(tableName, id, name);
    }
    else
    {
        std::cout << "Command doesn't exists\n";
    }
}
int main()
{
    std::string command, folderName = "database";
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
    while (true)
    {
        std::cout << "Enter the command : \n";
        std::getline(std::cin, command);
        parseCreateTableCommand(command);
    }
    return 0;
}