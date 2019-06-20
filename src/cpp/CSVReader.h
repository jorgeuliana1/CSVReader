//
// Created by jorgeuliana1 on 19/06/19.
//

#ifndef CSVREADER_CSVREADER_H
#define CSVREADER_CSVREADER_H

#include <map>
#include <fstream>
#include <regex>

/**
 * @author J. Jorge Moutinho Uliana (GitHub: jorgeuliana1)
 * Namespace for the CSVReader class and related classes (maybe in the future).
 */
namespace csv_reader {

    /**
     * CSVReader main class.
     * This class is the responsible for the reading of CSV files, it is meant to be simple and functional. Uses only
     * C++ basic features.
     * @author J. Jorge Moutinho Uliana (GitHub: jorgeuliana1)
     */
class CSVReader {
private:
    std::ifstream input;               // File input stream.
    std::string cache;                 // Cached string.
    std::regex separator;              // CSV Separator. (regex)
    bool tiNext;                       // Is there a next line?
    bool tiIndex;                      // Is there a index line?
    std::map<std::string, int> header; // Header interpreter.

    std::vector<std::string> split(const std::string&, std::regex);
    /* Split function, similar to String.split(regex) in java. */

public:
    /**
     * CSVReader constructor.
     * @param const std::string& filepath.
     * Path of the CSV file to be read.
     * @param const std::string& sprtr.
     * Regex of the separator. The information will be separated based on this.
     * @param const bool& isThereIndex.
     * True if the first line of the CSV is a header.
     * False if it isn't.
     * If false, there will be no possibility of using functions that search by index name, only by number.
     */
    CSVReader(const std::string&, const std::string& , const bool&);
    /**
     * CSVReader destructor.
     * Destructs the object.
     */
    ~CSVReader();
    /**
     * Reads the next line of the csv file. The lines are all stored on a cache string. When a new line is read the one
     * before it is thrown away and replaced by a new one. It is prudent to be careful with this function for a efficient
     * program.
     */
    void next();
    /**
     * Used to check if the reader has reached the end of the file.
     * @return Returns 'true' if the reader has reached the end of the file or if the file wasn't initialized properly.
     * Returns 'false' if the next line can be read without any problem.
     */
    bool eof();
    /**
     * Function that returns a string of the content located at the current cached line and in the specific given index.
     * @param Index number of the wanted element.
     * @return Returns the wanted element if the index is valid.
     */
    std::string getFromCachedLine(const int&);
    /**
     * Function that returns a string of the content located at the current cached line and in the specific given index.
     * @param Name of the wanted element index/category.
     * @return Returns the wanted element if the index is valid, otherwise it will return the first element of the line.
     */
    std::string getFromCachedLine(const std::string&);
};

}


#endif //CSVREADER_CSVREADER_H
