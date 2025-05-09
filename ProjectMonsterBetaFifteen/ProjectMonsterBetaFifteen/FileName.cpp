#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
//#include "raylib.h"
#pragma comment(lib, "winmm.lib")
using namespace std;
void WIN(int, bool);
void condPhys(int, bool); //conditions - physical. I cannot grade your mental state
void time1(int&);
void opener(); // The opening of the game
void randencfunc(int randx/*randomenc*/, int& healthcom, int& sightcom, int smartscom, int weapondamcom, int mapdifficulty, int weaponcom, string& stuffinvbox, bool& churchkey, string& sword, bool& brothelkey, string& drug, string& beasthorn, string& priestSkin, string& bell, string choice, bool& gamEnd); //16
void combat(int&, int&, int, int, bool, int&, bool&);  //Combat!
void story(int);  //Will iterate - based off of a few different factors - important story elements
void loot(int, bool&, bool&, int&); //Will give you some sort of loot - or trap.
void border(int&); //Checks if you hit the border of the map.
void deathchar(int, bool&); //death of the character
bool swordToWeap(int&);
void descript(int, int&, string&, bool&, string&, bool&, string&, string&, string&, string&, int&, bool&, int); //This became a pain in my ass. Ignore that it does not follow convention. Furthermore, ignore this comment if it does actually ollow conventions.
int main() {
	srand(time(0));
	opener();
	/* python {{}}*/
	int map[5][5] = { //IMPORTANT. The map is (totally purposefully, not because I'm a bad programmer) flipped 90 degrees to the right. That is to say, from the center of the map, west is upwards. East is downwards.
		{rand() % 10, rand() % 10, 21/*LandMark 1* Locked Church*/, rand() % 10, rand() % 3},//Used to generate the map at random times. Set numbers will be landmarks.
		{22 /*Landmark 2* Locked Brothel*/, rand() % 15, rand() % 8, rand() % 5, rand() % 10},
		{rand() % 3, rand() % 10, 23/*Landmark 3 Wasteland of Bodies*/, rand() % 11, rand() % 10},
		{rand() % 4, rand() % 10, rand() % 16, rand() % 14, 24/*Landmark 4* The Lake*/},
		{rand() % 15, rand() % 15, rand() % 14, 25/*Landmark 5 Speaking Woods*/, rand() % 10}
	};
	string choiceM;
	string musicbox; //Below are 'essential' items. To get the full ending, one must get all of these items (except for the sword? It counts as the weapon. you probably want the sword though.
	string sword = " ";
	bool churchKey = false;
	bool brothelKey = false;
	string drug;
	string beastHorn;
	string priestSkin;
	string bell;
	string inventorey[8] = { "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" };//honestly just ignore this. I never used it properly. I'll try and implement it at a later date
	int horpos = 2; //horizontal position
	int verpos = 2; // vertical position
	int randomenc = 0; //randomencounter. Used to check for loot, or fights.
	int smarts = 0;
	bool GamEnd = false;
	int location = map[horpos][verpos];
	int sight = 0; //special mechanic for story purposes.
	int timeMain = 0;
	bool weapon = false;
	int weapondmg = 0;
	string choice;
	string riddleans;
	int health = 100;
	std::cout << "\n";
	while (GamEnd == false) {
		std::cout << "\n";
		std::cin >> choice;
		std::cout << "\n";
		if (choice == "condition") {
			condPhys(health, weapon);
			time1(timeMain);
			continue;
		}
		else if (choice == "investigate") {
			randomenc = rand() % 5;
			descript(location, sight, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, weapondmg, GamEnd, timeMain);
			weapon = swordToWeap(weapondmg);
		}
		else if (choice == "south") {
			verpos--;
			border(verpos);
			location = map[horpos][verpos];
			descript(location, sight, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, weapondmg, GamEnd, timeMain);
			randomenc = rand() % 5;
			std::cout << endl;
			weapon = swordToWeap(weapondmg);
			randencfunc(randomenc, health, sight, weapondmg, weapon, location, smarts, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, choiceM, GamEnd); //This function has personally killed me
			timeMain++;
		}
		else if (choice == "north") {
			verpos++;
			border(verpos);
			location = map[horpos][verpos];
			descript(location, sight, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, weapondmg, GamEnd, timeMain);;
			randomenc = rand() % 5;
			std::cout << endl;
			weapon = swordToWeap(weapondmg);
			randencfunc(randomenc, health, sight, weapondmg, weapon, location, smarts, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, choiceM, GamEnd);
			timeMain++;
		}
		else if (choice == "west") {
			horpos--;
			border(horpos);
			location = map[horpos][verpos];
			descript(location, sight, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, weapondmg, GamEnd, timeMain);
			randomenc = rand() % 5;
			std::cout << endl;
			weapon = swordToWeap(weapondmg);
			randencfunc(randomenc, health, sight, weapondmg, weapon, location, smarts, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, choiceM, GamEnd);
			timeMain++;
		}
		else if (choice == "east") {
			horpos++;
			border(horpos);
			location = map[horpos][verpos];
			descript(location, sight, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, weapondmg, GamEnd, timeMain);
			randomenc = rand() % 5;
			std::cout << endl;
			weapon = swordToWeap(weapondmg);
			randencfunc(randomenc, health, sight, weapondmg, weapon, location, smarts, musicbox, churchKey, sword, brothelKey, drug, beastHorn, priestSkin, bell, choiceM, GamEnd);
			timeMain++;
		}
		else if (choice == "rest") {
			health += rand() % 20;
			std::cout << "\nYou feel better. Gained health...\n";
			if (health > 120) {
				health = 120;
				std::cout << "\nYou are as healthy as something like you can be.\n\n";
			}
			if (timeMain + 1 == 24) {
				timeMain = 0;
			}
			else {
				timeMain++;
			}
		}
		else if (choice == "churchKey") {
			churchKey = true;
			cout << churchKey << endl;
		}
		else if (choice == "brothelKey") {
			brothelKey = true;
		}
		else if (choice == "end") {
			GamEnd = true;
		}
		else if (choice == "carrots") {
			sight = 100;
		}
		else if (choice == "spinach") {
			std::cout << "\nYou pull a sword out your ass\n";
			weapondmg = 100;
		}
		else if (choice == "heaven") {
			WIN(sight, GamEnd);
		}
		else {
			std::cout << "\n\nTry something you know how to do.\n\n";
		}
	}
	return 0;
}
//descript(location, sight, musicbox, sword, churchKey, brothelKey, drug, beastHorn, priestSkin, bell);
void descript(int blocation, int& sight, string& stuffinvbox, bool& churchkey, string& sword, bool& brothelkey, string& drug, string& beasthorn, string& priestSkin, string& bell, int& weapDmg, bool& gamEnd, int timeMain) {
	string choice;
	//cout << "\nBlocation " << blocation << endl; //THIS IS TO MAKE SURE THIS FUNCTION FUNCTIONS. IT IS GIVEN ME A LOT OF ISSUES.
	if (blocation == 0 || blocation == 1 || blocation == 2) {
		std::cout << "\nAround you is white. Falling winter and heaven topped trees. Nothing of note.\nKeep Moving.\n";
	}
	else if (blocation == 3 || blocation == 4) {
		std::cout << "\nYou come to a house. Stone below, wood above.\n";
		if (sight % 2 == 0) {
			std::cout << "\nIt is burnt down. Smells good.\n";
		}
		else {
			std::cout << "\nIt's quiet - perhaps empty for some time now.\n";
		}
	}
	else if (blocation == 6 || blocation == 5) {
		std::cout << "\nIn a wide white field is a small shack.\nSmaller than you, with a reeking odor.\n";
	}
	else if (blocation == 7 || blocation == 8) {
		std::cout << "\nAround the forest you find yourself, are hung strips of metal and glass.\nThe wind blows, and a noise is made.\n";
		if (sight % 2 == 0) {
			std::cout << " It is a comforting sound. A memory stirs and dies with the wind.\n";
		}
		else {
			std::cout << " The racket assaults your ears, and you continue forth.";
		}
	}
	else if (blocation == 9 || blocation == 10) {
		std::cout << "You come across a frozen pond.\nBelow the ice, small fish move around. The ice is so scratched, no reflection is seen.";
		if (sight % 2 == 0) {
			std::cout << " This is comforting for some reason.\n";
		}
		else {
			std::cout << " This is discomforting for some reason.\n";
		}
	}
	else if (blocation == 11 || blocation == 12) {
		std::cout << " You come accross a half destroyed building.\n Strewn accross the dull grass and snow are books.\n";
		if (sight > 11) {
			std::cout << "Religious texts, war scripts, plays, and tales of merriment and culture - half burnt or strewn without care.\n You're not like them, but you still feel bad.\n";
		}
		else {
			std::cout << "You can't eat paper, and your eyes too weak to read them regardless.\nKeep any of your sorrows for these things when you're like them again.\n";
		}
	}
	else if (blocation == 13) {
		std::cout << "\nFor a moment, you hear a bird chirping.\n";
		if (sight > 15) {
			std::cout << "You spot it - small, and blue. It's hopping, not flying, and looking away from you. What do you do to it?\n'eat' 'destroy' 'reap' 'stalk' or 'ignore'\n";
			std::cin >> choice;
			if (choice == "eat") {
				std::cout << "\nYou eat the bird. It's gone before it knew it. You feel satisfied momentarily.\n";
			}
			else if (choice == "destroy") {
				std::cout << "\nIn a swift moment, you bring the full force of your blackened and long leg onto the bird.\n Nothing is left of the bird save for the burst of red on the ground.\n You feel satisfied.";
			}
			else if (choice == "reap") {
				std::cout << "\nYour mind stops, and when you come back the bird is gone. You can't help but feel good.\n";
				sight++;
			}
			else if (choice == "stalk") {
				std::cout << "\nYou creep behind the bird, salivating against your own will.\nThis goes for a long moment, until you bang against a tree branch, and the bird is gone.\nYou feel terrible.\n";
			}
			else if (choice == "ignore") {
				std::cout << "\nYou ignore the bird, and listen to it's song.\nYour flesh tears at itself, but deep inside your dull head something hums.\nYou feel conflicted.\n";
			}
		}
		else {
			std::cout << "You cannot find the bird, and eventually the song ends.\n";
		}
	}
	else if (blocation == 14) {
		string choice;
		std::cout << "You wander to what appears to be a humanoid hanging from a tree.\n";
		if (sight > 6) {
			std::cout << "Beneath him is a broken blade. ";
		}
		if (sight > 5 && sight < 10) {
			std::cout << "The man is adorned in distinct clothes. ";
		}
		if (sight > 9) {
			std::cout << "A soldier of sorts. There is no bleeding anywhere along him.\n";
		}
		std::cout << "What do you do to the body?\n'eat' 'reap' 'mourn' 'ignore'\n";
		std::cin >> choice;
		if (choice == "eat") {
			std::cout << "You devour the body. You feel satisfied.\n";
		}
		else if (choice == "reap") {
			std::cout << "Your eyes fail you a moment, and when you come back the body is gone.\nYou feel good.\n";
			sight++;
		}
		else if (choice == "mourn") {
			std::cout << "You don't know this one, but you find it in you to try and mourn.\nSomething inside you pangs with guilt, and then it is quiet.\n";
		}
		else if (choice == "ignore") {
			std::cout << "You ignore the body. The body hangs alone now, likely to be forgotten.\nYou feel horrible.\n";
		}
	}
	else if (blocation == 15) {
		string choice;
		std::cout << "You come accross a grave. It's open, with light dirt covering around it.\nIts alone out in the woodss.\n";
		if (sight > 15) {
			std::cout << "\nAround you is some sort of battlegrounds. Swords and armor lay around you, all broken.\n";
			std::cout << "You look at the grave. What does it say?";
			std::cin >> choice;
			std::cout << choice << " born 1575" << endl;
			std::cout << "Nothing else can be read. This makes you feel terrible.\n";
		}
	}
	else if (blocation == 21) { //L:ocked Church
		string choice;
		if (priestSkin == "priestSkin") {
			cout << "\nTheres the church. It's quiet and empty now. Best not change that.\n";
		}
		else {
			std::cout << "You come accross a church. The windows are dark and broken, yet the stir of voice can be heard.\nRocky bottom and wooden top.\n";
			std::cout << "What do you do?\n'knock' 'break' 'ignore' 'scream'\n";
			std::cin >> choice;
			if (choice == "ignore") {
				std::cout << "\nYou ignore the church. The cold will treat them harshly. This makes you feel bad.\n";
			}
			else if (choice == "scream") {
				std::cout << "\nYou can't explain it, but your mouth warps and you scream.\nYou scream.\nThe church quivers and shakes.\nYou scream about it.\nWhoever are in the church scream and cry.\nEventually, the screaming ends.\n";
			}
			else if (choice == "break") {
				std::cout << "\nYou attempt to claw and throw yourself at the church door.\nYou hear a pastor yell and politic inside, and the noises of women and children cry.\nThe church door is far too strong for you. Perhaps there is a key.\n";
			}
			else if (choice == "knock") {
				if (stuffinvbox != "musicBox") {
					std::cout << "\nFrom inside are hushes and bustles of noise. A man's voice speaks." << endl;
					std::cout << " 'Who be thy?'" << endl;
					std::cin >> choice;
					std::cout << "\nYou try and speak, but only coughs and noises come. The voice speaks again." << endl; Sleep(1000);
					std::cout << " 'You sound of poor health. I be terribly sorry, but we cannot help thy.'\n'There be barely enough for the few in here, and the lock's key be stashed.'\n'If ye really needs the help, see bouts the key. The wars been brutal on us all. God be with ye.'\n"; Sleep(1000);//Priest.
					std::cout << "The voice stops, and you are compelled to leave before a new voice is head. She sounds young.\n"; Sleep(1000);
					std::cout << " 'Wait! Outsider, I need you to find me pappy. He's a soldier out for the thane -'\n'If ye come to him, could you... give him this?' \n"; Sleep(1000);
					std::cout << "A small box comes out a window. Its a small, wind up musical box.\n";
					stuffinvbox = "musicBox";
				}
				else if (stuffinvbox == "musicBox") {
					std::cout << "\nThe priest speaks.\n" << " ' If we spoke earlier, then its the same story. I hope - if its really that bad - you find that key.'\n";
					std::cout << churchkey << endl;
					if (churchkey == true) {
						std::cout << "\nYou knock on the door, but recall the key from earlier. You try it. It fits like a glove.\n" << "You open the door, and fit yourself in. The church is quiet. They stare at you from below.\n";Sleep(1000);
						std::cout << "They stare. The priest stares at you. He fumbles with his book.\nThe young girl in the room eyes the musicBox at your side and they stare.\n Your vision goes black.\n"; Sleep(10000);
						std::cout << "\n\n\nWhen you come back to, they're gone. The pews have been reduced to shreds which smolder lightly.\nThe girl is gone. The people are gone. The priest is gone. \nAll that remains is the tear of his vestmants in your hand and whatever is dripping from the ceiling.\n";Sleep(1000);
						std::cout << "You feel... ";
						std::cin >> choice;
						std::cout << "\nYes. You feel " << choice << endl;
						std::cout << "\nYou leave the church, gripping whats left of the priest.\n";
						priestSkin = "priestSkin";
					}
				}
			}
		}
	}
	else if (blocation == 22) {//Locked borthel
		std::cout << "\nYou come upon some sort of building. It stands around wreckage. There is a flicker of orange behind one of the windows.\n";
		if (drug == "drug") {
			std::cout << "\nYou have done all you need here.\n";
		}
		std::cout << " 'enter' 'leave'\n";
		std::cin >> choice;
		if (choice == "enter") {
			std::cout << "\nYou enter the hostel. Its empty. Chairs upturned. Drinks and flaggons on the floor.\n";
			if (sight < 10) {
				std::cout << "Your eyes are too weak now, but maybe theres something here. For now, though...";
				std::cout << "\nYou leave.\n";
			}
			else {
				std::cout << "You spot a small, dark door in the corner. Theres a light knocking and tapping from it.\nAlthough... Its locked.\nAll locks have a key.";
				if (brothelkey == true) {
					std::cout << "\nYou just so happen to have the key for this lock. Lucky you.\n";
					std::cout << "'enter' 'leave'\n";
					cin >> choice;
					if (choice == "leave") {
						std::cout << "\nYou leave. Maybe another time.\n";
					}
					else {
						std::cout << "\nYou enter the basement. Theres a groan from the dark. Illuminating a few faces is a single lantern from above.\n";Sleep(1000);
						std::cout << "A voice from the corner speaks: " << "\n ' What! A visitar.............." << " Why are you here?... We cannot hears you.\n";Sleep(5000);
						std::cout << "Even with your improved eyesight, you cannot make out this thing through the dark.\n";Sleep(1000);
						std::cout << "Disjointed voices speak at random." << " ' it's here to end us! Our misery be over! ' ' No, you idiot! The misery merely began... ' 'Whom? oh, woe.... ' ' Kill it now! '\n";
						std::cout << " ' Silence, freaks. Here, take this and leave us.' \n A vial of sorts rolls towards you. Its a sedative.";
						drug = "drug";
						Sleep(5000);
						std::cout << "\n ' There, be done with us now!. There be no more... that you'd want... '  ' We must ensure to lock the door! ' 'We did, you fool! Locks have keys... ' 'sigh! woe!' \n";Sleep(1000);
						std::cout << "Before you leave, you have a choice...\n 'reap' 'choice'\n";Sleep(1000);
						std::cin >> choice;
						if (choice == "reap") {
							std::cout << "\nYou approach the voices. Their speaking quiets as now they see you.\n" << " ' oh dear god...' 'What... are you? ' 'Here it is! Our demise! '" << "\nBefore your eyes go dark... \n" << " '";
							std::cout << " '\n";
							Sleep(1000);
							std::cout << ".";
							Sleep(1000);
							std::cout << ".";
							Sleep(1000);
							std::cout << ".";
							Sleep(1000);
							std::cout << " You feel good. You leave.\n";
						}
						else {
							std::cout << "You leave.\n";
						}
					}
				}
			}
		}
		else {
			std::cout << "You leave.\n";
		}
	}
	else if (blocation == 23) { //Wasteland of Bodies
		if (sword != "sword") {
			std::cout << "\nYou step into a field of bodies. Smoldering men in ruined chain and helms covered in white.\nScabberds strewn, tabberds of color two amongst the bodies.\nShining, glistening in the blizzard - stuck in a man's back - is a sword.\n\nFit for your size.\n";
			std::cout << "'take' or 'ignore' \n";
			std::cin >> choice;
			if (choice == "take") {
				sword = "sword";
				cout << "\nIt's perfect. Now...\nGo along, soldier.\n\n";
				weapDmg = (rand() % 5) + 5;
			}
			else if (choice == "ignore") {
				cout << "\nIt pains your chest, but you ignore the sword.\nBest to keep moving.\n";
			}
		}
		else if (sword == "sword") {
			std::cout << "\nThe field of bodies around you is familiar. You grip your sword closely.\n\n";
		}
	}
	else if (blocation == 24) { //The lake
		cout << "\nYou come along to the great lake. It spans wide and far.\n As you approach, darkness swirls at the center of the lake. You hear whispers.\n";
		std::cout << "'look' 'listen'\n\n";
		std::cin >> choice;
		if (choice == "listen") {
			std::cout << "Undiscernable, but it grows louder and louder the closer you approach.\nEventually, you hear it.\n ' Bring me proof of your excellence...' \n";
			Sleep(5000);
			std::cout << "\nAnd then it is gone.\nBest to get that proof. You are the apex.\n\n"; //Each named area will have something for the player.
			if (sword == "sword" && stuffinvbox == "musicBox" && drug == "drug" && bell == "bell" && beasthorn == "beasthorn" && priestSkin == "priestSkin") {
				std::cout << "...";
				std::cout << "\nYou hold the sword over the water, and drop it.";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << "\nYou hold the music box over the water, and drop it.";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << "\nYou hold the priest's skin over the water, and drop it.";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << "\nYou hold the sedative over the water, and drop it.";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << "\nYou hold the bell over the water, and drop it.";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << "\nYou hold the beast horn over the water, and drop it.";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << ".";
				Sleep(100);
				std::cout << "\n\n\nThe whispers stop. The forest is quiet.\n\n";Sleep(5000);
				std::cout << "Your bones relax, and your muscles unwind.\n\n"; Sleep(5000);
				std::cout << "Your throat opens, and you breath in the cold air.\n\n";Sleep(5000);
				std::cout << "Feels like Heaven...";Sleep(5000);
				std::cout << "...";Sleep(10000);
				std::cout << "You throw yourself into the lake.\n";Sleep(2000);
				std::cout << "The water fills up your empty stomach. Your lungs fill and pop through your open ribs.\n\n";Sleep(2000);
				std::cout << "Your body grows weary and drifts to sleep.\nThe water rips your arms from their sockets.\n\n";Sleep(2000);
				std::cout << "You are torn piece from piece.\nYou feel joyous at this.\n\n";Sleep(2000);
				WIN(sight, gamEnd);
			}
		}
		else if (choice == "look") {
			std::cout << "\nYou ignore the whispers, and look into the water.\n";
			if (sight < 10) {
				std::cout << "A reflection of muted colors stairs back.\nYour eyes are far too weak.\n\n";
			}
			else if (sight > 9 && sight < 16) {
				std::cout << "A reflection of a hungry human stairs back.\nSomething draped on your shoulders, and your eyes dull.\n Your eyes still too fuzzy.\n\n";
			}
			else if (sight > 15) {
				std::cout << "A reflection of yourself. Your eyes are dots of brightness\nbut sunken so deep in your skull.\nThe horns of an animal parts your scraggled dark hair.\nYour skin is a muted blue.\nYour jaw hangs slopppily. It might as well not be attatched.\nDark, crimson streaks accross your body.\n";
			}
		}
	}
	else if (blocation == 25) {//whispering woods
		if (timeMain > 7 && timeMain < 19) {
			std::cout << "\nYou hear rustling of the leaves throughout the woods, but the sun...\n";
			std::cout << "\nThe woods won't let you in yet. Perhaps the moon will be more inviting.\n";
		}
		else if (beasthorn == "beastHorn") {
			std::cout << "\nYou have finished what you needed from these woods.\nThey whisper no more.\nBest be moving.\n";
		}
		else {
			if (bell != "bell") {
				std::cout << "\nYou step into the deep woods. The leaves rustle and swing even when the wind is low.\n";
				std::cout << "The wind...";
				Sleep(2000);
				std::cout << "\nThe leaves...";
				Sleep(2000);
				std::cout << "They're speaking to you. Your mind tremors and shakes as you listen.\n";
				std::cout << "' Seek the beast... The beast you knew... Take from it... What you do deserve...'\n' The bell... Ring the bell... and meet with... The great beast...'\n";
				std::cout << "\nAs it finished speaking, a tree branch crashes to your feet.\nThere is a small, silver bell hung from the branch.\n";
				std::cout << "'take' 'ignore'\n";
				std::cin >> choice;
				if (choice == "ignore") {
					std::cout << "\nYou ignore the bell...\n";
					std::cout << "You hear a shrieking in the woods. The trees move and merge and wrap around you.\nThe bark claws at you, ripping at your thin skin and digs into your chest.\n In a flash, you are on the ground.\n";
					std::cout << " 'Take the bell, Epoch.'\n";
					std::cout << " ' I won't let you leave till. ' \n";
					std::cout << "You find yourself at the foot of the forest again.\n";
				}
				else if (choice == "take") {
					std::cout << "\nThe bell is a soft silver, and is cold to the touch.\n";
					bell = "bell";
					std::cout << "\nBest keep moving.\n";
				}
			}
			else if (bell == "bell") {
				std::cout << "\nThe woods whispers to the bell. Seek the beast.\n";
				std::cout << " ' seek' 'leave'\n";
				std::cin >> choice;
				if (choice == "seek") {
					std::cout << "\nYou venture into the woods.\nThe whispers hum and haw and creep with you, until you stand in a small clearing.\n";
					std::cout << "'bell' 'scream' 'thrash'\n";
					std::cin >> choice;
					if (choice == "thrash") {
						std::cout << "\nYou thrash. You throw yourself against every tree, and don't stop. You don't stop until you can't move.\nYou grow weary. Tired.\nWhat were you thinking?\n";
					}
					else if (choice == "scream") {
						std::cout << "\nYou try to scream, but nothing comes out. Your throat closes in on itself, and you go quiet.\nThe woods silence you, and drag you back to the brink of the forest.\n";
					}
					else if (choice == "bell") {
						std::cout << "\nYou hold the bell, and lightly ring the bell. The whispers around you swirl and grow loud and suddenly...";
						Sleep(5000);
						std::cout << "Stop.\n";
						Sleep(1000);
						std::cout << "In the complete silence of the woods, you hear the cry of an animal.\nIt cries out, weak in tone but loud.\n";
						std::cout << "Your mind goes blank, and something inside you propells you forth.\nYou trudge along the dark woods, and come to...\n";
						if (sight < 11) {
							std::cout << "\nA beast, laying in a pool of crimson.\n";
						}
						else {
							std::cout << "An elk, bleeding out on the stone ground.\n";
						}
						std::cout << "\nAdorned upon it, is a single horn.\n";
						std::cout << "'take' 'kill' 'die' 'speak'\n";
						std::cin >> choice;
						if (choice == "die") {
							std::cout << "\nYou throw yourself onto the great horn of the animal. It impales you deeply.\nYou stand up, and do it again.\nOver and over and over and over and over and\n\n";
							std::cout << "The crack of your skull broken is the last thing you hear.\nThe elk cries\n\nYou have died.\n";
							gamEnd = true;
						}
						else if (choice == "speak") {
							std::cout << "\nYou do your best to speak, but nothing is spoken. Nothing is heard.\nOnly the cries of the animal as you slowly black out.\n";
							std::cout << "\nYou wake up at the edge of the woods.\n";
						}
						else if (choice == "kill") {
							std::cout << "\nYou try your best to dig your claws into the animal,\n but you cannot bring yourself to do it.\n";
							std::cout << "\nYou try. You try so hard. You cant. The animal thrashes around.\nIt rips into your skin.\nYou can't stop it. The horn digs into you.\nYou are ripped to shreds.\n" << "\nYou have died.\n";
							gamEnd = true;
						}
						else if (choice == "take") {
							std::cout << "\nYou approach the animal. It thrashes around far too much,\nfar to dangerous to aproach it while it's awake.\n";
							if (drug == "sedative") {
								std::cout << "\nYou grab the bottle of sedatives. You hang the bottle over the animal, and a few drops spill into the animals wound.\nIt slows down...";
								Sleep(2000);
								std::cout << "\nits movement grows more docile...";
								Sleep(2000);
								std::cout << "\nIt moves no longer.\n\nYou grip the horn of the animal. As you pull, the whispers of the woods once again ignite.\nThe forest grows louder and louder. The horn shakes.\n\nuntil...";
								Sleep(10000);
								std::cout << "\n\nThe woods go quiet. You hold the horn in your hand.\nBest now to leave.\nYou feel much better.\n\n";
								beasthorn = "beastHorn";
							}
							else if (drug != "sedative") {
								std::cout << "\nBest to come back when you have something to put that thing to rest.\n";
							}
						}
					}
				}
				else if (choice == "leave") {
					std::cout << "\nYou decide against the forest. This makes you sad.\n";
				}
			}
		}

	}
}
bool swordToWeap(int& swordDam) { //this has given me so much toruble. BOOLIAN
	if (swordDam > 0) {
		return true;
	}
	else {
		return false;
	}
}


