/**
* @date [10/30/2024]
 * @author [Farhana Sultana]
 */
#include "Kitchen.hpp"

/**
 * @brief Constructs a new Kitchen object.
 * 
 * Initializes a new instance of the Kitchen class, which inherits from ArrayBag<Dish*>.
 * The constructor sets the total preparation time and the count of elaborate dishes to zero.
 */
Kitchen::Kitchen() : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {}


/**
 * @brief Converts a string representation of a serving style to its corresponding enum value.
 * 
 * This function takes a string input and returns the corresponding 
 * Appetizer::ServingStyle enum value. If the input string does not match 
 * any known serving style, it defaults to Appetizer::PLATED.
 * 
 * @param str The string representation of the serving style.
 *            Expected values are "PLATED", "BUFFET", or "FAMILY_STYLE".
 * @return Appetizer::ServingStyle The corresponding enum value for the given string.
 *         Defaults to Appetizer::PLATED if the input string does not match any known serving style.
 */
Appetizer::ServingStyle stringToServingStyle(const std::string& str) {
    if (str == "PLATED") return Appetizer::PLATED;
    if (str == "BUFFET") return Appetizer::BUFFET;
    if (str == "FAMILY_STYLE") return Appetizer::FAMILY_STYLE;
    return Appetizer::PLATED;  // default
}

/**
 * @brief Converts a string representation of a cooking method to its corresponding enum value.
 *
 * This function takes a string input representing a cooking method and returns the corresponding
 * enum value from the MainCourse::CookingMethod enumeration. If the input string does not match
 * any known cooking method, the function defaults to returning MainCourse::GRILLED.
 *
 * @param str The string representation of the cooking method.
 *            Possible values are: "GRILLED", "BAKED", "BOILED", "FRIED", "STEAMED", "RAW".
 * @return MainCourse::CookingMethod The corresponding enum value for the given string.
 */
MainCourse::CookingMethod stringToCookingMethod(const std::string& str) {
    if (str == "GRILLED") return MainCourse::GRILLED;
    if (str == "BAKED") return MainCourse::BAKED;
    if (str == "BOILED") return MainCourse::BOILED;
    if (str == "FRIED") return MainCourse::FRIED;
    if (str == "STEAMED") return MainCourse::STEAMED;
    if (str == "RAW") return MainCourse::RAW;
    return MainCourse::GRILLED;  // default
}


/**
 * @brief Converts a string representation of a flavor profile to its corresponding Dessert::FlavorProfile enum value.
 * 
 * @param str The string representation of the flavor profile. Expected values are "SWEET", "BITTER", "SOUR", "SALTY", or "UMAMI".
 * @return Dessert::FlavorProfile The corresponding Dessert::FlavorProfile enum value. Defaults to Dessert::SWEET if the input string does not match any known flavor profile.
 */
Dessert::FlavorProfile stringToFlavorProfile(const std::string& str) {
    if (str == "SWEET") return Dessert::SWEET;
    if (str == "BITTER") return Dessert::BITTER;
    if (str == "SOUR") return Dessert::SOUR;
    if (str == "SALTY") return Dessert::SALTY;
    if (str == "UMAMI") return Dessert::UMAMI;
    return Dessert::SWEET;  // default
}

/**
* Parameterized constructor.
* @param filename The name of the input CSV file containing dish
information.
* @pre The CSV file must be properly formatted.
* @post Initializes the kitchen by reading dishes from the CSV file and
storing them as `Dish*`.
*/
Kitchen::Kitchen(const std::string& filename) : Kitchen() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        try {
            std::vector<std::string> tokens = split(line, ',');
            if (tokens.size() < 7) continue;  

            std::string dish_type = tokens[0];
            std::string name = tokens[1];
            std::vector<std::string> ingredients = split(tokens[2], ';');
            int prep_time = std::stoi(tokens[3]);
            double price = std::stod(tokens[4]);
            Dish::CuisineType cuisine_type = stringToCuisineType(tokens[5]);
            std::vector<std::string> additional_attrs = split(tokens[6], ';');

            Dish* dish = nullptr;

            if (dish_type == "APPETIZER") {
                Appetizer::ServingStyle serving_style = stringToServingStyle(additional_attrs[0]);
                int spiciness = std::stoi(additional_attrs[1]);
                bool vegetarian = additional_attrs[2] == "true";
                dish = new Appetizer(name, ingredients, prep_time, price, cuisine_type, 
                                   serving_style, spiciness, vegetarian);
            }
            else if (dish_type == "MAINCOURSE") {
                MainCourse::CookingMethod cooking_method = stringToCookingMethod(additional_attrs[0]);
                std::string protein = additional_attrs[1];
                bool gluten_free = additional_attrs[2] == "true";
                std::vector<MainCourse::SideDish> sides;
                dish = new MainCourse(name, ingredients, prep_time, price, cuisine_type, 
                                    cooking_method, protein, sides, gluten_free);
            }
            else if (dish_type == "DESSERT") {
                Dessert::FlavorProfile flavor = stringToFlavorProfile(additional_attrs[0]);
                int sweetness = std::stoi(additional_attrs[1]);
                bool contains_nuts = additional_attrs[2] == "true";
                dish = new Dessert(name, ingredients, prep_time, price, cuisine_type, 
                                 flavor, sweetness, contains_nuts);
            }

            if (dish != nullptr) {
                newOrder(dish);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << "\nError: " << e.what() << std::endl;
            continue;
        }
    }
    file.close();
}


