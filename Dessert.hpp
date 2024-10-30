/**
* @date [10/30/2024]
 * @author [Farhana Sultana]
 */
#ifndef DESSERT_HPP
#define DESSERT_HPP

#include "Dish.hpp"
#include <string>

/**
 * @class Dessert
 * @brief Represents a dessert dish, inheriting from Dish.
 */
class Dessert : public Dish {
public:
    /**
     * @enum FlavorProfile
     * @brief Describes the dominant flavor of the dessert.
     */
    enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI };

    /**
     * Default constructor.
     * Initializes all private members with default values.
     */
    Dessert();

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
    Dessert(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts);

    void display() const override;
    void dietaryAccommodations(const DietaryRequest& request) override;
    
    /**
     * Sets the flavor profile of the dessert.
     * @param flavor_profile The new flavor profile.
     * @post Sets the private member `flavor_profile_` to the value of the parameter.
     */
    void setFlavorProfile(const FlavorProfile &flavor_profile);

    /**
     * @return The flavor profile of the dessert.
     */
    FlavorProfile getFlavorProfile() const;

    /**
     * Sets the sweetness level of the dessert.
     * @param sweetness_level An integer representing the sweetness level of the dessert.
     * @post Sets the private member `sweetness_level_` to the value of the parameter.
     */
    void setSweetnessLevel(const int &sweetness_level);

    /**
     * @return The sweetness level of the dessert.
     */
    int getSweetnessLevel() const;

    /**
     * Sets the contains_nuts flag of the dessert.
     * @param contains_nuts A boolean indicating if the dessert contains nuts.
     * @post Sets the private member `contains_nuts_` to the value of the parameter.
     */
    void setContainsNuts(const bool &contains_nuts);

    /**
     * @return True if the dessert contains nuts, false otherwise.
     */
    bool containsNuts() const;

private:
    FlavorProfile flavor_profile_; ///< The flavor profile of the dessert.
    int sweetness_level_; ///< The sweetness level of the dessert.
    bool contains_nuts_; ///< Flag indicating if the dessert contains nuts.
};

#endif // DESSERT_HPP
