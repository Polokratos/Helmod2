#include "Recipe.hpp"
#include <stdexcept>

Recipe::Recipe(const std::string name, const double time,const std::vector<std::tuple<Ingredient,int>>d)
{
    if(Recipe::all_recipes.find(name) != Recipe::all_recipes.end())
        throw new std::invalid_argument("Duplicative recipe!");
    this->name = name;
    this->process_time = time;
    this->delta = d;
}

Recipe::Recipe(json builder)
{
    std::vector<std::tuple<Ingredient,int>> d;
    for(auto& element : builder["delta"].items())
        d.push_back({element.key(), element.value().get<int>()});
    this->name = builder["name"];
    this->process_time = builder["time"].get<double>();
    this->delta = d;
}