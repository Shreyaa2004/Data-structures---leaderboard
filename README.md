# Data-structures---leaderboard
A leaderboard created using skip lists to help gain a better understand of what exactly a skip list is!

Why?
On games such as Roblox, where there are many high traffic servers for different games, it’s important to maintain a real time leaderboard to show rank in the game with quick updates so it’s easy for the user to interact with. Binary search trees are efficient for this task but they are complex to integrate for a task like this. Skip lists offer a simpler alternative, achieving similar average performance using O(log n) for insertions, deletions, and lookups making this way simpler.

What is it?
Skip lists are a layered link list with the bottom as a standard sorted linked list and the higher it goes, it skips over nodes to allow faster traversal. When inserting a new value, it’s randomly assigned to appear in multiple layers. Searches begin at the topmost layer and drop down levels until the target is found, at O(log n).

Plan
I want to make a leaderboard with skip lists in C++. The leaderboard stores {score, player_name} in descending order. So what I’ll need to make for this is: insert(player, score) to add or update a player's score, remove(player) to remove a player from the leaderboard, getRank(player) to return the player's rank, and topN(n) to return the top N players.

Why skip lists?
Skip lists combine probability with structure, and replaces complex tree balancing logic with coin flips. It’s also more efficient at constantly changing dataset with performance guarantees with O(log n).

Challenges?
I think during this project I will face challenges such as having no memory leaks, handling duplicate scores and ranking ties fairly, and debugging.

Why should you find it interesting?
Leaderboards, although a common function, are very useful to see ranks as you are playing games. Skip lifts help attain this function with efficient performance time and is a more simpler way than binary search trees. 

How to run?
First open the terminal using - cd ~/Data-structures---leaderboard
Then compile the project with - g++ -std=c++17 -o leaderboard Leaderboard.cpp SkipList.cpp
Then run it with - ./leaderboard

Each Node in the skip list stores a Player and multiple next pointers that allow the list to “skip” over nodes for faster search, insertion, and deletion.

When you insert, remove, or look up a player, the skip list’s multi-level structure is used to quickly find the right position instead of scanning the whole list.
