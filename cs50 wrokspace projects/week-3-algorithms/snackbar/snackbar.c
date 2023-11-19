// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
}
menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(menu_item menus[]);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items(menu);

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
        for (int j = 0, length = strlen(menu[i].item); j < length; j++)
        {
            printf("length = %c\n", menu[i].item[j]);
            //menu[i].item[j] = tolower(menu[i].item[j]);
        }
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(menu_item menus[])
{
    menus[0].item = "Burger";
    menus[1].item = "Vegan Burger";
    menus[2].item = "Hot Dog";
    menus[3].item = "Cheese Dog";
    menus[4].item = "Fries";
    menus[5].item = "Cheese Fries";
    menus[6].item = "Cold Pressed Juice";
    menus[7].item = "Cold Brew";
    menus[8].item = "Water";
    menus[9].item = "Soda";

    menus[0].price = 9.5;
    menus[1].price = 11;
    menus[2].price = 5;
    menus[3].price = 7;
    menus[4].price = 5;
    menus[5].price = 6;
    menus[6].price = 7;
    menus[7].price = 3;
    menus[8].price = 2;
    menus[9].price = 2;

    return;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    int length_input = strlen(item);
    int length_snack;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        length_snack = strlen(menu[i].item);
        if (length_snack != length_input)
        {
            // printf("%s and %s length is not equal.\n", item, menu[i].item);
            continue;
        }
        for (int j = 0; j < length_snack; j++)
        {
            item[j] = tolower(item[j]);
            printf("%c\n", item[j]);
            if (item[j] != menu[i].item[j])
            {
                // printf("%s is not identical to %s.\n", item, menu[i].item);
                break;
            }
            if (j == length_snack - 1)
            {
                printf("Found\n");
                return menu[i].price;
            }
        }
    }
    printf("NOT FOUND\n");
    return 0.0;
}