/**
 * @brief Destructor for the Kitchen class.
 *
 * This destructor is responsible for cleaning up dynamically allocated
 * memory for dishes stored in the Kitchen. It iterates through all
 * the dishes and deletes each one to prevent memory leaks.
 */
Kitchen::~Kitchen() {
    // Delete all dynamically allocated dishes
    for (int i = 0; i < getCurrentSize(); i++) {
        delete items_[i];
    }
}

/**
 * @brief Adds a new dish to the kitchen's order list and updates preparation statistics.
 * 
 * This function attempts to add a new dish to the kitchen's order list. If the dish is 
 * successfully added, it updates the total preparation time and increments the count of 
 * elaborate dishes if the dish meets certain criteria.
 * 
 * @param new_dish A pointer to the Dish object representing the new dish to be added.
 * @return true if the dish was successfully added to the order list, false otherwise.
 */
bool Kitchen::newOrder(Dish* new_dish) {
    if (add(new_dish)) {
        total_prep_time_ += new_dish->getPrepTime();
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60) {
            count_elaborate_++;
        }
        return true;
    }
    return false;
}

/**
 * @brief Serves a dish by removing it from the kitchen's list of dishes.
 *
 * This function searches for the specified dish in the kitchen's list of dishes.
 * If the dish is found, it is removed from the list, its preparation time is
 * subtracted from the total preparation time, and if it meets certain criteria
 * (having 5 or more ingredients and a preparation time of 60 minutes or more),
 * the count of elaborate dishes is decremented. The memory allocated for the
 * dish is also freed.
 *
 * @param dish_to_remove A pointer to the dish to be removed.
 * @return true if the dish was successfully removed, false if the dish was not found.
 */
bool Kitchen::serveDish(const Dish* dish_to_remove) {
    if (getCurrentSize() == 0) return false;

    for (int i = 0; i < getCurrentSize(); i++) {
        if (*items_[i] == *dish_to_remove) {
            total_prep_time_ -= items_[i]->getPrepTime();
            if (items_[i]->getIngredients().size() >= 5 && items_[i]->getPrepTime() >= 60) {
                count_elaborate_--;
            }
            delete items_[i];  // Free the memory
            remove(items_[i]);
            return true;
        }
    }
    return false;
}

/**
 * @brief Adjusts the dietary accommodations for all dishes in the kitchen based on the given dietary request.
 * 
 * This function iterates through all the dishes currently in the kitchen and applies the specified dietary 
 * accommodations to each dish.
 * 
 * @param request A reference to a DietaryRequest object that specifies the dietary accommodations to be applied.
 */
void Kitchen::dietaryAdjustment(const Dish::DietaryRequest& request) {
    for (int i = 0; i < getCurrentSize(); i++) {
        items_[i]->dietaryAccommodations(request);
    }
}

/**
 * @brief Displays the menu items in the kitchen.
 * 
 * This function iterates through the list of menu items and calls the display
 * method on each item to print its details. A blank line is added between each
 * dish for better readability.
 */
void Kitchen::displayMenu() const {
    for (int i = 0; i < getCurrentSize(); i++) {
        items_[i]->display();
        std::cout << "\n";  // Add blank line between dishes
    }
}

/**
 * @brief Splits a given string into a vector of substrings based on a specified delimiter.
 * 
 * This function takes a string and a delimiter character, and splits the string into
 * substrings wherever the delimiter character is found. The substrings are stored in
 * a vector and returned.
 * 
 * @param str The string to be split.
 * @param delimiter The character used to split the string.
 * @return std::vector<std::string> A vector containing the substrings obtained by splitting the input string.
 */
std::vector<std::string> Kitchen::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * @brief Converts a string representation of a cuisine type to its corresponding enum value.
 * 
 * @param str The string representation of the cuisine type.
 *            Expected values are "ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH".
 * @return Dish::CuisineType The corresponding enum value of the cuisine type.
 *         Returns Dish::OTHER if the string does not match any known cuisine type.
 */
