# Custom Local Database

## Overview

This project is a custom local database management system implemented in C++. It allows users to create, insert, truncate, and drop tables using custom commands. The data is stored locally in CSV files, which are read back into memory when needed. The system supports basic table operations with minimal overhead and is designed for small-scale, local data storage applications. Please note that this project is solely for understanding C++ concepts and does not serve any practical or useful purpose.

## Features

- **Create Table**: Create a new table with a specified name.
- **Insert Data**: Insert rows into an existing table with specified values.
- **Truncate Table**: Clear all data from a table while keeping the table structure intact.
- **Drop Table**: Delete a table and its associated data from the local storage.
- **Data Persistence**: Data is stored in CSV files and can be retrieved across sessions.

## Commands

Here are the commands you can use with this system:

- **Create a Table**
  ```
  create tablename
  ```
  Creates a table with the given `tablename`.

- **Insert Data into a Table**
  ```
  insert tablename (id,"name")
  ```
  Inserts a new row into the specified `tablename`. The `id` should be an integer, and `name` should be a string.

- **Truncate a Table**
  ```
  truncate tablename
  ```
  Removes all rows from the specified `tablename`.

- **Drop a Table**
  ```
  drop tablename
  ```
  Deletes the specified `tablename` from the system.

## Usage

1. **Setup**:
   - Clone this repository to your local machine.
    
2. **Build and Run**:
   - Build the project using Visual Studio.
   - Run the executable to interact with the database system via the command-line interface.

3. **Commands**:
   - Follow the command structure mentioned above to perform operations on your database.

## Files and Structure

- **main.cpp**: Contains the main logic and command parser.
- **Row and Table Structures**: Structs to handle row and table data within the system.
- **File Handling**: Logic to persist data in CSV files within the `database` directory.

## Future Improvements

- **Enhance Command Parsing**: Improve command parsing using more advanced techniques like regular expressions.
- **Expand Functionality**: Add support for more complex queries and operations.
- **UI Integration**: Consider integrating a basic UI for easier interaction with the database.

## Contributing

Feel free to contribute to this project by opening a pull request. All contributions are welcome!

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
