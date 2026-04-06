/*******************************************************************************
 * library.cpp
 * Implements the Library class. Uses std::list<Game> kept in sorted order
 * by game title. File format uses '|' as a field delimiter, one game per line.
 *
 * File format:
 *   Title|Publisher|Genre|HoursPlayed|Price|Year
 *   Example:
 *   The Witcher 3|CD Projekt Red|RPG|120.5|39.99|2015
 ******************************************************************************/
 
#include "library.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
 
// toLower() — returns a lowercase copy of the given string.
std::string Library::toLower(const std::string &str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}
 
// printHeader() — prints column labels for formatted game output
void Library::printHeader() {
    std::cout << std::left
              << std::setw(30) << "Title"
              << std::setw(20) << "Publisher"
              << std::setw(15) << "Genre"
              << std::setw(10) << "Year"
              << std::setw(12) << "Hrs Played"
              << std::setw(9)  << "Price"
              << "\n"
              << std::string(93, '-') << "\n";
}
 
//insertSorted() — inserts a game into the list in alphabetical order by title.
void Library::insertSorted(const Game &game) {
    std::list<Game>::iterator it = games_.begin();
 
    while (it != games_.end() &&
           toLower(it->getTitle()) < toLower(game.getTitle())) {
        ++it;
    }
 
    games_.insert(it, game);
}
 
// printAll() — prints every game in the library
void Library::printAll() const {
    if (games_.empty()) {
        std::cout << "  No games in library.\n";
        return;
    }
 
    printHeader();
    for (const Game &g : games_) {
        g.print();
    }
    std::cout << "  " << games_.size() << " game(s) total.\n";
}
 
// findGenre() — prints all games matching the specified genre (case-insensitive).
void Library::findGenre(const std::string &genre) const {
    bool found = false;
 
    for (const Game &g : games_) {
        if (toLower(g.getGenre()) == toLower(genre)) {
            if (!found) {
                printHeader();
                found = true;
            }
            g.print();
        }
    }
 
    if (!found) {
        std::cout << "  No games found in genre: " << genre << "\n";
    }
}
 
// findGame() — prints all games whose title contains the query string
void Library::findGame(const std::string &query) const {
    bool found = false;
 
    for (const Game &g : games_) {
        if (toLower(g.getTitle()).find(toLower(query)) != std::string::npos) {
            if (!found) {
                printHeader();
                found = true;
            }
            g.print();
        }
    }
 
    if (!found) {
        std::cout << "  No games found matching: " << query << "\n";
    }
}
 
/*
 * deleteGame() — removes the game with the exact title and release year.
 *                Returns true if a game was removed, false if not found.*/
bool Library::deleteGame(const std::string &title, int year) {
    for (std::list<Game>::iterator it = games_.begin();
         it != games_.end(); ++it) {
        if (toLower(it->getTitle()) == toLower(title) &&
            it->getYear() == year) {
            games_.erase(it);
            return true;
        }
    }
    return false;
}
 
/*
 * loadFromFile() — reads games from a '|'-delimited file into the library.
 *                  Returns true on success, false if the file cannot be opened.
 */
bool Library::loadFromFile(const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        return false;
    }
 
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
 
        std::istringstream ss(line);
        std::string title, publisher, genre, hoursStr, priceStr, yearStr;
 
        if (!std::getline(ss, title,     '|')) continue;
        if (!std::getline(ss, publisher, '|')) continue;
        if (!std::getline(ss, genre,     '|')) continue;
        if (!std::getline(ss, hoursStr,  '|')) continue;
        if (!std::getline(ss, priceStr,  '|')) continue;
        if (!std::getline(ss, yearStr,   '|')) continue;
 
        float hours = std::stof(hoursStr);
        float price = std::stof(priceStr);
        int   year  = std::stoi(yearStr);
 
        insertSorted(Game(title, publisher, genre, hours, price, year));
    }
 
    inFile.close();
    return true;
}
 
/*
 * saveToFile() — writes all games to a '|'-delimited file.
 *                Returns true on success, false if the file cannot be opened.
 */
bool Library::saveToFile(const std::string &filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        return false;
    }
 
    for (const Game &g : games_) {
        outFile << g.getTitle()       << "|"
                << g.getPublisher()   << "|"
                << g.getGenre()       << "|"
                << std::fixed << std::setprecision(1) << g.getHoursPlayed() << "|"
                << std::fixed << std::setprecision(2) << g.getPrice()       << "|"
                << g.getYear()        << "\n";
    }
 
    outFile.close();
    return true;
}
 
