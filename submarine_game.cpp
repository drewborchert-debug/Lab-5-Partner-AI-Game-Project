/* 
Game: Deep Sea Diving
Name: Drew Borchert
Date: 2/13/2026

Program Description:
This is a text based submarine game where the player has 
to explore different locations, collect items, and return to the
submarine to win. 
*/

#include <iostream>
#include <vector> 
#include <string> 

using namespace std;

// General starting point and check of player
string active_loc = "Submarine";
vector<string> inventory;

bool unlocked_underwater_cave = false;
bool unlocked_shipwreck = false;
bool fin_game = false;

// Keeping track of items
bool grab_diving_suit = false;
bool grab_sonar_scanner = false;
bool grab_navigation_tool = false;
bool grab_oxygen_tank = false;
bool grab_ancient_clue = false;
bool grab_torch = false;
bool grab_special_coin = false;

// Abilities for the game
void show_description();
void show_inventory();
void show_map();
vector<string> get_available_commands();
bool valid_cmd(string user_cmd, vector<string>& avail_cmds);
void get_item(string item);
void goto_location(string location);
void use_item(string item);

//What is considered a valid command
/* Returns true if the user_cmd exists within the available commands
user is by the player where as available is done through the code*/
bool valid_cmd(string user_cmd, vector<string>& avail_cmds){
    for (int i = 0; i < avail_cmds.size(); i++){
        if(user_cmd == avail_cmds[i]){
            return true;
        }
    }
    return false;
}

//Main Game Start
int main(){

    cout << "Welcome to Deep Sea Diving!" << endl;
    cout << "Please type 'help' to see the available options." << endl;

    show_description();
    while(!fin_game){
        string user_cmd;
        getline(cin, user_cmd);
        vector<string> avail_cmds = get_available_commands();

        if(!valid_cmd(user_cmd, avail_cmds)){
            cout << "[INVALID COMMAND]" << endl;
            continue;
        }

        if(user_cmd == "help"){
            for(int i = 0; i < avail_cmds.size(); i++){
                cout << "[" << avail_cmds[i] << "]" << endl;
            }
        }
        else if(user_cmd == "show inventory"){
            show_inventory();
        }
        else if(user_cmd == "show map"){
            show_map();
        }
        else if(user_cmd.find("get ") == 0){
            get_item(user_cmd.substr(4));
        }
        else if(user_cmd.find("goto ") == 0){
            goto_location(user_cmd.substr(5));
        }
        else if(user_cmd.find("use ") == 0){
            use_item(user_cmd.substr(4));
        }
    }
    return 0;
}

void show_description(){
    /* Gives description of the location that the 
    player is in under 200 characters*/

    cout << "[LOCATION: " << active_loc << "]" << endl;

    if(active_loc == "Submarine"){
        cout << "You are in your submarine control room. You can find equipment and more here." << endl;
    }
    else if(active_loc == "Coral Reef"){
        cout << "You are in the colorful coral reef. Strange fish swim by and signals echo from nearby." << endl;
    }
    else if(active_loc == "Underwater Cave"){
        cout << "The cave is dark and mysterious. Ancient markings hint at hidden treasures." << endl;
    }
    else if(active_loc == "Shipwreck"){
        cout << "A sunken ship lies dead ahead. Twisted metal hides supplies and secrets." << endl;
    }
}

void show_inventory(){
    /* This will show all the items the player has or EMPTY if nothing*/

    if (inventory.size() == 0){
        cout << "[EMPTY]" << endl;
    }else{
        for(int i = 0; i < inventory.size(); i++){
            cout << "[" << inventory[i] << "]" << endl;
        }
    }
}

void show_map(){
    /* Shows all locations of the game, and indicating
    where the player is using (*) */

    cout << "[Player Map]" << endl;

    // Submarine
    if(active_loc == "Submarine"){
        cout << "- [Submarine] (*)" << endl;
    } else {
        cout << "- [Submarine]" << endl;
    }

    // Coral Reef
    if(active_loc == "Coral Reef"){
        cout << "- [Coral Reef] (*)" << endl;
    } else {
        cout << "- [Coral Reef]" << endl;
    }

    // Underwater Cave (inside Coral Reef)
    if(unlocked_underwater_cave){
        if(active_loc == "Underwater Cave"){
            cout << "    - [Underwater Cave] (*)" << endl;
        } else {
            cout << "    - [Underwater Cave]" << endl;
        }
    }

    // Shipwreck
    if(unlocked_shipwreck){
        if(active_loc == "Shipwreck"){
            cout << "- [Shipwreck] (*)" << endl;
        } else {
            cout << "- [Shipwreck]" << endl;
        }
    }
}

