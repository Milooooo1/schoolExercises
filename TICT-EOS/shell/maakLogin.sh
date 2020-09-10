#!/usr/bin/env bash

echo "Do you want to enter a username? [y/n]"

read username

if [[ $response = "y" ]] ; then
    echo "Enter your username:"
    read username
    echo "You entered the username:" $username
else
    username=$(whoami)
    echo "Your username is:" $username
fi

running=true; 

while [ $running = true ]
do 
    echo "Enter your password: "
    read -s password
    echo "Please enter your password again: "
    read -s password2
    if [[ $password = $password2 ]] ; then
        length=${#password}
        if [[ $length -ge 8 ]]; then  
            echo "Passwords matched and contains at least 8 characters."
            running=false;
        else
            echo "Password did not contain atleast 8 characters."
        fi
    else
        echo "Passwords did not match, please try again."
    fi
done

echo $username, $password | md5sum >> $1

