#!/bin/bash

# This script installs all of the necessary development libraries needed for running MarkTwo.
# Once this script is complete, you shouldnt need to re-run it unless you move the code to a new machine.
# This codebase is designed to run on linux-based machines.

echo "---------------------------------------------"
echo "MarkTwo First Time Install Script"
echo "---------------------------------------------"

sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev 
sudo apt-get install libsdl2-mixer-dev 
sudo apt-get install libsdl2-ttf-dev 