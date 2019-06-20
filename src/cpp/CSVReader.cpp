//
// Created by jorgeuliana1 on 19/06/19.
//

#include <iostream>
#include "CSVReader.h"

using namespace std;

// TODO: Document the file.
// TODO: Find exceptions and do it.

namespace csv_reader {

    CSVReader::CSVReader(const string& filepath, const string& sprtr, const bool& isThereIndex) {

        // Copying the sprtr string content to separator in order to avoid some problems (please don't remove it).
        string separator;
        separator.clear();
        separator.append(sprtr);

        this->input.open(filepath); // Opening the file stream

        if(this->input.fail()) /* Handling file stream errors. */ {
            // In case we couldn't find the file:
            tiNext = false; // Responsible programmers won't get to read the files.
        }
        else // Otherwise:
            tiNext = true; // The file can be read without any problem.

        this->separator = separator;              // Setting up the separator.
        /*
         * NOTE:
         * As it can be noticed, this->cache hasn't received any value, the library must be implemented in a way that
         * we won't have troubles with this->cache being unassigned.
         */

        if(!isThereIndex) {
            this->tiIndex = false; // Used to avoid problems in functions that call by index name.
            return;
        }

        this->tiIndex = true; // Allows the usage of index-related functions.

        string raw_header; // raw_header is the unmodified first line of the csv.
        getline(this->input, raw_header); // assigning the proper value to the string.
        vector<string> header_vals = split(raw_header, this->separator); // taking the separated values.

        long unsigned int limit = header_vals.size();
        for(long unsigned int i = 0; i < limit; i++) /* Walking through the vector and ... */{
            this->header[header_vals[i]] = i; // ... assigning the values to the a position on the map.
        }

    }

    CSVReader::~CSVReader() {
        this->input.close();
    }

    vector<string> CSVReader::split(const string& str, regex spr) {
        /*
         * This functions works similarly to Java String.split(regex) function.
         */
        vector<string> vctr;
        sregex_token_iterator itr(str.begin(), str.end(), spr, -1);
        sregex_token_iterator end;
        for( ; itr!=end; ++itr)
            vctr.push_back(*itr);

        return vctr;
    }

    void CSVReader::next() {
        // If the file hasn't reached the end:
        if(!eof())
            // Get the whole line and put on the cache.
            getline(this->input, this->cache);
        else // it sets the cache line value to null.
            this->cache = "null";
    }

    bool CSVReader::eof() {
        // Returns true if the reader has reached the end of the file or if the file doesn't exists.
        return !(this->tiNext && !this->input.eof());
    }

    string CSVReader::getFromCachedLine(const int& index) {
        // Creating vector to store the line content.
        vector<string> vctr;

        // Storing the splitted-line content in the vector.
        vctr = split(this->cache, this->separator);

        // Returning the cached line content.
        return vctr[index];
    }

    string CSVReader::getFromCachedLine(const string& indexName) {
        /*
         * Small problem here:
         *  - if we give the function a wrong index name we will receive the index 0 content.
         *  TODO: FIND A SOLLUTION FOR THAT AND THROW AN EXCEPTION.
         */

        int index = 0; // The dafault index value was set to 0.
        if(this->tiIndex) // This function can only be used properly if the user set the CSVReader to read the index.
            index = this->header[indexName];

        // Index is whitespace sensitive.
        return getFromCachedLine(index);
    }

}