#include <iostream>
#include <vector>

enum Elements : char {
    Flag = 'F',
    Mine = 'M'
};

struct squareInCamp
{
    bool hidden = true;
    bool flaged = false;
    char value = 48;
    char get_value()
    {   
        if(hidden)
        {
            return flaged ? Elements::Flag : 'X';
        }
        else
        {
            return value;
        }
    };
};

struct pos
{
    int x = 0;
    int y = 0;
};

class Minecamp {   
    private:
        unsigned int total_flags;
        unsigned int mine_quant {};
        bool saw_info = false;
        const unsigned int TRY_MINE_QUANT = 10;
        size_t size {};
        
        std::vector<std::vector<squareInCamp>> camp;
        std::vector<pos> mine_pos;
        std::vector<pos> player_guesses;
        
        void generate_camp();
        void recursive_safe(pos position);
        bool check_guesses();
    
    public:
        Minecamp(size_t size, unsigned int mine_quant);
        void show_minecamp();
        void xray_minecamp();
        int get_size();
        int get_flag_quant();
        std::vector<pos> get_neighboors(pos position);
        char step(pos position);
        void flag(pos position);
};