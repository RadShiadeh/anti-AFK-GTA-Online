A script I wrote so I don't get kicked off a closed online session based on a similar Python script found in the thread: https://stackoverflow.com/questions/14489013/simulate-python-keypresses-for-controlling-a-game which you can also find in this repo

It randomly moves the character forward and wiggles the mouse

Every IRL hour it calls Mutt to source supplies, which can only happen twice per run

if using this, only use it in a closed friends session, make sure Mutt can be called and is not always busy (happens sometimes when you spawn in, going outside of your spawn location works)

make sure the key mappings are correct: you need to change your key binds as I couldn't make the arrow keys work... up: i, down: k, left: j, and right: l... change these binds in settings for your phone 

I am assuming you are using a Windows PC to make use of this bot so here are some instructions on how to run the C++ code:

--clone this repo or create a file and copy all of the C++ code into it

--Install a C++ Compiler
Windows:
Install MinGW:
Download the MinGW installer from MinGW website.
Run the installer and follow the instructions.
During installation, select at least the "g++" and "mingw32-base" options.

--Open Command Prompt:
Press Win + R, type cmd, and press Enter.
Navigate to the Code File:
Use the cd command to navigate to the directory where your bot_move.cpp file is located.
use ls to list all files

--Compile and Run:
Run the following commands:
g++ bot_move.cpp -o b
b

link to a video explaining How to set up C++ in Visual Studio Code: https://www.youtube.com/watch?v=DMWD7wfhgNY&t=232s&ab_channel=KennyYipCoding
