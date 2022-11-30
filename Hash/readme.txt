A Hash table. The keys are lower-case English words (e.g., apple, pear). 
The length of a key is at most 10. The hash function is “simply using the last character”. That is,the hash value of apple should be e, and the hash value of pear should be r. Your hash table contains exactly
26 slots (hash value a to hash value z). The total number of English words/keys you need to deal with is at most 26, so the table is never too small.
A table slot has three different statuses: “never used”, “tombstone”, and “occupied”. Table starts with 26 “never used” slots.

Searching works as follows: given a key, take its last character as the hash value. First try the corre-sponding table slot, if the objective key is there, then you have found it. If the corresponding slot is never used, terminate because we are certain that the objective is not in the table. 
If the slot is occupied but it’s not the objective, or the slot is a “tombstone”, then we move on to the next slot (may need to wrap around the table if the current slot is the last one). 
Keep trying until we either find the key or are certain that the key does not exist in the table.

Insertion works as follows: First perform searching to ensure that the key does not exist. If it already exists, then do nothing. 
If it does not, take the last character of a key as the hash value. If the corresponding table slot is not occupied (either “never used” or “tombstone”), put the key there (the slot is now occupied).
If the corresponding slot is already occupied, try the next slot. Repeat trying until you find an unoccupied slot.

Deletion works as follows: given a key, use the searching process to locate its slot. (If the key is not in the table, then do nothing.) 
Once you find the key, change the slot status to “tombstone”.

Initializing an empty hash table and take one line as input. 
The input line contains n“modification moves” separated by spaces (1 ≤n≤26). 
The available modification moves are
•AWord (Character A followed by a lower-case English word of length at most 10): Aapple means insert key apple into the hash table. 
If apple is already in the table, do nothing.
•DWord (Character D followed by a lower-case English word of length at most 10): Dapple means delete key apple from the hash table. If apple is not in the tree, do nothing. 
At the end, go through the slots from a to z, and output all the keys separated by space.

Invalid inputs are not considered.
Sample input 1: Aaaa Accc Abbb
Sample output 1: aaa bbb ccc
Sample input 2: Abba Aaaa Acca
Sample output 2: bba aaa cca
Sample input 3: Abba Aaaa Acca Daaa
Sample output 3: bba cc
