#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <ctime>  

struct Player {
    std::string name;
    int score;
};

// comparison function for sorting by score
inline bool higherScoreFirst(const Player& a, const Player& b) {
    if (a.score != b.score)
        return a.score > b.score;
    return a.name < b.name;
}

class SkipList {
public:
    SkipList(int maxLevel = 6, float p = 0.5);
    ~SkipList();

    void insert(std::string name, int score); 
    bool remove(std::string name);            
    int getScore(std::string name);           
    int getRank(std::string name);            
    void printTopN(int n);                    
    void printAll();
    std::vector<Player> topN(int n);
    std::vector<Player> all();                          

private:
    struct Node {
        Player data;
        std::vector<Node*> next;
        Node(Player p, int level) : data(p), next(level, nullptr) {}
    };

    Node* head;        
    int maxLevel;      
    float probability; 
    int size;
    std::vector<Player> players;          

    int randomLevel();            
    Node* findNode(std::string);  
    void clear();                  
};

#endif