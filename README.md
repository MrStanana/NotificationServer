# NotificationServer
Modular Notification Server

## Introduction
Allows multiple users to access notifications from language-independent distributed modules. Also allows remote control.

## Servers
Control server: receives control commands, such as shutdown.
User server: accepts connections from user applications.
Module server: receives data from external modules, to store and later redistribute to users.

All communication is authenticated and done using secure tunnels.

## External Libs
cJSON, SQLite/MySQL, crypto
