/**
* @date [10/30/2024]
 * @author [Farhana Sultana]
 */
#include "MainCourse.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}


/**
* Displays the main course's details.
* @post Outputs the main course's details, including name, ingredients,
preparation time, price, cuisine type, cooking method, protein type,
side dishes, and gluten-free status to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
* Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
* Side Dishes: [Side dish name] (Category: [Category: e.g., Starches,
Vegetables])
* Gluten-Free: [Yes/No]
*/
void MainCourse::display() const {
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
    
    // Convert cooking method to string
    std::string method;
    switch (cooking_method_) {
        case GRILLED: method = "Grilled"; break;
        case BAKED: method = "Baked"; break;
        case BOILED: method = "Boiled"; break;
        case FRIED: method = "Fried"; break;
        case STEAMED: method = "Steamed"; break;
        case RAW: method = "Raw"; break;
    }
    std::cout << "Cooking Method: " << method << std::endl;
    std::cout << "Protein Type: " << protein_type_ << std::endl;
    
    // Display side dishes with their categories
    std::cout << "Side Dishes:";
    if (side_dishes_.empty()) {
        std::cout << " None";
    }
    for (const auto& side : side_dishes_) {
        std::string category;
        switch (side.category) {
            case GRAIN: category = "Grain"; break;
            case PASTA: category = "Pasta"; break;
            case LEGUME: category = "Legume"; break;
            case BREAD: category = "Bread"; break;
            case SALAD: category = "Salad"; break;
            case SOUP: category = "Soup"; break;
            case STARCHES: category = "Starches"; break;
            case VEGETABLE: category = "Vegetable"; break;
        }
        std::cout << "\n" << side.name << " (Category: " << category << ")";
    }
    std::cout << std::endl;
    std::cout << "Gluten-Free: " << (gluten_free_ ? "Yes" : "No") << std::endl;
}


/**
* Modifies the main course based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the main course's attributes to meet the specified
dietary needs.
* - If `request.vegetarian` is true:
* - Changes `protein_type_` to "Tofu".
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.vegan` is true:
* - Changes `protein_type_` to "Tofu".
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
* - If `request.gluten_free` is true:
* - Sets `gluten_free_` to true.
* - Removes side dishes from `side_dishes_` whose category
involves gluten.
* Gluten-containing side dish categories are: `GRAIN`,
`PASTA`, `BREAD`, `STARCHES`.
*/
void MainCourse::dietaryAccommodations(const DietaryRequest& request) {
    if (request.vegetarian) {
        protein_type_ = "Tofu";
        std::vector<std::string> non_vegetarian = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        bool used_beans = false;
        bool used_mushrooms = false;
        
        std::vector<std::string> new_ingredients;
        for (const auto& ingredient : getIngredients()) {
            bool is_non_veg = false;
            for (const auto& non_veg : non_vegetarian) {
                if (ingredient == non_veg) {
                    is_non_veg = true;
                    if (!used_beans) {
                        new_ingredients.push_back("Beans");
                        used_beans = true;
                    } else if (!used_mushrooms) {
                        new_ingredients.push_back("Mushrooms");
                        used_mushrooms = true;
                    }
                    break;
                }
            }
            if (!is_non_veg) {
                new_ingredients.push_back(ingredient);
            }
        }
        setIngredients(new_ingredients);
    }
    
    if (request.vegan) {
        protein_type_ = "Tofu";
        std::vector<std::string> dairy_and_eggs = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"};
        
        std::vector<std::string> new_ingredients;
        for (const auto& ingredient : getIngredients()) {
            bool is_dairy_or_egg = false;
            for (const auto& dairy : dairy_and_eggs) {
                if (ingredient == dairy) {
                    is_dairy_or_egg = true;
                    break;
                }
            }
            if (!is_dairy_or_egg) {
                new_ingredients.push_back(ingredient);
            }
        }
        setIngredients(new_ingredients);
    }
    
    if (request.gluten_free) {
        gluten_free_ = true;
        
        // Remove side dishes with gluten-containing categories
        std::vector<SideDish> new_side_dishes;
        for (const auto& side : side_dishes_) {
            if (side.category != GRAIN && side.category != PASTA && 
                side.category != BREAD && side.category != STARCHES) {
                new_side_dishes.push_back(side);
            }
        }
        side_dishes_ = new_side_dishes;
    }
}