void get_item(string item){
    /* This will add an item to the inventory if
    it is available in the laction the player is in*/

    if(active_loc == "Submarine" && item == "diving_suit" && !grab_diving_suit){
        inventory.push_back("diving_suit");
        grab_diving_suit = true;
        cout << "You picked up the diving suit. This might help in deeper areas." << endl;
    }
    else if(active_loc == "Coral Reef" && item == "navigation_tool" && !grab_navigation_tool){
        inventory.push_back("navigation_tool");
        grab_navigation_tool = true;
        cout << "You picked up the navigation tool. This will help you find hidden paths." << endl;
    }
    else if(active_loc == "Underwater Cave" && item == "ancient_clue" && !grab_ancient_clue){
        inventory.push_back("ancient_clue");
        grab_ancient_clue = true;
        cout << "You picked up the ancient clue. Ancient markings guide to the next spot." << endl;
    }
    else if(active_loc == "Shipwreck" && item == "torch" && !grab_torch){
        inventory.push_back("torch");
        grab_torch = true;
        cout << "You picked up the torch. You can use this to shine through obstacles." << endl;
    }
    else if(active_loc == "Submarine" && item == "oxygen_tank" && !grab_oxygen_tank){
        inventory.push_back("oxygen_tank");
        grab_oxygen_tank = true;
        cout << "You picked up the oxygen tank. Extra oxygen is never a bad thing." << endl;
    }
    else if(active_loc == "Coral Reef" && item == "sonar_scanner" && !grab_sonar_scanner){
        inventory.push_back("sonar_scanner");
        grab_sonar_scanner = true;
        cout << "You picked up the sonar scanner. Scan the area to reveal hidden paths." << endl;
    }
    else if(active_loc == "Shipwreck" && item == "special_coin" && !grab_special_coin){
        inventory.push_back("special_coin");
        grab_special_coin = true;
        cout << "You picked up the special treasure coin. Sure is shiny, this will be of use later." << endl;
    }
    else{
        cout << "You cannot get that item here." << endl;
    }
}

void goto_location(string location){
    /* Moves the player to the location of choice*/

    if(location == "Submarine"){
        active_loc = "Submarine";
        show_description();
    }
    else if(location == "Coral Reef"){
        active_loc = "Coral Reef";
        show_description();
    }
    else if(location == "Underwater Cave"){
        if(grab_navigation_tool){  // requires navigation tool to unlock
            unlocked_underwater_cave = true;
            active_loc = "Underwater Cave";
            show_description();
        }
        else{
            cout << "You cannot enter the Underwater Cave yet. You might need a navigation tool." << endl;
        }
    }
    else if(location == "Shipwreck"){
        if(grab_ancient_clue){  // requires ancient clue to unlock
            unlocked_shipwreck = true;
            active_loc = "Shipwreck";
            show_description();
        }
        else{
            cout << "You cannot access the Shipwreck yet. Maybe the ancient clue will help." << endl;
        }
    }
    else{
        cout << "That location does not exist." << endl;
    }
}

void use_item(string item){
     /* Uses an item from the player's inventory to unlock areas or win the game */

    // Make sure the player actually has the item
    bool has_item = false;
    for(int i = 0; i < inventory.size(); i++){
        if(inventory[i] == item){
            has_item = true;
            break;
        }
    }

    if(!has_item){
        cout << "You don't have that item to use." << endl;
        return;
    }

    // Using items in specific locations
    if(active_loc == "Submarine" && item == "torch"){
        // Win condition: must have all 4 required items
        if(grab_diving_suit && grab_navigation_tool && grab_ancient_clue && grab_torch){
            cout << "You use the torch to cut through the final barrier in your submarine!" << endl;
            if(grab_special_coin){
                cout << "Your special coin shines! Your victory is doubled!" << endl;
            }
            cout << "[YOU WIN!]" << endl;
            fin_game = true;
        } else {
            cout << "You need all required items before using the torch here." << endl;
        }
    }
    else if(active_loc == "Coral Reef" && item == "sonar_scanner"){
        cout << "You scan the reef with the sonar scanner. Paths to hidden treasures appear!" << endl;
    }
    else if(active_loc == "Coral Reef" && item == "navigation_tool"){
        unlocked_underwater_cave = true;
        cout << "You use the navigation tool to chart a path to the Underwater Cave." << endl;
    }
    else if(active_loc == "Underwater Cave" && item == "ancient_clue"){
        unlocked_shipwreck = true;
        cout << "The ancient clue reveals the way to the Shipwreck." << endl;
    }
    else{
        cout << "You can't use that item here." << endl;
    }
}

vector<string> get_available_commands(){
    /* Returns a vector of all commands the player can currently use */

    vector<string> commands;

    // Always available commands
    commands.push_back("help");
    commands.push_back("show inventory");
    commands.push_back("show map");

    // Location-based goto commands
    commands.push_back("goto Submarine");
    commands.push_back("goto Coral Reef");
    if(unlocked_underwater_cave || grab_navigation_tool){
        commands.push_back("goto Underwater Cave");
    }
    if(unlocked_shipwreck || grab_ancient_clue){
        commands.push_back("goto Shipwreck");
    }

    // Item-based get commands
    if(active_loc == "Submarine" && !grab_diving_suit){
        commands.push_back("get diving_suit");
    }
    if(active_loc == "Submarine" && !grab_oxygen_tank){
        commands.push_back("get oxygen_tank");
    }
    if(active_loc == "Coral Reef" && !grab_navigation_tool){
        commands.push_back("get navigation_tool");
    }
    if(active_loc == "Coral Reef" && !grab_sonar_scanner){
        commands.push_back("get sonar_scanner");
    }
    if(active_loc == "Underwater Cave" && !grab_ancient_clue){
        commands.push_back("get ancient_clue");
    }
    if(active_loc == "Shipwreck" && !grab_torch){
        commands.push_back("get torch");
    }
    if(active_loc == "Shipwreck" && !grab_special_coin){
        commands.push_back("get special_coin");
    }

    // Item-based use commands
    for(int i = 0; i < inventory.size(); i++){
        commands.push_back("use " + inventory[i]);
    }

    return commands;
}
