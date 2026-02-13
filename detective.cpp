/*
 * Game: Detective Adventure
 * Name: Milijana Stojanovic
 * Date: 2/12/2026
 * Class: CS 240
 * Section: 01
 * Description: 
 *   A detective adventure through crime scenes
 *   and hidden locations. Gather evidence and 
 *   find out who the killer is.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// VARIABLES
vector<string> inventory; // to store the player's collected items
string currentLocation = "Police Station"; // starter location for the player
bool caseSolved = false; // boolean that keeps track whether the case is solved, i.e. the game is won
bool apartmentUnlocked = false; // player has to "use wallet" to unlock the Victim's Apartment
bool cabinUnlocked = false; // player has to "use key" and have a "photo" in their inventory to unlock the Abandoned Cabin
vector<string> locations = {"Police Station", "Crime Scene", "Victim's Apartment", "Abandoned Cabin", "Forensic Lab"}; // vector of all locations in the game

// FUNCTIONS

/**
 * checks if the player has a specific item in their inventory
 * item - the item to check for
 * return true if the item is in the inventory, false otherwise
*/
bool hasItem(string item){
    for (int i = 0; i < inventory.size(); i++){
        if (inventory[i] == item){
            return true;
        }
    }
    return false;
}

/**
 * moves player to a specific location if allowed
 * location - the name of the location to go to
*/
void goTo(string location){
    bool locationFound = false;
    for (int i = 0; i < locations.size(); i++){
        if (locations[i] == location){
            locationFound = true;
        }
    }

    if (!locationFound){
        cout << "\n[INVALID COMMAND]" << endl;
        return;
    }

    if (location == "Police Station" && !hasItem("fingerprints")) {
        cout << "\nYou can't solve the case yet. You need the fingerprints from the killer." << endl;
        return;
    }

    currentLocation = location;
}

/**
 * Displays the current location and its description.
 */
void showLocation(){
    cout << "[LOCATION: " << currentLocation << "]\n" << endl;

    if (currentLocation == "Police Station"){
        if (!hasItem("fingerprints")){
            cout << "You are at the police station.\nYour desk is cluttered with old case files, but this one isn’t closed yet.\nYou need solid evidence before you can solve the case and go home...\n" << endl;
        }
        if (hasItem("fingerprints")){
            cout << "You're back already detective?\nPlease tell us you have the killer's fingerprints...\n" << endl;
        }
    }
    else if (currentLocation == "Crime Scene"){
        if (!hasItem("wallet")){
            cout << "You stand in a quiet forest.\nYou see a shiny *wallet* buried beneath the leaves.\nIt could belong to the victim and may hold important clues.\n" << endl;
        }
        else {
            cout << "Looks like the victim's ID is in the wallet. Oh, and it has his address.\nQuick! Go to the Victim's Apartment before the killer catches up.\n" << endl;
        }
    }
    else if (currentLocation == "Victim's Apartment"){
        if (!apartmentUnlocked){
            cout << "The doorman is not letting you in. You need to use something that proves who lived here (like a wallet).\n" << endl;
        }
        else {
            cout << "You are inside the victim's apartment." << endl;
            if (!hasItem("key")){
                cout << "On a small table near the door, you notice a strange *key*.\n" << endl;
            }
            else if (!hasItem("photo") && hasItem("key")) {
                cout << "There also appears to be a *photo* on the ground.\nIt shows the victim and their spouse in front of an Abandoned Cabin.\nThat might be worth investigating...\n" << endl;
            }
            else if (hasItem("photo")){
                cout << "You recognize the Abandoned Cabin from the photo.\nYou now know exactly where to go next.\n" << endl;
            }
        }
    }
    else if (currentLocation == "Abandoned Cabin"){
        if (!cabinUnlocked) {
            cout << "The cabin door is locked. You need a key to get inside.\n" << endl;
        }
        else {
            cout << "You arrive at an abandoned cabin deep in the woods." << endl;
            if (hasItem("confession")){
                cout << "Looks like the confession was written by the killer.\nBring it to the Forensic Lab!\n" << endl;
            }
            if (!hasItem("confession")){
                cout << "Lying on a wooden table is a handwritten *confession*.\n" << endl;
            }
        }
    }
    else if (currentLocation == "Forensic Lab"){
        cout << "You are inside the forensic lab. Machines hum quietly as evidence is analyzed." << endl;
        if (!hasItem("fingerprints")){
            cout << "You can get a *fingerprints* report that could prove everything.\n" << endl;
        }
        else {
            cout << "The analysis is complete, take the fingerprints to the Police Station.\n" << endl;
        }
    }
}

/**
 * allows the player to get an item at the current location
 * item - the item to get
 */
void getItem(string item){
    cout << endl;

    if (currentLocation == "Crime Scene" && item == "wallet" && !hasItem("wallet")) {
        inventory.push_back("wallet");
        cout << "-- You got [wallet] ! --" << endl;
    }
    else if (currentLocation == "Victim's Apartment" && apartmentUnlocked) {
        if (item == "key" && !hasItem("key")) {
            inventory.push_back("key");
            cout << "-- You got [key] ! --" << endl;
        } 
        else if (item == "photo" && !hasItem("photo")) {
            inventory.push_back("photo");
            cout << "-- You got [photo] ! --" << endl;
        } else {
            cout << "[INVALID COMMAND]" << endl;
        }
    }
    else if (currentLocation == "Abandoned Cabin" && item == "confession" && !hasItem("confession") && cabinUnlocked) {
        inventory.push_back("confession");
        cout << "-- You got [confession]! --" << endl;
    } 
    else if (currentLocation == "Forensic Lab" && item == "fingerprints") {
        cout << "The lab technician shakes their head.\n\"We need evidence, like a handwritten confession, before we can extract fingerprints,\" they say." << endl;
    } 
    else {
        cout << "[INVALID COMMAND]" << endl;
    }
}

