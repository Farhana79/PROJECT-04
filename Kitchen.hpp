#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Kitchen : public ArrayBag<Dish*> {
    public:
        /**
         * Default constructor
         */
        Kitchen();

        /**
         * Parameterized constructor.
         * @param filename The name of the input CSV file containing dish information.
         * @pre The CSV file must be properly formatted.
         * @post Initializes the kitchen by reading dishes from the CSV file and storing them as Dish*.
         */
        Kitchen(const std::string& filename);

        /**
         * Destructor.
         * @post Deallocates all dynamically allocated dishes to prevent memory leaks.
         */
        ~Kitchen();

        bool newOrder(Dish* new_dish);
        bool serveDish(const Dish* dish_to_remove);
        int getPrepTimeSum() const;
        int calculateAvgPrepTime() const;
        int elaborateDishCount() const;
        double calculateElaboratePercentage() const;
        int tallyCuisineTypes(const std::string& cuisine_type) const;
        int releaseDishesBelowPrepTime(const int& prep_time);
        int releaseDishesOfCuisineType(const std::string& cuisine_type);
        void kitchenReport() const;

        /**
         * Adjusts all dishes in the kitchen based on the specified dietary accommodation.
         * @param request A DietaryRequest structure specifying the dietary accommodations.
         * @post Calls the dietaryAccommodations() method on each dish in the kitchen to adjust them accordingly.
         */
        void dietaryAdjustment(const Dish::DietaryRequest& request);

        /**
         * Displays all dishes currently in the kitchen.
         * @post Calls the display() method of each dish.
         */
        void displayMenu() const;

    private:
        int total_prep_time_;
        int count_elaborate_;

        /**
         * Helper function to split a string by delimiter
         */
        std::vector<std::string> split(const std::string& str, char delimiter) const;

        /**
         * Helper function to convert string to CuisineType
         */
        Dish::CuisineType stringToCuisineType(const std::string& str) const;
};

#endif // KITCHEN_HPP