void puzzle(int x/*Randomenc*/, int& healf, bool& gamEnd, int& sightcom) {//Riddles.
	string choice;
	int puzch = rand() % 7;
	std::cout << "\nYour mind stutters then...";
	Sleep(1000);
	std::cout << "\n\nIt all stops. A voice deep within your chest speaks.\n";
	if (puzch == 0) {
		std::cout << " ' I speak without a mouth and hear without ears.'\n 'I have no body, but I come alive in the Wind. What am I? '\n an ";
		std::cin >> choice;
		if (choice == "echo") {
			std::cout << "\nYou blink. Your eyes adjust back to the white and grey around. Continue forth.\n";
		}
		else {
			std::cout << "\nYour body rages against itself, tearing and moving.\nYour ribs shatter, your muscles come undone.\nYour mind goes blank with pain...";
			Sleep(1000);
			healf -= 40;
			deathchar(healf, gamEnd);
			Sleep(1000);
			std::cout << "\nYou awake in pain. Your mind and body clearly in disarray.\nBest to keep moving, and hope it doesn't happen again.\n\n";
		}

	}
	else if (puzch == 1) {
		std::cout << " ' The more of this there is, the less you see. What is it? '\n";
		std::cin >> choice;
		if (choice == "darkness") {
			std::cout << "\nYou blink. Your eyes adjust back to the white and grey around. Continue forth.\n";
		}
		else {
			std::cout << "\nYour body rages against itself, tearing and moving.\nYour ribs shatter, your muscles come undone.\nYour mind goes blank with pain...";
			Sleep(1000);
			healf -= 40;
			deathchar(healf, gamEnd);
			Sleep(1000);
			std::cout << "\nYou awake in pain. Your mind and body clearly in disarray.\nBest to keep moving, and hope it doesn't happen again.\n\n";
		}
	}
	else if (puzch == 2) {
		std::cout << " ' I am not alive, but I grow. I do not have lungs, but I need air.\n I do not have a mouth, but water kills me. What am I? ' \n";
		std::cin >> choice;
		if (choice == "fire") {
			std::cout << "\nYou blink. Your eyes adjust back to the white and grey around. Continue forth.\n";
		}
		else {
			std::cout << "\nYour body rages against itself, tearing and moving.\nYour ribs shatter, your muscles come undone.\nYour mind goes blank with pain...";
			Sleep(1000);
			healf -= 40;
			deathchar(healf, gamEnd);
			Sleep(1000);
			std::cout << "\nYou awake in pain. Your mind and body clearly in disarray.\nBest to keep moving, and hope it doesn't happen again.\n\n";
		}
	}
	else if (puzch == 3) {
		std::cout << " ' The more you take, the more you leave behind. What am I? ' \n";
		if (choice == "footsteps") {
			std::cout << "\nYou blink. Your eyes adjust back to the white and grey around. Continue forth.\n";
		}
		else {
			std::cout << "\nYour body rages against itself, tearing and moving.\nYour ribs shatter, your muscles come undone.\nYour mind goes blank with pain...";
			Sleep(1000);
			healf -= 40;
			deathchar(healf, gamEnd);
			Sleep(1000);
			std::cout << "\nYou awake in pain. Your mind and body clearly in disarray.\nBest to keep moving, and hope it doesn't happen again.\n\n";
		}
	}
	else if (puzch == 4) {
		std::cout << " 'What has a head, a tail, but no body? '\n a ";
		std::cin >> choice;
		if (choice == "coin") {
			std::cout << "\nYou blink. Your eyes adjust back to the white and grey around. Continue forth.\n";
		}
		else {
			std::cout << "\nYour body rages against itself, tearing and moving.\nYour ribs shatter, your muscles come undone.\nYour mind goes blank with pain...";
			Sleep(1000);
			healf -= 40;
			deathchar(healf, gamEnd);
			Sleep(1000);
			std::cout << "\nYou awake in pain. Your mind and body clearly in disarray.\nBest to keep moving, and hope it doesn't happen again.\n\n";
		}
	}
	else if (puzch == 5) {
		std::cout << " 'I have cities, but no houses. I have forests, but no trees.\n I have rivers, but no water. What am I?'\n a ";
		std::cin >> choice;
		if (choice == "map") {
			std::cout << "\nYou blink. Your eyes adjust back to the white and grey around. Continue forth.\n";
		}
		else {
			std::cout << "\nYour body rages against itself, tearing and moving.\nYour ribs shatter, your muscles come undone.\nYour mind goes blank with pain...";
			Sleep(1000);
			healf -= 40;
			deathchar(healf, gamEnd);
			Sleep(1000);
			std::cout << "\nYou awake in pain. Your mind and body clearly in disarray.\nBest to keep moving, and hope it doesn't happen again.\n\n";
		}
	}
	else if (puzch == 6) {
		std::cout << " 'I can fill up a room but take up no space. What am I? \n";
		std::cin >> choice;
		if (choice == "light") {
			std::cout << "\nYou blink. Your eyes adjust back to the white and grey around. Continue forth.\n";
		}
		else {
			std::cout << "\nYour body rages against itself, tearing and moving.\nYour ribs shatter, your muscles come undone.\nYour mind goes blank with pain...";
			Sleep(1000);
			healf -= 40;
			deathchar(healf, gamEnd);
			Sleep(1000);
			std::cout << "\nYou awake in pain. Your mind and body clearly in disarray.\nBest to keep moving, and hope it doesn't happen again.\n\n";
		}
	}
	sightcom++;
	return;
}
void story(int x) {//I HATE THIS. This is the final "Core" function made and is probably the weakest.
	int storypull = x % 10;
	std::cout << "\n\nYour vision goes black, and you recall something...\n\n";
	if (storypull == 0) {
		std::cout << "You hear the voices of men, women, and children. You brush against something soft.\n";
	}
	else if (storypull == 1) {
		std::cout << "You touch cold steel, and touch a blade. Then you hear knocking.\n";
	}
	else if (storypull == 2) {
		std::cout << "You feel grass on your feet, and the humming of birds.\n";
	}
	else if (storypull == 3) {
		std::cout << "You hear the sermon and teaching of the familiar priest.\n";
	}
	else if (storypull == 4) {
		std::cout << "You hear cheer, and near you a soft music box.\n";
	}
	else if (storypull == 5) {
		std::cout << "You touch soft silver - tap it, then hear a soft ring.\n";
	}
	else if (storypull == 6) {
		std::cout << "You hear a war chant, then orders being barked.\n";
	}
	else if (storypull == 7) {
		std::cout << "You feel a wooden bow, the tension in the string, and hear the snap of the string.\n"; //hits the elk
	}
	else if (storypull == 8) {
		std::cout << "You feel a warm liquid on your hands, and taste iron in your mouth.\n";
	}
	else if (storypull == 9) {
		std::cout << "You taste the sickly sweetness of a medication.\n";
	}
	Sleep(5000);
	std::cout << "\n\nBut then the memory is gone.\nKeep moving.\n";
}
void loot(int mapdiff, bool& churchkey, bool& brothelkey, int& healf) {
	string choice;
	int lootpull = rand() % 12;
	std::cout << "\nAs you wander, you come accross...\n";
	if (lootpull == 0) {
		std::cout << "A chunk of wood - garbage.\n\n";
	}
	else if (lootpull == 1) {
		std::cout << "A wet, torn blanket - garbage.\n\n";
	}
	else if (lootpull == 2) {
		std::cout << "A ruined, small military knife - garbage\n\n";
	}
	else if (lootpull == 3) {
		std::cout << "A frozen squirrel laying in the snow - garbage\n\n";
	}
	else if (lootpull == 4) {
		std::cout << "A handwritten note covered in soot - garbage\n\n";
	}
	else if (lootpull == 5) {
		std::cout << "The body of a soldier, with a shiny key in his hand - 'take' 'ignore'\n";
		std::cin >> choice;
		if (choice == "take") {
			std::cout << "\nThe key is nice. A small cross can be felt on it.\n\n";
			churchkey = true;
		}
		else {
			std::cout << "\nSure, its your un-life.\n\n";
		}
	}
	else if (lootpull == 6) {
		std::cout << "A doll with stuffing strewn about.\n\n";
	}
	else if (lootpull == 7) {
		std::cout << "The crest of a soldier with the hand still attatched.\n\n";
	}
	else if (lootpull == 8) {
		std::cout << "A wooden box, broken open with a key stick out - 'take' 'ignore'\n";
		cin >> choice;
		if (choice == "take") {
			std::cout << "\nThe key is old.\n";
			brothelkey = true;
		}
		else {
			std::cout << "\nSure, its your un-life.\n\n";
		}
	}
	else if (lootpull == 9) {
		std::cout << "A birds nest without any eggs - garbage\n\n";
	}
	else if (lootpull == 10) {
		std::cout << "A hat, sized for a child - garbage\n\n";
	}
	else if (lootpull == 11) {
		std::cout << "A helmet, still leaking red - garbage\n\n";
	}

}
//descript(location, sight, musicbox, sword, churchKey, brothelKey, drug, beastHorn, priestSkin, bell);
void randencfunc(int randx/*randomenc*/, int& healthcom, int& sightcom, int smartscom, int weapondamcom, int mapdifficulty, int weaponcom, string& stuffinvbox, bool& churchkey, string& sword, bool& brothelkey, string& drug, string& beasthorn, string& priestSkin, string& bell, string choice, bool& gamEnd) {
	if (randx == 0) {
		puzzle(mapdifficulty, healthcom, gamEnd, sightcom);
	}
	else if (randx == 1) {
		combat(healthcom, sightcom, weapondamcom, mapdifficulty, weaponcom, smartscom, gamEnd);
	}
	else if (randx == 2 || randx == 4) {
		loot(mapdifficulty, churchkey, brothelkey, healthcom);
		combat(healthcom, sightcom, weapondamcom, mapdifficulty, weaponcom, smartscom, gamEnd);
	}
	else if (randx == 3) {
		story(mapdifficulty);
	}
}

