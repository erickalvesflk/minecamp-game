#include <iostream>
#include <vector>

struct squareInCamp
{
    bool hidden = true;
    char value = 48;
    char get_value()
    {
        return hidden ? 'x' : value;
    };
};

struct pos
{
    int x = 0;
    int y = 0;
};

class Minecamp {   
    private:
        size_t size {};
        unsigned int mine_quant {};
        const unsigned int TRY_MINE_QUANT = 4;

        std::vector<std::vector<squareInCamp>> camp;
        std::vector<pos> mine_pos;

        void generate_camp();

    public:
        Minecamp(size_t size, unsigned int mine_quant);
        void show_minecamp();
        void xray_minecamp();
        int get_size();
};