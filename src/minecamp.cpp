#include <iostream>
#include <vector>
#include "minecamp.hpp"

Minecamp::Minecamp(size_t size, unsigned int mine_quant)
{   
    this->size = size;
    this->mine_quant = mine_quant;
    this->total_flags = mine_quant;

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

std::vector<pos> Minecamp::get_neighboors(pos position)
{
    pos neighboors[8] {};
        // UP
        neighboors[0].x = position.x;
        neighboors[0].y = position.y + 1;
        // DOWN
        neighboors[1].x = position.x;
        neighboors[1].y = position.y - 1;
        // LEFT
        neighboors[2].x = position.x - 1;
        neighboors[2].y = position.y;
        // RIGHT
        neighboors[3].x = position.x + 1;
        neighboors[3].y = position.y;
        // UP-LEFT
        neighboors[4].x = position.x - 1;
        neighboors[4].y = position.y + 1;
        // UP-RIGHT
        neighboors[5].x = position.x + 1;
        neighboors[5].y = position.y + 1;
        // DOWN-LEFT
        neighboors[6].x = position.x - 1;
        neighboors[6].y = position.y - 1;
        // DOWN-RIGHT
        neighboors[7].x = position.x + 1;
        neighboors[7].y = position.y - 1;


    std::vector<pos> result = {};
    for (pos neighboor_pos : neighboors)
    {   
        // Verificação coordenada dentro do "campo" (array 2D)
        if(neighboor_pos.x < 0 or neighboor_pos.x >= size) continue;
        if(neighboor_pos.y < 0 or neighboor_pos.y >= size) continue;
        result.push_back(neighboor_pos);
    }

    return result;
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

        if(possible_mine.value == Elements::Mine)
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
        camp[y][x].value = Elements::Mine;

        find_mine_try = 0; // Reseta o contador de tentativas de encontrar uma mina (contador para impedir um loop infinito)
        
    }

    // Update mine's neighboors
    for(pos mine : mine_pos)
    {
        std::vector<pos> neighboors_pos = get_neighboors(mine);
        for(pos neighboor_pos : neighboors_pos)
        {
            squareInCamp& neighboor = camp[neighboor_pos.y][neighboor_pos.x];

            if(neighboor.value == Elements::Mine) continue;
            camp[neighboor_pos.y][neighboor_pos.x].value += 1;          
        }
    }
}

// VIZUALIZAÇÃO
void Minecamp::show_minecamp()
{
    for(size_t y = 0; y < size; ++y)
    {
        for(size_t x = 0; x < size; ++x)
        {    
            std::cout << camp[y][x].get_value() << " ";
        }
        if (size/(y+1) == 2 and (not saw_info)) // Meio
        {
            std::cout << "   FLAGS: " << total_flags << " - Mines: " << total_flags << " of " << mine_quant;
            saw_info = true;
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
int Minecamp::get_flag_quant()
{
    return total_flags;
}

bool Minecamp::check_guesses(){
    for(pos mine : mine_pos)
    {
        if(not camp[mine.y][mine.x].flaged)
        {
            return false;
        }
    }
    return true;
}

// AÇÕES

void Minecamp::flag(pos position)
{
    squareInCamp& square = camp[position.y][position.x];
    if(square.flaged)
    {
        total_flags += 1;
        square.flaged = false;
    }
    else
    {
        if(total_flags > 0){
            total_flags -= 1;
            square.flaged = true;
        }
    }
}

void Minecamp::recursive_safe(pos position){
    std::vector<pos> neighboors = get_neighboors(position);

    for(pos neighboor_pos : neighboors){
        squareInCamp& neighboor = camp[neighboor_pos.y][neighboor_pos.x];
        if(neighboor.value == '0' and neighboor.hidden)
        {   
            neighboor.hidden = false;
            recursive_safe(neighboor_pos);
        }
    }
}

char Minecamp::step(pos position)
{
    squareInCamp& square = camp[position.y][position.x];
    if(square.value == Elements::Flag) return 'F';

    square.hidden = false;
    if(square.value == Elements::Mine) return 'M';

    if(square.value == '0')
    {
        recursive_safe(position);
    }

    return '0';
}