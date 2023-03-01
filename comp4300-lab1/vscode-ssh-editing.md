# Editing files on Gadi through SSH with VSCode

## Extension Installation

To edit files on Gadi through VSCode, you will need to install the the [Remote Development](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack) extension pack. To install the extensions, search for `Remote Development` extension pack in the VSCode extensions pane (one of the options on the left of the window) and click `Install`. 

## Setting up connection with Gadi

To connect with the Gadi system by SSH, you will first need to configure Gadi as an SSH host. You can do this by following these steps 

1. Open the VSCode Command Pallete (`Ctrl + Shift + P`) then type and select `Remote-SSH: Add New SSH Host...` 
2. Then enter `ssh xxx444@gadi.nci.org.au` replacing `xxx444` with your Gadi username.
3. Finally select the default SSH config file by pressing enter.

## Opening the Gadi Filesystem

Each time you want to edit files on Gadi you will need to follow these steps:

1. Open the Command Pallete and select `Remote-SSH: Connect to Host...` 
2. Choose `gadi.nci.org.au`
3. This will then open a new window and you will need to enter your password for the Gadi system.
4. Select `Open Folder` in the left window pane and then select `OK` (or navigate to the specific folder you would like to open). VSCode may ask for your password again after this step.

You can now view and edit your Gadi filesystem and use the Gadi terminal just like it is your own computer - the only difference is that all of the files are stored and executed on the Gadi machine.