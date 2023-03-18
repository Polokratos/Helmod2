#ifndef HELMOD_RECIPE_HPP
#define HELMOD_RECIPE_HPP


#include <vector>
#include <tuple>
#include <iostream>
#include <unordered_map>
#include <stdexcept>

#include"nlohmann/json.hpp"
using json = nlohmann::json;
#include "Ingredient.hpp"

class ProductionLine
{
private:
    //Each recipe is a singleton, therefore we block copy constructor and '=' operator.
    ProductionLine(const ProductionLine &tc){}
    ProductionLine& operator=(const ProductionLine &tc){}

public:
    static std::unordered_map<std::string,ProductionLine*> recipes; //recipes cannot be duplicative. This static map ensures this.
    static std::unordered_map<std::string,ProductionLine*> lines; //recipes cannot be duplicative. This static map ensures this.
    std::string name; //name of recipe
    std::unordered_map<Ingredient,double> delta;
    std::unordered_map<std::string,double> internal;

    //JSON object constructor
    ProductionLine(json builder)
    {
        name = builder["name"];
        if(recipes.find(name) != recipes.end() || lines.find(name) != lines.end())
            throw new std::runtime_error("name collision");
        delta = builder["delta"].get<std::unordered_map<std::string,double>>();
        internal = builder["internal"].get<std::unordered_map<std::string,double>>();
        internal.empty() ? recipes[name] = this : lines[name] = this;
    }

    bool isValid()
    {
        if(internal.empty()) return true; //this is a recipe. We implicitly trust recipes.
        std::unordered_map<Ingredient,double> expectedDelta; //delta should be equal to the weighted sum we wil calc here.
        for (auto &&[key,value] : internal) //for all constructing blocks
        {
            auto block = recipes.find(key);
            if(block == recipes.end()) block = lines.find(key);
            if(block == lines.end()) return false; //404 block to found
            if(!block->second->isValid()) return false; //garbage in garbage out.
            for (auto &&[dkey,dvalue] : block->second->delta)
                expectedDelta[dkey]+=dvalue;
        }
        for (auto &&[key,value] : delta)
            if(abs(expectedDelta[key] - value) > 0.001) return false;
        return true;
        
        
    }
};


#endif