#include <iostream>
#include "HashMap.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>

static const char *INPUT = "Invalid input";
static const int CORRECT_ARG_NUMBER = 4;
static const int DATABASE = 1;
static const int THRESHOLD = 3;
static const int MESSAGE = 2;
static const char *const SPAM_MESSAGE = "SPAM";
static const char *const NOT_SPAM_MESSAGE = "NOT_SPAM";
static const char *const MEMORY_EXCEPTION = "Memory allocation failed";
static const char *USAGE = "Usage: SpamDetector <database path> <message path> <threshold>";

/**
 * @param input The string to convert to a non-negative integer
 * @param output A non-negative integer
 * @return true iff success
 */
bool parseInt(const char *input, int &output)
{
    char *endptr;
    long value = std::strtol(input, &endptr, 10);
    errno = 0;
    if (endptr == input || *endptr != '\0' ||
        value > INT_MAX || value < INT_MIN ||
        (errno == ERANGE && value == LONG_MAX) ||
        (errno == ERANGE && value == LONG_MIN))
    {
        return false;
    }
    output = (int) value;
    return output >= 0;
}

/**
 * @param line from database
 * @return true iff line is in correct format
 */
bool parseLine(const std::string &line, std::vector<std::string> &keys, std::vector<int> &scores)
{
    std::string word;
    std::stringstream s(line);
    int counter = 0;
    while (getline(s, word, ','))
    {

        if (++counter > 2)
        {
            return false;
        }
        if (word.length() == 0)
        {
            return false;
        }
        if (counter == 1)
        {
            keys.push_back(word);
        }
        if (counter == 2)
        {
            scores.push_back(0);
            const char *w = word.c_str();
            if (!parseInt(w, scores[scores.size() - 1]))
            {
                return false;
            }
        }
    }
    return (counter == 2);
}

/**
 * Convert uppercase letters to lowercase
 * @param input String
 */
void convertToLowercase(std::string &input)
{
    for (char &i : input)
    {
        if (i >= 65 && i <= 92)
        {
            i += 32;
        }
    }
}

/**
 * @param words Spam words
 * @param scores
 * @param filePath path to database
 * @return true iff success
 */
bool parseDatabase(std::vector<std::string> &words, std::vector<int> &scores,
                   const std::string &filePath)
{
    std::string line;
    std::ifstream database;
    database.open(filePath);
    if (!database.is_open())
    {
        return false;
    }
    while (getline(database, line))
    {
        std::vector<std::string> row;
        if (!parseLine(line, words, scores))
        {
            return false;
        }
    }
    database.close();
    for (std::string &key : words)
    {
        convertToLowercase(key);
    }
    return true;
}

/**
 * @param keys Spammy words
 * @param scores
 * @param filepath to message
 * @param totalScore sum of products of (no. of appearances)*score of spam words.
 * @return true iff success
 */
bool parseMessage(const std::vector<std::string> &keys,
                  std::vector<int> &scores, const std::string &filepath, int &totalScore)
{
	HashMap<std::string, int> scoreMap(keys, scores);
    std::string line;
    std::ifstream message;
    message.open(filepath);
    if (!message.is_open())
    {
        return false;
    }
    for (const std::pair<std::string, int> &pair : scoreMap)
    {
        while (getline(message, line))
        {
            convertToLowercase(line);
            size_t pos = line.find(pair.first, 0);
            while (pos != std::string::npos)
            {
                totalScore += pair.second;
                pos = line.find(pair.first, pos);
            }
        }
        message.clear();
    }
    message.close();
    return true;
}

/**
 * @param argc
 * @param argv
 * @param threshold
 * @param totalScore sum of products of (no. of appearances)*score of spam words.
 * @return true iff success
 */
bool parseFile(int argc, const char **argv, int &threshold, int &totalScore)
{
    if (argc != CORRECT_ARG_NUMBER)
    {
	    std::cerr << USAGE << std::endl;
        return false;
    }
    std::vector<std::string> keys;
    std::vector<int> scores;
    if (!parseInt(argv[THRESHOLD], threshold) || !threshold
        || !parseDatabase(keys, scores, argv[DATABASE])
        || !parseMessage(keys, scores, argv[MESSAGE], totalScore))
    {
	    std::cerr << INPUT << std::endl;
        return false;
    }
    return true;
}

/**
 * @param argc
 * @param argv
 * @return 0 if no errors, 1 otherwise
 */
int main(int argc, const char **argv)
{

    int threshold = 0, totalScore = 0;
    try
	{
		if (parseFile(argc, argv, threshold, totalScore))
		{
			(totalScore >= threshold) ?
			std::cout << SPAM_MESSAGE << std::endl :
			std::cout << NOT_SPAM_MESSAGE << std::endl;
			return 0;
		}
	}
	catch(std::bad_alloc&)
	{
		std::cerr << MEMORY_EXCEPTION << std::endl;
	}
	return 1;
}