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
ProductionLine::ProductionLine(std::string name)
{
    this->name = name;
}
ProductionLine::~ProductionLine() noexcept
{
    delta.clear();
}

void ProductionLine::add(const ProductionLine& recipe, Ingredient product, double pval)
{
    if(recipe.delta.at(product) == 0) throw new std::invalid_argument("Recipe linearly independent to product!");
    double scale = ((pval - delta[product]) / recipe.delta.at(product)); // pval = this.delta + scale * recipe.delta, solve for scale.
    internal[recipe.name] += scale;
    for (auto &&[ingredient,change] : recipe.delta)
        delta[ingredient] += change * scale;
    
}
void ProductionLine::remove(const ProductionLine& recipe)
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

void ProductionLine::dumpInternal()
{
    for (auto &&[k,v] : internal)
        std::cout << k << " : " << v << "\n";
    
}
void ProductionLine::dumpDelta()
{
    for (auto &&[k,v] : delta)
        if (v != 0) std::cout << k << " : " << v << "\n";
} 