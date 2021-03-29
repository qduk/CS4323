# CS4323
To run this project, you'll need to run each individual file separately.

First, start the server process with the server `./compile_Server.sh`.

Then, start the manager process by compiling it with `gcc ManagerAvi.c -o manager.exe` and run it with `./manager.exe`

Then, start the mfirst assistant process by compiling it with `gcc Assistant.c -o assistant.exe` and run it with `./assistant.exe`

Last, start the second half of the assistant process with `gcc assistantRecieve.c -o assistantReveive.exe` and run it with `./assistantRecieve.exe`

These will need to be ran in their own terminals. Once they are all running you can enter the info into the manager process and it the process will kick off the workflow. 
