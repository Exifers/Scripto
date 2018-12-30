#pragma once

/**
 * @name read_file
 * @details Reads the content of a file into a string.
 * @param filename the name of the file to be read
 * @return a string containing the content of the file
 */
std::string read_file(std::string filename);

/**
 * @name read_cin
 * @@details Reads standard input and stores it into a string until it finds EOF
 * character.
 * @return a string containing the read standard input
 */
std::string read_cin();
