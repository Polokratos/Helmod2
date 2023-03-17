#ifndef HELMOD_RECIPE_HPP
#define HELMOD_RECIPE_HPP
#endif

#include <unordered_map>
#include <iostream>

#include"nlohmann/json.hpp"
using json = nlohmann::json;
#include "Ingredient.hpp"

class Recipe
{
private:
    /**
     * Change in stock after 1 production cycle.
     * if delta["xyz"] < 0, recipe used some xyz
     * if delta["xyz"] > 0, recipe created some xyz
     * if delta["xyz"] = 0, recipe does not care for xyz
    */
    std::unordered_map<Ingredient,int> delta;
    /**
     * Time required for 1 production cycle.
    */
    double process_time;
public:
    //Explicit constructor
    Recipe(const double time,const std::unordered_map<Ingredient,int>d):delta(d){}
    //JSON object constructor
    Recipe(json builder) 
    {
        delta = builder.at("delta").get<std::unordered_map<Ingredient,int>>();
    }

    
    
};
