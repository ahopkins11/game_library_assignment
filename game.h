#ifndef GAME_H
#define GAME_H
 
#include <string>
 
class Game {
public:
    // Constructors
    Game();
    Game(std::string title, std::string publisher, std::string genre,
         float hoursPlayed, float price, int year);
 
    // Getters
    std::string getTitle()       const;
    std::string getPublisher()   const;
    std::string getGenre()       const;
    float       getHoursPlayed() const;
    float       getPrice()       const;
    int         getYear()        const;
 
    // Setters
    void setTitle(std::string title);
    void setPublisher(std::string publisher);
    void setGenre(std::string genre);
    void setHoursPlayed(float hoursPlayed);
    void setPrice(float price);
    void setYear(int year);
 
    // Display a formatted summary of the game
    void print() const;
 
private:
    std::string title_;
    std::string publisher_;
    std::string genre_;
    float       hoursPlayed_;
    float       price_;
    int         year_;
};
 
#endif // GAME_H