void border(int& numbord) {
	if (numbord < 0 || numbord == 5) {
		cout << "\nYou enter trees so thick and dense you cannot see past.\n You enter, and the woods consume your mind.\n At the last moment, as it begins to suffocate you, you stumble back.\n You are in the last locaton you have found.";
		cout << "\nYour mind begs you not to try that again.\n";
		if (numbord < 0) {
			numbord = 1;
		}
		else if (numbord == 5) {
			numbord = 4;
		}
		return;
	}
}


void combat(int& healthcom, int& sightcom, int weapondamcom, int mapdifficulty, bool weaponcom, int& smartscom, bool& gamEnd) {
	std::cout << "\n\nYou hear something behind you...";
	if (mapdifficulty > 20) {
		std::cout << "\nBut then its gone...\n";
		return;
	}
	Sleep(500);
	std::cout << "\nC O M B A T\n";
	std::cout << "************\n";
	std::cout << "Hope you're ready...\n\n";
	string comChoice;
	int mondam; //Playerdamage
	int mondod; //Player dodge
	int monbonus = 0; //Bonus damage, given for properly dodging
	int endam = 1;//enemy dmage
	int enheal = 1; //enemy health. I'm really hungry while writing this.
	int enhit = 1;
	if (mapdifficulty < 3 && sightcom < 5) { //Easy foe, Low Sight
		std::cout << "There's a pitiful little thing in front of you\nYour eyes are too weak to tell what it is.\n";
		endam = 1;
		enheal += 5;
		enhit = rand() % 10;
	}
	else if (mapdifficulty < 3 && sightcom > 4 && sightcom < 8) { //Easy foe, Low-mid Sight
		std::cout << "There's a pitiful little thing in front of you\nYou can make out grey fur, but the animal's name is foriegn to you.\n";
		endam = 1;
		enheal += 5;
		enhit = rand() % 10;
	}
	else if (mapdifficulty < 3 && sightcom >7 && sightcom < 20) {
		std::cout << "There's a pitiful little thing in front of you\nIt's got grey fur, and something metal hangs from its neck.\n";
		endam = 1;
		enheal += 5;
		enhit = rand() % 10;
	}
	else if (mapdifficulty < 3 && sightcom > 19) { //Yeah idk what this one is about
		std::cout << "Theres a pitifful little thing in front of you\n It's a dog - emmaciated. Hungry. A chain hangs from its grey furred neck.\n";
		endam = 1;
		enheal += 5;
		enhit = rand() % 10;
	}
	else if (mapdifficulty > 2 && mapdifficulty < 8 && sightcom < 5) { //low-mid foe, low sight
		std::cout << "Something stands in your way.\nYour eyes are too weak to tell what it is.\n";
		endam = 4;
		enheal += 15;
		enhit = rand() % 15;
	}
	else if (mapdifficulty > 2 && mapdifficulty < 8 && sightcom > 4 && sightcom < 8) { //low-mid foe, low-mid sight
		std::cout << "Something Stands in your way.\nIt's fleshy, with blotches of brown, but the animal's name is foriegn to you.\n";
		endam = 4;
		enheal += 15;
		enhit = rand() % 15;
	}
	else if (mapdifficulty > 2 && mapdifficulty < 8 && sightcom > 7 && sightcom < 20) {
		std::cout << "A humanoid stands in your way.\nIts fleshy face is fearful, and it hold some sort of blunt weapon.\nBe careful.\n";
		endam = 4;
		enheal += 15;
		enhit = rand() % 15;
	}
	else if (mapdifficulty > 7 && mapdifficulty < 11 && sightcom < 5) {
		std::cout << "There is a hulking mass of brown ahead.\n The air grows stale and dangeorus.\n Take caution, despite your lack of vision.\n";
		endam = 7;
		enheal += 30;
		enhit = rand() % 25;
	}
	else if (mapdifficulty > 7 && mapdifficulty < 11 && sightcom >4 && sightcom < 8) {
		std::cout << "A danger ahead: Brown, matted fur stands nearly eye level with you.\n The air grows stale and dangerous.\n You do not know it, but this might hurt you.\n";//mid high foe
		endam = 7;
		enheal += 30;
		enhit = rand() % 25;
	}
	else if (mapdifficulty > 7 && mapdifficulty < 11 && sightcom >7) {
		std::cout << "Ahead, brown fur and teeth stops you. You once knew its name, but know you only know its title:\nBear\n Make sure you survive against this creature.\n"; //mid high foe
		endam = 7;
		enheal += 30;
		enhit = rand() % 25;
	}
	else if (mapdifficulty > 10 && mapdifficulty < 17 && sightcom < 5) {
		std::cout << "A mound of unseeable flesh halts your way.\nMaybe you knew this thing once, but it's horns twist and curve unnaturally.\nKill it and prove you are the apex.\n";
		endam = 10;
		enheal += 55;
		enhit = rand() % 50;
	}
	else if (mapdifficulty > 10 && mapdifficulty < 17 && sightcom > 4 && sightcom < 8) {
		std::cout << "A bleeding and fleshy homonculus of sorts wallows in the white below\nIt's groaning as it's horns drag accross the floor.\nKill it and prove you are the apex.\n";
		endam = 10;
		enheal += 55;
		enhit = rand() % 50;
	}
	else if (mapdifficulty > 10 && mapdifficulty < 17 && sightcom > 7) {
		std::cout << "A liar approaches. It's horns drag and droop but underneath layers of flesh of men and women is a liar.\nThe snow is drenched in red.\nDestroy the Deciever and prove you are the apex.\n";
		endam = 10;
		enheal += 55;
		enhit = rand() % 50;
	}
	while (enheal > 0 && healthcom > 0) {
		std::cout << " ' attack ' ' dodge ' ' defend ' \n\n";
		std::cin >> comChoice;
		if (comChoice == "attack") { //Attacking pairs well with dodging. The bonus's acrewed from dodging can be used (to depletion) in one huge attack. You are definitely getting hit when attacking though.
			std::cout << "\nIt attacks first, dealing " << endam << " damage to you.";
			healthcom -= endam;
			deathchar(healthcom, gamEnd);
			std::cout << "\nYou attack.\n";
			if (weapondamcom > 0) {
				mondam = (rand() % 20) + weapondamcom + monbonus;
				Sleep(1000);
				std::cout << "You strike well with your sword dealing " << mondam << " damage\n";
				enheal = enheal - mondam;
				monbonus = 0;
				if (enheal == 0 || enheal < 0) {
					std::cout << "\nYou cleave through it, standing victorious. You are the apex.\n";
				}
			}
			else if (weapondamcom == 0) {
				mondam = (rand() % 10) + monbonus;
				Sleep(1000);
				std::cout << "You strike well with your claws dealing " << mondam << " damage\n";
				enheal = enheal - mondam;
				monbonus = 0;
				if (enheal == 0 || enheal < 0) {
					std::cout << "\nYou pummel through it, standing victorious. You are the apex.\n";
				}
			}
		}

		else if (comChoice == "defend") {
			std::cout << "\nYou take a defensive stance.\n";
			int newdam = endam - 5; //New damage, used to reduce dmaage.
			if (newdam > 0) {
				Sleep(1000);
				std::cout << "You take " << newdam << " damage.\n";
				healthcom = healthcom - newdam;
				deathchar(healthcom, gamEnd);

			}
			else {
				Sleep(1000);
				std::cout << "You blocked all damage.\nThe enemy hurts itself while attacking.\n";
				enheal = enheal - (rand() % (monbonus + 1) + 1);
			}
		}
		else if (comChoice == "dodge") {
			mondod = rand() % 20;
			cout << "\n Dodge: " << mondod << " Hit: " << enhit << endl;
			if (mondod >= enhit) {
				Sleep(1000);
				std::cout << "\nYou dodge the attack with elegence. You gain a bonus to damage.\n";
				monbonus += 5;
				if (endam == 1) {
					enhit = rand() % 10;
				}
				else if (endam == 4) {
					enhit = rand() % 20;
				}
				else if (endam == 7) {
					enhit = rand() % 30;
				}
				else if (endam == 10) {
					enhit = rand() % 55;
				}
			}
			else if (mondod < enhit) {
				Sleep(1000);
				std::cout << "\nIt catches you, and deals " << endam << " damage to you.\nDo not fail.\n";
				healthcom -= endam;
				deathchar(healthcom, gamEnd);
				if (endam == 1) {
					enhit = rand() % 10;
				}
				else if (endam == 4) {
					enhit = rand() % 20;
				}
				else if (endam == 7) {
					enhit = rand() % 30;
				}
				else if (endam == 10) {
					enhit = rand() % 55;
				}
			}
		}
	} if (enheal == 0 || enheal < 0) {
		std::cout << "\n\nYou feel stronger... You stare at the corpse of your prey.\n";
		std::cout << "Until...\n";
		Sleep(2000);
		std::cout << ". ";
		Sleep(2000);
		std::cout << ". ";
		Sleep(2000);
		std::cout << ". \n";
		std::cout << "\nYou black out for a moment, and come back to. The body is gone.\n";
		sightcom += endam + 1;
		smartscom++;
		std::cout << "Best to keep moving.\n\n";
	}
}

