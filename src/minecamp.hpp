#include <iostream>
#include <vector>
#include <random>

enum Elements : char {
    Flag = 'F',
    Mine = 'M',
    Safe = '0'
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
    }
};

struct pos
{
    int x = 0;
    int y = 0;
    static pos new_pos(unsigned int x,unsigned int y)
    {   
        pos result {};
        result.x = x;
        result.y = y;
        return result;
    }
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

        std::default_random_engine random_int_generator{std::random_device{}()};
        std::uniform_int_distribution<int> dist_mines;
        
        void generate_camp();
        void recursive_safe(pos position);
        bool check_guesses();
        pos find_safe_pos();
        
        public:
        Minecamp(size_t size, unsigned int mine_quant);
        void build_minecamp(std::string value);
        void show_minecamp();
        void xray_minecamp();
        int get_size();
        int get_flag_quant();
        std::vector<pos> get_neighboors(pos position);
        squareInCamp step(pos position);
        bool flag(pos position);
};