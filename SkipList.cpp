#include "SkipList.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

SkipList::SkipList(int maxLvl, float p)
    : maxLevel(maxLvl), probability(p), size(0)
{
    head = new Node(Player{"", -1}, maxLevel); 
    srand(time(NULL));
}

SkipList::~SkipList() {
    clear();
    delete head;
}

void SkipList::clear() {
    Node* curr = head->next[0];
    while (curr != nullptr) {
        Node* temp = curr->next[0];
        delete curr;
        curr = temp;
    }
    
    for (int i = 0; i < maxLevel; i++) {
        head->next[i] = nullptr;
    }
    size = 0;
}

int SkipList::randomLevel() {
    int level = 1;
    while ((rand() / (float)RAND_MAX) < probability && level < maxLevel) {
        level++;
    }
    return level;
}

SkipList::Node* SkipList::findNode(std::string name) {
    Node* curr = head->next[0];
    while (curr != nullptr) {
        if (curr->data.name == name) {
            return curr;
        }
        curr = curr->next[0];
    }
    return nullptr;
}

void SkipList::insert(std::string name, int score) {
    // remove old entry if exists
    remove(name);

    std::vector<Node*> update(maxLevel, nullptr);
    Node* curr = head;
    Player p = {name, score};

    // find insert position at each level
    for (int level = maxLevel - 1; level >= 0; level--) {
        while (curr->next[level] != nullptr && 
               higherScoreFirst(curr->next[level]->data, p)) {
            curr = curr->next[level];
        }
        update[level] = curr;
    }

    int newLevel = randomLevel();
    Node* newNode = new Node(p, newLevel);

    // insert node at each level
    for (int i = 0; i < newLevel; i++) {
        newNode->next[i] = update[i]->next[i];
        update[i]->next[i] = newNode;
    }

    size++;
}

bool SkipList::remove(std::string name) {
    std::vector<Node*> update(maxLevel, nullptr);
    Node* curr = head;

    // find node to remove
    for (int level = maxLevel - 1; level >= 0; level--) {
        while (curr->next[level] != nullptr && 
               curr->next[level]->data.name != name) {
            curr = curr->next[level];
        }
        update[level] = curr;
    }

    Node* toDelete = update[0]->next[0];
    if (toDelete == nullptr || toDelete->data.name != name) {
        return false;
    }

    // remove from each level
    int levels = toDelete->next.size();
    for (int i = 0; i < levels; i++) {
        if (update[i]->next[i] == toDelete) {
            update[i]->next[i] = toDelete->next[i];
        }
    }

    delete toDelete;
    size--;
    return true;
}

int SkipList::getScore(std::string name) {
    Node* n = findNode(name);
    return (n != nullptr) ? n->data.score : -1;
}

int SkipList::getRank(std::string name) {
    Node* curr = head->next[0];
    int position = 0;
    
    while (curr != nullptr) {
        if (curr->data.name == name) {
            return position;
        }
        position++;
        curr = curr->next[0];
    }
    return -1;
}

void SkipList::printTopN(int n) {
    Node* curr = head->next[0];
    int idx = 0;
    while (curr != nullptr && idx < n) {
        std::cout << idx << ") " << curr->data.name 
                  << " : " << curr->data.score << "\n";
        curr = curr->next[0];
        idx++;
    }
}

void SkipList::printAll() {
    Node* curr = head->next[0];
    int idx = 0;
    while (curr != nullptr) {
        std::cout << idx << ") " << curr->data.name 
                  << " : " << curr->data.score << "\n";
        curr = curr->next[0];
        idx++;
    }
}

std::vector<Player> SkipList::topN(int n) {
    std::vector<Player> results;
    Node* curr = head->next[0];
    int count = 0;
    
    while (curr != nullptr && count < n) {
        results.push_back(curr->data);
        curr = curr->next[0];
        count++;
    }
    return results;
}

std::vector<Player> SkipList::all() {
    std::vector<Player> results;
    Node* curr = head->next[0];
    
    while (curr != nullptr) {
        results.push_back(curr->data);
        curr = curr->next[0];
    }
    return results;
}