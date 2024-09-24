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
    // std::cout << "table name is : " << tableName << " id is : " << id << " name is : " << name;
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
// parsing commands
void parseCommand(const std::string &command)
{
    std::cout << "Command: " << command << "\n";

    // Define regular expressions for different command patterns
    std::regex createRegex(R"(create\s+(\w+))");
    std::regex dropRegex(R"(drop\s+(\w+))");
    std::regex truncateRegex(R"(truncate\s+(\w+))");
    std::regex insertRegex(R"(insert\s+(\w+)\s+\((\d+),\s*\"([^\"]+)\"\))");
    std::smatch match;

    // Check for CREATE command
    if (std::regex_match(command, match, createRegex))
    {
        std::string tableName = match[1];
        createTable(tableName);
    }
    // Check for DROP command
    else if (std::regex_match(command, match, dropRegex))
    {
        std::string tableName = match[1];
        dropTable(tableName);
    }
    // Check for TRUNCATE command
    else if (std::regex_match(command, match, truncateRegex))
    {
        std::string tableName = match[1];
        truncateTable(tableName);
    }
    // Check for INSERT command
    else if (std::regex_match(command, match, insertRegex))
    {
        std::string tableName = match[1];
        // extract id from match
        int id = std::stoi(match[2]);
        // extract name from match
        std::string name = match[3];
        insertIntoTable(tableName, id, name);
    }
    else
    {
        std::cout << "Unknown or invalid command format!\n";
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
        std::cout << "-> create t_tablename to create table name\n-> drop t_tablename to drop table\n-> truncate t_tablename to truncate table\n-> insert t_tablename (int,string) to insert new rows in a table\n";
        std::cout << "Enter the command : \n";
        std::getline(std::cin, command);
        parseCommand(command);
    }
    return 0;
}