void opener() {
	std::cout << "You awake. It is cold. Your vision is so blurry you might as well be blind and your body aches.\nYour stomach rumbles, and cold swirls and flows around you.\n";
	std::cout << "You do not have a weapon. You don't even have a name.\nYou're so hungry. It's quiet. So quiet around you. There's red on the snow below." << endl << endl;
	std::cout << "(Controls: 'condition' will show you your vitals\n'north' 'west' 'east' 'south' will move you in the direction you type\n'investigate' will have you investigate what is nearby.\n'rest' will have you regain a random amount of health.\nText present between ' ' are commands or dialogue.\n";
	std::cout << "\nYou have one goal. Survive. Perhaps, discover what happened to you.)\n";
}


void condPhys(int x, bool y) { /*Checks physical condition*/
	cout << x << " Health...\n\n";
	if (x > 90) {
		std::cout << "You feel strong. Do not fear what is infront of you. Apex." << endl;
	}
	else if (91 > x && x > 55) {
		std::cout << "You are strong, but weary. Be careful. " << endl;
	}
	else if (54 > x && x > 20) {
		std::cout << "You are weak. You are bloody. Your bones ache. The cold will ail you." << endl;
	}
	else if (x < 21 && x != 1) {
		std::cout << "You are delirious. The colors blur around you, clouded with red. Only the Gods may save you now." << endl;
	}
	else if (x == 1) {
		std::cout << "Nothing will save you now." << endl;
		return;
	}

	if (y = true) {
		std::cout << "You are dangerous. Predator" << endl;
	}
	else {
		std::cout << "You are without arms. Prey." << endl;
	}
}
void time1(int& x) { //Sets and Checks time
	std::cout << "You take a moment and observe the sky." << endl;
	if (x + 1 == 24) {
		x = 0;
		std::cout << endl << "The time: " << x << endl;
		std::cout << "It is dark. Midnight." << endl;
		return;
	}
	else {
		x++;
		std::cout << endl << "The time: " << x << endl;
		if (x > 7 && x < 20) {
			std::cout << "It is light." << endl;
		}
		else {
			std::cout << "It is dark." << endl;
		}
		return;
	}
}
void deathchar(int healf, bool& gamEnd) {
	if (healf == 0 || healf < 0) {
		std::cout << "\nYour vision fades, but it never returns.\nYour terrible body grows cold. You feel something rip your chest open. You have died.\nPathetic.";
		gamEnd = true;
		Sleep(100000000);
	}
}
void WIN(int sight,bool gamend) {
	std::cout << "\n\n\nYou have won.\n\n\n";
	std::cout << "You won with " << sight << " points.\n\n";
	std::cout << "\n\n\n\n\nGame developed by \nHagen Gundacker,\nAbdullah Tahir,\nMuhammend Wajeeh.\n\nStory and Narrative written by\nHagen Gundacker,\nGabriella Cruz,\nManny Abuin.\n";
	std::cout << "\nThank you for Playing.\n";
	gamend = true;
}