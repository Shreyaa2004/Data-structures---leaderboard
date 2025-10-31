# Data-structures---leaderboard
A leaderboard created using skip lists to help gain a better understand of what exactly a skip list is!

Why?
On platforms like Roblox, where there are many games that have fairly high traffic servers, it is important to keep a real-time leaderboard that quickly updates the user's rank in the game, so they are easily able to engage with it. Binary search trees would be a great efficient data structure to consider, however using them can be quite complicated to implement when completing a task such as this. A skip list would perform average with similar efficiency, using O(log n) for its insertions, deletions and look ups, 'and ends up being simpler.

What is it?
Skip lists are multi-layered linked lists, with their lower layer as a normal sorted linked list, and higher layers allowing elements to skip over other linked list nodes for improved traversal performance. When a new value is inserted, it is assigned randomly for multiple layers of the skip list. Searches begin at the top layer of the skip list and drop down levels until the target value is found, with complexity O(log n).

Plan
I want to implement a leaderboard in C++ using skip lists that contains {score, player_name} in descending order. Therefore, the methods I would want to implement are: insert(player, score) to add or update the score of a player, remove(player) to remove a player from the leaderboard, getRank(player) to return the rank of a player, and topN(n) to get the top n players.

Why skip lists?
Skip lists integrate randomness and structure, and eliminate complex tree balancing with simple coin flips. It’s also more efficient at constantly changing dataset with O(log n) performance guarantees.

Challenges?
I think during this project I will face challenges such as having no memory leaks, handling duplicate scores and ranking ties fairly.

Why should you find it interesting?
Leaderboards, though a standard feature in many games, are incredibly useful to see the ranks to see where you are. Skip lists provide this feature with a relatively efficient performance time, and they represent an easier way than observing many binary search trees.

How to run?
First open the terminal using - cd ~/Data-structures---leaderboard
Then compile the project with - g++ -Wall -Wextra -std=c++11 -O2 -o leaderboard main.cpp SkipList.cpp
Then run it with - ./leaderboard

Each Node that is part of the skip list has a Player in it as well as multiple next pointers so that we can "skip" over nodes in the list when looking for a different player and speed up erase and insert operations.

When you insert, erase, or look up a player, the multi-level structure of the skip list allows you to find the right node without having to traverse the whole list.
