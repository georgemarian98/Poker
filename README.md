# Poker

The project recreates the classic game of texas hold 'em poker. Poker is any of a number of card games in which players wager over which hand is best according to that specific game's rules in ways similar to these rankings. 

The windows based application is just a simple single player experience, while the linux one is local multiplayer and is based on the client-server architecture. On either platform there is no GUI interface, the entire game is shown in the terminal.

# Installation

After you clone the repository first you must run the server application using the following command:
```bash
./server
```

After than you can connect to the server maximum 10 players, using the command for each client:

```bash
./client
```

# Usage

As each player is connecting, the server can decide after each one of them if you start the game or wait for more players. Each round the player has 2 choices: fold or check (for the moment other actions are not implemented).
