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
};

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

        size_t size {};
        try
        {
            size = stoi(answer);
            menu.playing = true;

            Minecamp minecamp(size,10);
            string command = "s";

            while (menu.playing)
            {
                system("cls");
                menu.show_title();

                minecamp.show_minecamp();
                cout << "- comando: ";
                cin >> command;

                if (command[0] == 'l') menu.playing = false;

            }
        }
        catch (exception e)
        {
            cout << "- Inform a valid number or 'l' " << endl;
            getchar();
            getchar();
            continue;
        }
    }
    return 0;
}