Dish::CuisineType Kitchen::stringToCuisineType(const std::string& str) const {
    if (str == "ITALIAN") return Dish::ITALIAN;
    if (str == "MEXICAN") return Dish::MEXICAN;
    if (str == "CHINESE") return Dish::CHINESE;
    if (str == "INDIAN") return Dish::INDIAN;
    if (str == "AMERICAN") return Dish::AMERICAN;
    if (str == "FRENCH") return Dish::FRENCH;
    return Dish::OTHER;
}


/**
 * @brief Calculates the total preparation time for all items in the kitchen.
 * 
 * This function returns the sum of the preparation times for all items currently
 * in the kitchen. If there are no items, it returns 0.
 * 
 * @return int The total preparation time. Returns 0 if there are no items.
 */
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}

/**
 * @brief Calculates the average preparation time of items in the kitchen.
 * 
 * This function computes the average preparation time of all items currently
 * in the kitchen. If there are no items, it returns 0. The preparation time
 * is rounded to the nearest integer.
 * 
 * @return int The average preparation time of items, rounded to the nearest integer.
 */
int Kitchen::calculateAvgPrepTime() const {
    if (getCurrentSize() == 0) {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++) {
        total_prep_time_ += items_[i]->getPrepTime();  // Using -> instead of .
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    return round(total_prep_time_);
}

/**
 * @brief Returns the count of elaborate dishes.
 * 
 * This function checks if the current size of the kitchen or the count of elaborate dishes is zero.
 * If either is zero, it returns 0. Otherwise, it returns the count of elaborate dishes.
 * 
 * @return int The count of elaborate dishes.
 */
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}

/**
 * @brief Calculates the percentage of elaborate dishes in the kitchen.
 * 
 * This function computes the percentage of elaborate dishes based on the 
 * current size of the kitchen and the count of elaborate dishes. If the 
 * current size or the count of elaborate dishes is zero, the function 
 * returns 0. Otherwise, it returns the percentage of elaborate dishes 
 * rounded to two decimal places.
 * 
 * @return double The percentage of elaborate dishes in the kitchen.
 */
double Kitchen::calculateElaboratePercentage() const
{
    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}

/**
 * @brief Tally the number of items of a specific cuisine type in the kitchen.
 * 
 * This function iterates through all items in the kitchen and counts how many
 * of them match the specified cuisine type.
 * 
 * @param cuisine_type The type of cuisine to tally.
 * @return int The number of items that match the specified cuisine type.
 */
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const {
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++) {
        if (items_[i]->getCuisineType() == cuisine_type) {  // Using -> instead of .
            count++;
        }
    }
    return count;
}


/**
 * @brief Releases and serves dishes with preparation time below the specified threshold.
 *
 * This function iterates through the list of dishes in the kitchen and serves those
 * whose preparation time is less than the given `prep_time`. It counts and returns
 * the number of dishes that were served.
 *
 * @param prep_time The maximum preparation time threshold for serving dishes.
 * @return The number of dishes served that have a preparation time below the specified threshold.
 */
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time) {
    int count = 0;
    int num = getCurrentSize();
    for (int i = 0; i < num; i++) {
        if (items_[i]->getPrepTime() < prep_time) {  // Using -> instead of .
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

/**
 * @brief Releases and serves all dishes of a specified cuisine type.
 *
 * This function iterates through the list of dishes in the kitchen and serves
 * all dishes that match the specified cuisine type. It counts the number of 
 * dishes served and returns this count.
 *
 * @param cuisine_type The type of cuisine to filter dishes by.
 * @return The number of dishes served that match the specified cuisine type.
 */
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type) {
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++) {
        if (items_[i]->getCuisineType() == cuisine_type) {  // Using -> instead of .
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}


/**
 * @brief Generates a report of the kitchen's performance.
 * 
 * This function outputs the tally of different cuisine types prepared in the kitchen,
 * the average preparation time, and the percentage of elaborate dishes.
 * 
 * Cuisine types reported:
 * - ITALIAN
 * - MEXICAN
 * - CHINESE
 * - INDIAN
 * - AMERICAN
 * - FRENCH
 * - OTHER
 * 
 * The report includes:
 * - The count of each cuisine type.
 * - The average preparation time of all dishes.
 * - The percentage of elaborate dishes.
 * 
 * @note This function assumes the existence of the following member functions:
 * - tallyCuisineTypes(const std::string& cuisineType): Returns the count of dishes for the given cuisine type.
 * - calculateAvgPrepTime(): Returns the average preparation time of all dishes.
 * - calculateElaboratePercentage(): Returns the percentage of elaborate dishes.
 */
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}
