#ifndef HELMOD_RECIPE_HPP
#define HELMOD_RECIPE_HPP
#endif

#include <vector>
#include <tuple>
#include <iostream>
#include <map>

#include"nlohmann/json.hpp"
using json = nlohmann::json;
#include "Ingredient.hpp"

class Recipe
{
private:
    std::string name; //name of recipe
    static std::map<std::string,Recipe> all_recipes; //recipes cannot be duplicative. This static map ensures this.
    /**
     * Change in stock after 1 production cycle.
     * Using a map here is unnescesary, since this object will be always read in full anyway.
    */
    std::vector<std::tuple<Ingredient,int>> delta;
    /**
     * Time required for 1 production cycle.
    */
    double process_time;

    //Each recipe is a singleton, therefore we block copy constructor and '=' operator.
    Recipe(const Recipe &tc){}
    Recipe& operator=(const Recipe &tc){}

public:
    //Explicit constructor
    Recipe(const std::string name, const double time,const std::vector<std::tuple<Ingredient,int>>d);
    //JSON object constructor
    Recipe(json builder);


    static std::map<std::string, Recipe> getAllRecipes() {return all_recipes;}
    std::vector<std::tuple<Ingredient,int>> getDelta() const {return this->delta;}
    std::string getName() const {return name;}
    double getTime() const {return process_time;}
};
