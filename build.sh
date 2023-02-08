#!/bin/bash

echo "$(tput setaf 4 && tput bold)[1] Running Make...$(tput sgr0)"
make || {
	echo "$(tput setaf 1 && tput bold)[!] An error occurred with make. Aborting...$(tput sgr0)"
	exit;
}

echo "$(tput setaf 4 && tput bold)[2] Uploading to Brain...$(tput sgr0)"
pros upload || {
	echo "$(tput setaf 1 && tput bold)[!] Failed to upload to robot brain.$(tput sgr0)"
	exit;
}

echo "$(tput setaf 2 && tput bold)[✔] Build successful$(tput sgr0)"