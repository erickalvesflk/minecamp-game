#include <iostream>
#include <vector>
#include "minecamp.hpp"

Minecamp::Minecamp(size_t size, unsigned int mine_quant)
{   
    this->size = size;
    this->mine_quant = mine_quant;

    mine_pos.resize(mine_quant);
    camp.resize(size);
    
    for(size_t y = 0; y < size; ++y)
    {
        camp[y].resize(size);
        for(size_t x = 0; x < size; ++x)
        {    
            squareInCamp square;
            this->camp[y][x] = square;
        }
    }
    generate_camp();
}

void Minecamp::generate_camp()
{
    // Generate mines
    int find_mine_try = 0;
    for(size_t mine_index = 0; mine_index < mine_quant; ++mine_index)
    {
        int x = rand()%size;
        int y = rand()%size;

        const squareInCamp& possible_mine = camp[y][x];

        if(possible_mine.value == 'M')
        {   
            // std::cout << "mina ja gerada! - " << possible_mine.value <<  std::endl;
            if(find_mine_try <= TRY_MINE_QUANT)
            {
                mine_index -= 1;
                ++find_mine_try;
                continue;
            }
            else
            {   
                find_mine_try = 0;
                continue;
            }
        }
        
        // std::cout << x << " e " << y << " : escolhidos!" << std::endl;
        mine_pos[mine_index].x = x;
        mine_pos[mine_index].y = y;
        camp[y][x].value = 'M';

        find_mine_try = 0; // Reseta o contador de tentativas de encontrar uma mina (contador para impedir um loop infinito)
        
    }

    // Update mine's neighboors
    for(pos mine : mine_pos)
    {
        pos neighboors[8] {};
        // UP
        neighboors[0].x = mine.x;
        neighboors[0].y = mine.y + 1;
        // DOWN
        neighboors[1].x = mine.x;
        neighboors[1].y = mine.y - 1;
        // LEFT
        neighboors[2].x = mine.x - 1;
        neighboors[2].y = mine.y;
        // RIGHT
        neighboors[3].x = mine.x + 1;
        neighboors[3].y = mine.y;
        // UP-LEFT
        neighboors[4].x = mine.x - 1;
        neighboors[4].y = mine.y + 1;
        // UP-RIGHT
        neighboors[5].x = mine.x + 1;
        neighboors[5].y = mine.y + 1;
        // DOWN-LEFT
        neighboors[6].x = mine.x - 1;
        neighboors[6].y = mine.y - 1;
        // DOWN-RIGHT
        neighboors[7].x = mine.x + 1;
        neighboors[7].y = mine.y - 1;

        for (pos neighboor_pos : neighboors)
        {   
            // Verificação coordenada dentro do "campo" (array 2D)
            if(neighboor_pos.x < 0 or neighboor_pos.x >= size) continue;
            if(neighboor_pos.y < 0 or neighboor_pos.y >= size) continue;
            std::cout << "[log] - Viziho valido da mina " << "("<<mine.x<<","<<mine.y<<") na posicao: "<< "("<<neighboor_pos.x<<","<<neighboor_pos.y<<")" << std::endl;

            squareInCamp& neighboor = camp[neighboor_pos.y][neighboor_pos.x];

            if(neighboor.value == 'M') continue;
            camp[neighboor_pos.y][neighboor_pos.x].value += 1;
        }

    }
}

void Minecamp::show_minecamp()
{
    for(size_t y = 0; y < size; ++y)
    {
        for(size_t x = 0; x < size; ++x)
        {    
            std::cout << camp[y][x].get_value() << " ";
        }
        std::cout << std::endl;
    }
}

void Minecamp::xray_minecamp()
{
    for(size_t y = 0; y < size; ++y)
    {
        for(size_t x = 0; x < size; ++x)
        {    
            std::cout << camp[y][x].value << " ";
        }
        std::cout << std::endl;
    }
}

int Minecamp::get_size()
{
    return size;
}