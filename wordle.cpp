#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
set<string> findValidWords(const string& input, const string& floating, const set<string>& dictionary);
set<string> explorePermutations(const string& input, const string& floating, const set<string>& dictionary);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> validWords;

    // If input contains no dashes
    if (in.find('-') == string::npos) {
        set<string> result = findValidWords(in, floating, dict);
        if (!result.empty()) {
            validWords.insert(result.begin(), result.end());
        }
        return validWords;
    }

    // If floating characters are provided
    if (!floating.empty()) {
        size_t found = 0;
        char hold = floating.front();

        // Replace each dash in input with a floating character
        while ((found = in.find('-', found)) != string::npos) {
            string tempInput = in;
            tempInput[found] = hold;
            string tempFloating = floating.substr(1);
            set<string> result = wordle(tempInput, tempFloating, dict);
            validWords.insert(result.begin(), result.end());
            found++;
        }
    } 
    else {
        // If no floating characters are provided, explore all permutations with alphabet
        validWords = explorePermutations(in, floating, dict);
    }

    return validWords;
}

// Define any helper functions here

set<string> findValidWords(const string& input, const string& floating, const set<string>& dictionary){
    set<string> validWords;

    // Check if the input word exists in the dictionary
    if (dictionary.find(input) != dictionary.end()) {
        validWords.insert(input);
    }

    return validWords;
}

set<string> explorePermutations(const string& input, const string& floating, const set<string>& dictionary) {
    set<string> validWords;

    for (int i = 0; i < 26; i++) {
        string tempInput = input;
        char hold = 'a' + i;
        size_t dashPos = tempInput.find('-');

        // Replace the dash with the current alphabet
        if (dashPos != string::npos) {
            tempInput[dashPos] = hold;
        }

        // Recursively explore all permutations
        set<string> result = wordle(tempInput, floating, dictionary);
        validWords.insert(result.begin(), result.end());
    }

    return validWords;
}