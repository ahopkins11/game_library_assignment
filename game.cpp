#include "game.h"
#include <iostream>
#include <iomanip>
 
// Default constructor — initializes to empty/zero values
Game::Game()
    : title_(""), publisher_(""), genre_(""),
      hoursPlayed_(0.0f), price_(0.0f), year_(0) {}
 
//Parameterized constructor
Game::Game(std::string title, std::string publisher, std::string genre,
           float hoursPlayed, float price, int year)
    : title_(title), publisher_(publisher), genre_(genre),
      hoursPlayed_(hoursPlayed), price_(price), year_(year) {}
 
//Getters
 
std::string Game::getTitle()       const { return title_;       }
std::string Game::getPublisher()   const { return publisher_;   }
std::string Game::getGenre()       const { return genre_;       }
float       Game::getHoursPlayed() const { return hoursPlayed_; }
float       Game::getPrice()       const { return price_;       }
int         Game::getYear()        const { return year_;        }
 
//Setters
 
void Game::setTitle(std::string title)           { title_       = title;       }
void Game::setPublisher(std::string publisher)   { publisher_   = publisher;   }
void Game::setGenre(std::string genre)           { genre_       = genre;       }
void Game::setHoursPlayed(float hoursPlayed)     { hoursPlayed_ = hoursPlayed; }
void Game::setPrice(float price)                 { price_       = price;       }
void Game::setYear(int year)                     { year_        = year;        }
 
//print() — displays a formatted summary of this game
void Game::print() const {
    std::cout << std::left
              << std::setw(30) << title_
              << std::setw(20) << publisher_
              << std::setw(15) << genre_
              << std::setw(10) << year_
              << std::setw(12) << std::fixed << std::setprecision(1) << hoursPlayed_
              << "$" << std::setw(8) << std::fixed << std::setprecision(2) << price_
              << "\n";
}
