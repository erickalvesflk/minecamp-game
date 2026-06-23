#include <iostream>
#include <vector>
#include <random>
#include "minecamp.hpp"

Minecamp::Minecamp(size_t size, unsigned int mine_quant)
{   
    this->size = size;
    this->mine_quant = mine_quant;
    this->total_flags = mine_quant;

    std::uniform_int_distribution<int> dm(0,size-1);
    this->dist_mines = dm;

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
    std::vector<pos> neighboors {};
    
        for(int y_pos = -1; y_pos <= 1; ++y_pos){
            for(int x_pos = -1; x_pos <= 1; ++x_pos)
            {   
                if(y_pos == 0 and x_pos == 0) continue;
                neighboors.push_back(pos::new_pos(position.x+x_pos,position.y+y_pos));
            }    
        }

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
        int x = dist_mines(random_int_generator);
        int y = dist_mines(random_int_generator);

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
        mine_pos[mine_index] = pos::new_pos(x,y);
        camp[y][x].value = Elements::Mine;

        find_mine_try = 0; // Reseta o contador de tentativas de encontrar uma mina (contador para impedir um loop infinito)
        
    }
    // Update mine's neighboors
    for(pos mine : mine_pos)
    {
        std::vector<pos> neighboors_pos = get_neighboors(mine);
        std::cout <<"x: "<< mine.x << " y: " << mine.y << std::endl;
        for(pos neighboor_pos : neighboors_pos)
        {
            std::cout <<"x: "<< neighboor_pos.x << " y: " << neighboor_pos.y << std::endl;
            squareInCamp& neighboor = camp[neighboor_pos.y][neighboor_pos.x];
            
            if(neighboor.value == Elements::Mine) continue;
            camp[neighboor_pos.y][neighboor_pos.x].value += 1;          
        }
    }
    
    step(find_safe_pos()); // Gera um local seguro para iniciar.
}

// VIZUALIZAÇÃO

void Minecamp::build_minecamp(std::string value_type)
{   
    
    std::cout<< "     |"; // build x axis
    for(size_t x = 0; x < size; ++x)
    {
        std::string str_cod = std::to_string(x + 1);
        std::cout << str_cod.insert(0,3 - str_cod.length(), ' ') << " |";
    }
    std::cout<< std::endl;
    std::cout<< "-----  "; // build decotarion for x axis
    for(size_t x = 0; x < size; ++x)
    {
        std::cout << " :   ";
    }
    std::cout<< std::endl;

    for(size_t y = 0; y < size; ++y){

        std::string str_cod = std::to_string(y + 1); // build y axis
        std::cout << str_cod.insert(0,5 - str_cod.length(), ' ') << " - ";

        for(size_t x = 0; x < size; ++x) // Build Squares
        {    
            char value = value_type == "xray" ? camp[y][x].value : camp[y][x].get_value();
            std::cout << value << "    ";
        }
        std::cout<< std::endl;
        std::cout << "-----";
        for(size_t x = 0; x < size; ++x) // Build Line
        {    
            std::cout << "     ";
        }
        if (size/(y+1) == 2 and (not saw_info)) // Meio
        {
            std::cout << "   FLAGS: " << total_flags << " - Mines: " << total_flags << " of " << mine_quant;
            saw_info = true;
        }
        std::cout << std::endl;
    }
}

void Minecamp::show_minecamp()
{   
    build_minecamp("show");
}
void Minecamp::xray_minecamp()
{
    build_minecamp("xray");
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

bool Minecamp::flag(pos position)
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

    return check_guesses();
}

void Minecamp::recursive_safe(pos position){
    std::vector<pos> neighboors = get_neighboors(position);

    for(pos neighboor_pos : neighboors){
        squareInCamp& neighboor = camp[neighboor_pos.y][neighboor_pos.x];
        if((neighboor.value == Elements::Safe or neighboor.value == '1') and neighboor.hidden)
        {   
            neighboor.hidden = false;
            recursive_safe(neighboor_pos);
        }
    }
}

squareInCamp Minecamp::step(pos position)
{   
    squareInCamp& square = camp[position.y][position.x];
    if(square.hidden)
    {
        square.hidden = false;
    
        if(square.value == Elements::Safe)
        {
            recursive_safe(position);
        }
    }
    return square;
}

pos Minecamp::find_safe_pos()
{

    std::vector<pos> candidates;
    for(size_t x = 0; x < size; ++x){
        for(size_t y = 0; y < size; ++y)
        {
            if (camp[y][x].value == Elements::Safe)
            {
                candidates.push_back(pos::new_pos(x,y));
            }
        }
    }

    std::uniform_int_distribution<int> choice_dist(0,candidates.size()-1);
    int index_choiced = choice_dist(random_int_generator);

    std::cout << "Chegou aqui!" << std::endl;
    
    return candidates[index_choiced];
}