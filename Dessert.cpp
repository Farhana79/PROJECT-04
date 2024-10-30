/**
* @date [10/30/2024]
 * @author [Farhana Sultana]
 */
#include "Dessert.hpp"
#include <iomanip>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert()
    : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts)
    : Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(const FlavorProfile &flavor_profile) {
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(const int &sweetness_level) {
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */
int Dessert::getSweetnessLevel() const {
    return sweetness_level_;
}

/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(const bool &contains_nuts) {
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */
bool Dessert::containsNuts() const {
    return contains_nuts_;
}


/**
* Displays the dessert's details.
* @post Outputs the dessert's details, including name, ingredients,
preparation time, price, cuisine type, flavor profile, sweetness level, and
whether it contains nuts.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
Note for all subclasses: When multiple ingredients are removed, at most two replacement
ingredients should be added, and they should replace the first and second (when applicable)
occurrences of the ingredients to be removed.
Step 3: Modify the Kitchen Class
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Flavor Profile: [Flavor profile: Sweet, Bitter, Sour, Salty, or Umami]
* Sweetness Level: [Sweetness level]
* Contains Nuts: [Yes/No]
*/
void Dessert::display() const {
    std::cout << "Dish Name: " << getName() << std::endl;
    std::cout << "Ingredients: ";
    const auto& ingredients = getIngredients();
    for (size_t i = 0; i < ingredients.size(); ++i) {
        std::cout << ingredients[i];
        if (i != ingredients.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;
    
    // Convert flavor profile to string
    std::string flavor;
    switch (flavor_profile_) {
        case SWEET: flavor = "Sweet"; break;
        case BITTER: flavor = "Bitter"; break;
        case SOUR: flavor = "Sour"; break;
        case SALTY: flavor = "Salty"; break;
        case UMAMI: flavor = "Umami"; break;
    }
    std::cout << "Flavor Profile: " << flavor << std::endl;
    std::cout << "Sweetness Level: " << sweetness_level_ << std::endl;
    std::cout << "Contains Nuts: " << (contains_nuts_ ? "Yes" : "No") << std::endl;
}

/**
* Modifies the dessert based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the dessert's attributes to meet the specified dietary
needs.
* - If `request.nut_free` is true:
* - Sets `contains_nuts_` to false.
* - Removes nuts from `ingredients_`.
* Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
"Peanuts", "Cashews", "Pistachios".
* - If `request.low_sugar` is true:
* - Reduces `sweetness_level_` by 3 (minimum of 0).
* - If `request.vegan` is true:
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
*/
void Dessert::dietaryAccommodations(const DietaryRequest& request) {
    std::vector<std::string> new_ingredients;
    bool need_update = false;

    std::vector<std::string> current_ingredients = getIngredients();

    if (request.nut_free) {
        contains_nuts_ = false;
        std::vector<std::string> nuts = {"Almonds", "Walnuts", "Pecans", "Hazelnuts", 
                                       "Peanuts", "Cashews", "Pistachios"};
        
        for (const auto& ingredient : current_ingredients) {
            bool is_nut = false;
            for (const auto& nut : nuts) {
                if (ingredient == nut) {
                    is_nut = true;
                    break;
                }
            }
            if (!is_nut) {
                new_ingredients.push_back(ingredient);
            }
        }
        need_update = true;
    }

    if (request.low_sugar) {
        sweetness_level_ = std::max(0, sweetness_level_ - 3);
    }

    if (request.vegan) {
        std::vector<std::string> dairy_and_eggs = {"Milk", "Eggs", "Cheese", 
                                                  "Butter", "Cream", "Yogurt"};
        
        new_ingredients.clear();  // Clear in case it was modified by nut_free
        bool used_first_replacement = false;
        bool used_second_replacement = false;

        for (const auto& ingredient : (need_update ? new_ingredients : current_ingredients)) {
            bool is_dairy_or_egg = false;
            for (const auto& dairy : dairy_and_eggs) {
                if (ingredient == dairy) {
                    is_dairy_or_egg = true;
                    if (!used_first_replacement) {
                        new_ingredients.push_back("Almond Milk");
                        used_first_replacement = true;
                    } else if (!used_second_replacement) {
                        new_ingredients.push_back("Flax Egg");
                        used_second_replacement = true;
                    }
                    break;
                }
            }
            if (!is_dairy_or_egg) {
                new_ingredients.push_back(ingredient);
            }
        }
        need_update = true;
    }

    // Update ingredients if any changes were made
    if (need_update) {
        setIngredients(new_ingredients);
    }
}
