
#include "SkipList.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

SkipList::SkipList(int maxLvl, float p)
    : maxLevel(maxLvl), probability(p), size(0)
{
    head = new Node(Player{"", -1}, maxLevel); 
    srand(static_cast<unsigned>(time(0)));    
}

SkipList::~SkipList() {
    clear();
    delete head;
}

void SkipList::clear() {
    Node* current = head->next[0];
    while (current) {
        Node* next = current->next[0];
        delete current;
        current = next;
    }
    for (int i = 0; i < maxLevel; ++i) {
        head->next[i] = nullptr;
    }
    size = 0;
}

int SkipList::randomLevel() {
    int lvl = 1;
    while (((float)rand() / RAND_MAX) < probability && lvl < maxLevel) {
        lvl++;
    }
    return lvl;
}

SkipList::Node* SkipList::findNode(std::string name) {
    Node* current = head->next[0];
    while (current) {
        if (current->data.name == name)
            return current;
        current = current->next[0];
    }
    return nullptr;
}

void SkipList::insert(std::string name, int score) {
    remove(name);

    std::vector<Node*> update(maxLevel, nullptr);
    Node* current = head;
    Player newPlayer{name, score};

    for (int lvl = maxLevel - 1; lvl >= 0; --lvl) {
        while (current->next[lvl] && higherScoreFirst(current->next[lvl]->data, newPlayer)) {
            current = current->next[lvl];
        }
        update[lvl] = current;
    }

    int nodeLvl = randomLevel();
    Node* newNode = new Node(newPlayer, nodeLvl);

    for (int i = 0; i < nodeLvl; ++i) {
        newNode->next[i] = update[i]->next[i];
        update[i]->next[i] = newNode;
    }

    size++;
}

bool SkipList::remove(std::string name) {
    std::vector<Node*> update(maxLevel, nullptr);
    Node* current = head;

    for (int lvl = maxLevel - 1; lvl >= 0; --lvl) {
        while (current->next[lvl] && current->next[lvl]->data.name != name) {
            current = current->next[lvl];
        }
        update[lvl] = current;
    }

    Node* target = update[0]->next[0];
    if (!target || target->data.name != name)
        return false;

    int nodeLvl = target->next.size();
    for (int i = 0; i < nodeLvl; ++i) {
        if (update[i]->next[i] == target)
            update[i]->next[i] = target->next[i];
    }

    delete target;
    size--;
    return true;
}

int SkipList::getScore(std::string name) {
    Node* node = findNode(name);
    if (node) return node->data.score;
    return -1;
}

int SkipList::getRank(std::string name) {
    int rank = 0;
    Node* current = head->next[0];
    while (current) {
        if (current->data.name == name)
            return rank;
        rank++;
        current = current->next[0];
    }
    return -1;
}

void SkipList::printTopN(int n) {
    Node* current = head->next[0];
    int count = 0;
    while (current && count < n) {
        std::cout << count << ") " << current->data.name << " : " << current->data.score << "\n";
        current = current->next[0];
        count++;
    }
}

void SkipList::printAll() {
    Node* current = head->next[0];
    int count = 0;
    while (current) {
        std::cout << count << ") " << current->data.name << " : " << current->data.score << "\n";
        current = current->next[0];
        count++;
    }
}

std::vector<Player> SkipList::topN(int n) {
    std::vector<Player> result;
    Node* current = head->next[0];
    int count = 0;
    while (current && count < n) {
        result.push_back(current->data);
        current = current->next[0];
        count++;
    }
    return result;
}

std::vector<Player> SkipList::all() {
    std::vector<Player> result;
    Node* current = head->next[0];
    while (current) {
        result.push_back(current->data);
        current = current->next[0];
    }
    return result;
}
