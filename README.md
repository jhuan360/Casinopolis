[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8871131&assignment_repo_type=AssignmentRepo)

# Casinopolis
  Authors: \<[Aryan Kanuparti](https://github.com/Aryan-Kanuparti), [Julio Gil](https://github.com/jgil014), [Jason Huang](https://github.com/jhuan360), [Miguelangel Tinoco](https://github.com/Tinoco451)\>

## Project Description
 --- We thought it would be cool to try and implement a mini-virtual casino that players could explore offline. Additionally we thought it would be an interesting   challenge to try and unify our efforts on a project, with various different components.
 
 --- We will be using C++ for this project.
 
 --- The input will be various user choices such as which minigame to play, how much to bet, when to stop playing/switch games, etc.
 
 --- The output will range from a game selection menu, to various console printed games of chance: As well as prompts to help the users play and navigate through   Casinopolis

 --- We plan to implement  a number of minigames inside the virtual casino. Starting at a menu page, the user will be prompted to choose any of the listed games –     tentatively – Poker(Texas Holdem), 21(Blackjack), Slot Machine, Roulette, Horse Racing. After the end of each game, the user should be able to decide whether to keep playing, switch to a different minigame, or exit Casinopolis.
 
--- We also plan to implement a feature where users can select a starting amount of in-game currency (from provided increments) and possible milestones or achievements for accumulating more in-game currency (doubling or tripling etc). On the other hand, if the users in-game currency hits 0, they are kicked out Casinopolis

--- A leaderboard feature that tracks and updates the earnings or previous visitors of Casinopolis and displays them relative to the current players earnings.

--- Also thinking about incorporating graphics libraries to display our output in a nicer way.

  ## UML Diagram
  ![image](https://user-images.githubusercontent.com/93834323/204666995-6ff0b676-ba35-49d5-b5ba-04e49c8d3a9f.png)


--
UML Class Description
--
We have a player class that stores the player’s name, initial balance, and chip balance. The player class includes 3 member functions that check the player’s balance, their chip balance, and a cash out option to exchange chips to currency. Those data members from the player class are being inherited by the four game classes, Poker, Blackjack, Roulette, and Slots. We also have a cards class that contains the card value(2 through A) and suits (Spades, Clubs, Diamonds, Hearts). Furthemore, We have a deck class that is dependent on the card class and uses its member variables to put together a deck of 52 cards. Additionally, each of the four games also inherits the functions from the deck class to perform their own member functions.

 
 
 ## Screenshots
 Main Landing Page
 
 ![image](https://user-images.githubusercontent.com/93834323/204667196-15af50c4-a048-4ab1-8fb1-a4f65155745b.png)
![image](https://user-images.githubusercontent.com/93834323/204668783-61a1f5d5-812a-45be-aab8-bfacbe095749.png)

Poker Example


![image](https://user-images.githubusercontent.com/93834323/204669063-b2c23932-7b26-4c4f-b45d-eebe88bf60bd.png)
![image](https://user-images.githubusercontent.com/93834323/204669088-8439c1ca-cd81-49cd-abda-7365ed9805d5.png)
![image](https://user-images.githubusercontent.com/93834323/204669141-298de0e2-7ee1-47a8-9f34-eaa4f855e7f0.png)
![image](https://user-images.githubusercontent.com/93834323/204669185-77e91808-b2c8-49d0-b886-b4af063ef4ce.png)


BlackJack Example


![image](https://user-images.githubusercontent.com/93834323/204669230-b5742d6b-c532-4c0e-8939-70995bbcac77.png)


Slot Machine Example


![image](https://user-images.githubusercontent.com/93834323/204668927-ff68059b-a80c-4cd6-8a81-0423d8862905.png)

Roulette Example


![image](https://user-images.githubusercontent.com/93834323/204669007-a078a88c-0eb5-46d8-a4c8-821c0cbc9661.png)


 
 
 ## Installation/Usage
Casinopolis is a terminal based choice game that runs the player through a virtual casino simulation. As such there is not much setup, simply opening and compiling the files in any IDE ( browser or application) will give players access to  the full game.
 ## Testing
 
 Our project was partially tested with googletest and partially tested using seperate driver files.
 ![image](https://user-images.githubusercontent.com/93834323/204670461-379f3724-2bc6-4c67-bfe8-b440bacd60c2.png)

