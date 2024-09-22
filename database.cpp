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
    std::string name;
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
}
int main()
{
    // creating table
    createTable("class10");
    for (const auto &i : database)
    {
        std::cout << "Table name : " << i.name << '\n';
    }
    return 0;
}