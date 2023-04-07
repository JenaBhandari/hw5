#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <deque>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
std::string current, 
int index, 
const std::set<std::string>& dict, 
std::set<std::string>& result, std::deque<char>& letters);

// Definition of primary wordle function

/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */


std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{


    // Initialize the results set
    std::set<std::string> results;

		std::deque<char> letters;

		//put in all blanks
		for (char c: in)
		{
			if (c == '-')
			{
				letters.push_back('%');
			}
		}

		//for each floating letter, delete a blank and put in the letter
		for (char b: floating)
		{
			letters.pop_back();
			letters.push_front(b);
		}


		//make copy of in
		std::string current = in;
		wordleHelper(current, 0, dict, results, letters);


    return results;

}


// Define any helper functions here
void wordleHelper(
std::string current, 
int index, 
const std::set<std::string>& dict, 
std::set<std::string>& result, 
std::deque<char>& letters) 
{
		//if to length and all floating letters within then check if in dict
    if (index == current.length() && letters.empty()) 
		{
        if (dict.find(current) != dict.end()) 
				{
          result.insert(current);
        }
        return;
    }

		//if fixed then recurse
    if (current[index] != '-') 
		{
        wordleHelper(current, index + 1, dict, result, letters);
    } 
		else 
		{
			//go thru the deck
			for (int i = 0; i < letters.size(); i++)
			{
				char frontLetter = letters.front();

				if (frontLetter == '%')
				{
					letters.pop_front();
					for (char c = 'a'; c <= 'z'; c++) 
					{
        		current[index] = c;
        		wordleHelper(current, index + 1, dict, result, letters);
						current[index] = '-';
    			}

					letters.push_back('%');
				}
				else 
				{
					letters.pop_front();

					current[index] = frontLetter;
					wordleHelper(current, index + 1, dict, result, letters);
					current[index] = '-';

					letters.push_back(frontLetter);
				}
    		
			}

    }
}
