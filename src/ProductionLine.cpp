#include "ProductionLine.hpp"
#include <stdexcept>

std::unordered_map<std::string,ProductionLine*> ProductionLine::blocks;

//JSON object constructor
ProductionLine::ProductionLine(json builder)
{
    name = builder["name"].get<std::string>();
    delta = builder["delta"].get<std::unordered_map<std::string,double>>();
    internal = builder["internal"].get<std::unordered_map<std::string,double>>();
}

void ProductionLine::add(ProductionLine& recipe, Ingredient product, double pval)
{
    if(recipe.delta[product] == 0) throw new std::invalid_argument("Recipe linearly independent to product!");
    double scale = ((pval - delta[product]) / recipe.delta[product]); // pval = this.delta + scale * recipe.delta, solve for scale.
    internal[recipe.name] += scale;
    for (auto &&[ingredient,change] : recipe.delta)
        delta[ingredient] += change * scale;
    
}
void ProductionLine::remove(ProductionLine& recipe)
{
    for (auto &&[ingredient,change] : recipe.delta)
        delta[ingredient] -= change * internal[recipe.name];
    internal.erase(recipe.name);
}
void ProductionLine::rescale(Ingredient product, double pval)
{
    if(delta[product] == 0) throw new std::invalid_argument("Production line does not produce this ingredient, cannot rescale to fit!");
    double scale = pval / delta[product];
    for (auto &&[k,v] : internal)
        v *= scale;
    for (auto &&[k,v] : delta)
        v*= scale;
}
/*

(pval - deltaOld)/innerDelta =  scale

*/