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
public:
    static std::unordered_map<std::string,ProductionLine*> blocks; //recipes cannot be duplicative. This static map ensures this.
    std::string name; //name of recipe
    std::unordered_map<Ingredient,double> delta;
    std::unordered_map<std::string,double> internal;

    //JSON object constructor
    ProductionLine(json builder);
    ProductionLine(std::string name);
    ~ProductionLine();
    void add(const ProductionLine& recipe,const Ingredient product,const double pval);
    void remove(const ProductionLine& recipe);
    void rescale(const Ingredient product,const double pval);
    void dumpDelta();
    void dumpInternal();
};
#endif