/**
 * allows the player to use an item at the current location
 * item - the item to use
 */
void useItem(string item) {
    cout << endl;

    if (!hasItem(item)) {
        cout << "[INVALID COMMAND]" << endl;
        return;
    }

    if (item == "wallet") {
        if (currentLocation == "Victim's Apartment" && !apartmentUnlocked) {
            apartmentUnlocked = true;
            cout << "You show the wallet at the door, proving who lived here.\nYou can now explore the apartment freely." << endl;
        }
        else {
            cout << "You can't use the wallet here. Try using it at the Victim's Apartment." << endl;
        }
    } 
    else if (item == "key") {
        if (currentLocation == "Abandoned Cabin" && hasItem("photo")) {
            cabinUnlocked = true;
            cout << "You use the key and unlock the correct cabin!\nTime to investigate inside." << endl;
        }
        else if (currentLocation == "Abandoned Cabin" && !hasItem("photo")){
            cout << "You try to use the key, but you realize you don’t know which cabin is correct.\nMaybe you should pick up the photo from the victim's apartment first to help you recognize it ;)" << endl;
        }
        else {
            cout << "You can't use the key here. Looks like the one you have is a cabin key..." << endl;
        }
    }
    else if (item == "confession"){
        if (currentLocation == "Forensic Lab") {
            if (!hasItem("fingerprints")){
                inventory.push_back("fingerprints");
                cout << "-- You got [fingerprints]! --" << endl;
            }
        }
        else {
            cout << "You can't use the confession here. Try taking it to the forensic lab." << endl;
        }
    }
    else if (item == "fingerprints") {
        if (currentLocation == "Police Station") {
            cout << "You present the fingerprints to your colleagues...\nAnd the killer was...the victim's WIFE!" << endl;
            caseSolved = true;
        }
        else {
            cout << "You can't use the fingerprints here. Try taking them to the police station." << endl;
        }
    }
    else {
        cout << "[INVALID COMMAND]" << endl;
    }
}

/**
 * displays the player's current inventory
 */
void showInventory(){
    cout << endl;
    cout << "--- Inventory ---" << endl;
    if(inventory.size() == 0){
        cout << "[EMPTY]" << endl;
    } else {
        for(int i = 0; i < inventory.size(); i++){
            cout << " - [" << inventory[i] << "]" << endl;
        }
    }
}

/**
 * displays a map of all game locations
 * and the player's current location
 */
void showMap(){
    cout << endl;
    cout << "--- Map ---" << endl;
    for(int i = 0; i < locations.size(); i++){
        if(locations[i] == currentLocation){
            cout << " - [" << locations[i] << "] <-- You are here" << endl;
        } else {
            cout << " - [" << locations[i] << "]" << endl;
        }
    }
}

/**
 * displays a list of available commands
 * based on the player's current location and inventory
 */
void help(){
    cout << endl;
    cout << "--- Available commands ---" << endl;
    cout << " - [show inventory]" << endl;
    cout << " - [show map]" << endl;
    cout << " - [help]" << endl;

    // show goto commands for all locations except the current one
    for (string location : locations){
        if (location != currentLocation){
            cout << " - [goto " << location << "]" << endl;
        }
    }

    // commands specific to locations
    if (currentLocation == "Crime Scene") {
        if (!hasItem("wallet")) {
            cout << " - [get wallet]" << endl;
        }
    }

    if (currentLocation == "Victim's Apartment") {
        if (hasItem("wallet") && !apartmentUnlocked) {
            cout << " - [use wallet]" << endl;
        }
        if (!hasItem("key") && apartmentUnlocked) {
            cout << " - [get key]" << endl;
        } 
        if (!hasItem("photo") && hasItem("key")) {
            cout << " - [get photo]" << endl;
        }
    }

    if (currentLocation == "Abandoned Cabin") {
        if (!cabinUnlocked) {
            if (hasItem("key")) {
            cout << " - [use key]" << endl;
        }
        }
        else {
            if (!hasItem("confession")) {
            cout << " - [get confession]" << endl;
            }
        }
    }

    if (currentLocation == "Forensic Lab") {
        if (hasItem("confession") ) {
            cout << " - [use confession]" << endl;
        }
        if (!hasItem("fingerprints")) {
            cout << " - [get fingerprints]" << endl;
        }
    }
    if (currentLocation == "Police Station" && hasItem("fingerprints")) {
        cout << " - [use fingerprints]" << endl;
    }
}

// MAIN

int main(){
    cout << endl;

    string input;

    while (!caseSolved){
        showLocation();
        cout << ">>>> What do you do? ";
        getline(cin, input);

        if (input == "help") {
            help();
        }
        else if (input == "show inventory") {
            showInventory();
        }
        else if (input == "show map") {
            showMap();
        }
        else if (input.substr(0,5) == "goto ") {
            string location = input.substr(5);
            goTo(location);
        }
        else if (input.substr(0,4) == "get ") {
            string item = input.substr(4);
            getItem(item);
        }
        else if (input.substr(0,4) == "use ") {
            string item = input.substr(4);
            useItem(item);
        }
        else {
            cout << "[INVALID COMMAND]" << endl;
        }
        cout << endl;
    }
    cout << "[YOU WIN!]" << endl;

    return 0;
}