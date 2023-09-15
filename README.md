# Domino
This is a simulator for the game Dominoes. It is a 4 player game with 2 teams of two players each. The players can be CPU or human controlled.
The functions have some brief comments above them explaining what they accomplish. For more in depth explanations, please contact me.
This simulator was designed for use by some friends and family in Algeria, so I have some French and Algerian words, which are translated below:
Jeux: Game
Jouer: Player
Ma7roga: The round must be replayed
Tebla3 La3b: The game is closed, meaning there are no possible plays left

I also am referring to the actual domino pieces as "rocks". Think of a rock being analogous to a card in poker.
A double means the rock has 2 of the same number. So a rock with two 3's would be a double 3.
A hand is the collection of rocks a player has.

The basic rules are as follows: 
There are 28 total rocks, and each of the 4 players gets 7 at the start. If any player has at least 5 doubles in their hand, then the rocks are reshuffled.
The players are positioned in a way that each player is adjacent to both opponents. Whoever has the double 6 plays it, and play moves to the right. 
There are 2 ends of the playing pile, and a player can play a matching number from any of their rocks on the corresponding number from the playing pile.
Whichever player plays all 7 cards first wins the round. If there are no possible plays left at any time (tebla3 la3b) and no player was able to finish their hand, 
then the player with the least total sum of their rocks wins (so if I have a [2|3] and [0|1|, my total sum is 2+3+0+1=6).
If two players from opposing teams tie for the least, then the round is replayed and no one wins (the next round is restarted with the double 6). 
The team that contains the winning player gains a point tally equal to the total sum of the other team's rocks combined.
When a round finishes, the rocks are reshuffled and distributed.
When a team wins a round, either player from that team can start the next round with any rock they choose (if there is a next round).
Once one teams reaches or passes the winning point tally, they win the game.

