//        __  ____                                     
//       /  |/  (_)___  ___  _________ _____ ___  ____ 
//      / /|_/ / / __ \/ _ \/ ___/ __ `/ __ `__ \/ __ \ 
//     / /  / / / / / /  __/ /__/ /_/ / / / / / / /_/ /
//    /_/  /_/_/_/ /_/\___/\___/\__,_/_/ /_/ /_/ .___/ 
//                                            /_/  
//      By : Erick Alves dos Santos

#include <iostream>
#include <cstdlib>


using namespace std;

class MenuClass 
{
    public:
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
    bool running = true;

    MenuClass menu;
    
    while(running)
    {   
        system("cls");
        string answer = "";

        menu.show_title();
        cout << "- Hello! Inform the desire size (lxl) for the minecamp or write 'l' to leave: ";
        cin >> answer;

        if (answer[0] == 'l'){
            cout << "\n- The minecamp was finalized! " << endl;
            break;
        }

        unsigned int size {};
        try
        {
            size = stoi(answer);
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