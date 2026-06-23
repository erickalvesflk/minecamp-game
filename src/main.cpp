//        __  ____                                     
//       /  |/  (_)___  ___  _________ _____ ___  ____ 
//      / /|_/ / / __ \/ _ \/ ___/ __ `/ __ `__ \/ __ \ 
//     / /  / / / / / /  __/ /__/ /_/ / / / / / / /_/ /
//    /_/  /_/_/_/ /_/\___/\___/\__,_/_/ /_/ /_/ .___/ 
//                                            /_/  
//      By : Erick Alves dos Santos

#include <iostream>
#include <cstdlib>
#include "minecamp.hpp"

using namespace std;

class MenuClass 
{
    public:

        bool running = true;
        bool playing = false;

        string title[7] = {
            R"(    __  ____                                      )",
            R"(   /  |/  (_)___  ___  _________ _____ ___  ____  )",
            R"(  / /|_/ / / __ \/ _ \/ ___/ __ `/ __ `__ \/ __ \ )",
            R"( / /  / / / / / /  __/ /__/ /_/ / / / / / / /_/ / )",
            R"(/_/  /_/_/_/ /_/\___/\___/\__,_/_/ /_/ /_/ .___/ )",
            R"(                                        /_/)",
             "- By: Erick Alves dos Santos",
        };

        void show_title()
        {
            for(size_t i = 0; i < size(title); ++i)
            {
                cout << title[i] << endl;
            }
        }

        void invalid_input()
        {
            cout << "- Inform a valid number or 'l' " << endl;
            getchar();
            getchar();                           
        }
};

void game(MenuClass& menu, string& answer)
{
    int size = stoi(answer);
    menu.playing = true;

    Minecamp minecamp(size,size*size * .3);
    string command = "";

    while (menu.playing)
    {
        system("cls");
        menu.show_title();

        minecamp.show_minecamp();
        // minecamp.xray_minecamp();
        cout << "- Inform the desire action. Which 'f' for flag, 's' for step or 'l' for leave" << endl;
        cout << "- Comand: ";
        cin >> command;

        if (command[0] == 'l'){ menu.playing = false; break;}
        
        string str_x = {}, str_y = {};
        int x = 0, y = 0;
        bool in_x = true;
            
        if(command[0] == 'f' or command[0] == 's')
        {
            cout << "Action: " << command[0] << " - You can cancel informing 'c' " << endl;
            try
            {
                cout << "-  Inform x: ";
                cin >> str_x;
                if(str_x == "c")continue;
                cout << "-  Inform y: ";
                cin >> str_y;
                if(str_y == "c") continue;

                x = stoi(str_x);
                y = stoi(str_y);

                if((x - 1 < 0) or (y - 1 < 0) or (x  - 1 > size) or (y  - 1 > size - 1)) {
                    menu.invalid_input(); 
                    continue;
                }
            }
            catch(const exception& e)
            {
                menu.invalid_input();
                continue;
            }

            pos position;
            position.x = x - 1;
            position.y = y - 1;

            if(command[0] == 'f')
            {  
                bool won = minecamp.flag(position);
                if(won)
                {
                    system("cls");
                    menu.show_title();
                    minecamp.show_minecamp();
                    cout << "\n                   YOU WIN!" << endl;
                    getchar();
                    getchar();
                    break;                    
                }
            }
            else
            {
                squareInCamp result = minecamp.step(position);
                if(result.value == Elements::Mine and (not result.flaged))
                {
                    system("cls");
                    menu.show_title();
                    minecamp.show_minecamp();
                    cout << "\n                   KABOOM!" << endl;
                    getchar();
                    getchar();
                    break;
                }
            }
        }
        else
        {
            menu.invalid_input();
            continue;
        }              
    }
}

int main()
{
    MenuClass menu;
    
    while(menu.running)
    {   
        system("cls");
        string answer = "";

        menu.show_title();
        cout << "- Hello! Inform the desire size (lxl) for the minecamp or write 'l' to leave: ";
        cin >> answer;

        if (answer[0] == 'l')
        {
            cout << "\n- The minecamp was finalized! " << endl;
            break;
        }
        try
        {
            game(menu, answer);
        }
        catch (exception e)
        {
            menu.invalid_input();
            continue;
        }
    }
    return 0;
}