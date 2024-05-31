#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

#include "GroceryItem.h"

#define GROCECY_ITEM_COUNT 10
#define EXIT_CHOICE 11

GroceryItem read_grocery_item(std::istream& input_stream)
{
  std::string item_name;
  std::getline(input_stream, item_name);
  double price;
  input_stream >> price;
  int quantity_on_hand;
  input_stream >> quantity_on_hand;
  input_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  GroceryItem grocery_item;

  if (!input_stream && !input_stream.eof()) {
    return grocery_item;
  }

  grocery_item.set_item_name(item_name);
  grocery_item.set_item_price(price);
  grocery_item.set_qty_on_hand(quantity_on_hand);
  grocery_item.set_qty_purchased(0);
  return grocery_item;
}

void display_menu(GroceryItem* grocery_items)
{
  for (int i = 0; i < GROCECY_ITEM_COUNT; ++i) {
    std::cout << std::setw(2) << std::right << (i + 1) << ": " << std::setw(16)
              << std::left << grocery_items[i].get_item_name()
              << " price: " << std::showbase
              << std::put_money(grocery_items[i].get_item_price() * 100.0)
              << " quantity: " << std::setw(4)
              << grocery_items[i].get_qty_on_hand()
              << " purchased: " << std::setw(4)
              << grocery_items[i].get_qty_purchased() << '\n';
  }

  std::cout << std::setw(2) << std::right << EXIT_CHOICE << ": Exit\n";
}

int read_menu_choice()
{
  int index = -1;

  while (!(std::cin >> index) || (index < 1 || index > EXIT_CHOICE)) {
    std::cout << "Invalid input, please try again: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (index == EXIT_CHOICE) {
    return EXIT_CHOICE;
  }

  return index - 1; // Convert to 0-based indexing.
}

int ask_for_quantity(const GroceryItem& grocery_item)
{
  std::cout << "How many of " << grocery_item.get_item_name()
            << " do you want? (" << grocery_item.get_qty_on_hand()
            << " available) ";

  int quantity = -1;

  while (!(std::cin >> quantity)
         || ((quantity < 0) || (quantity > grocery_item.get_qty_on_hand()))) {
    std::cout << "Invalid input, please try again: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return quantity;
}

int main()
{
  std::cout.imbue(std::locale("en_US.UTF-8"));
  GroceryItem grocery_items[GROCECY_ITEM_COUNT];

  const std::string file_name = "grocerylist.dat";
  std::ifstream     input_file_stream(file_name);

  if (!input_file_stream) {
    std::cerr << "Couldn't open " << file_name << "!\n";
    return 1;
  }

  for (int i = 0; (i < GROCECY_ITEM_COUNT) && input_file_stream; ++i) {
    grocery_items[i] = read_grocery_item(input_file_stream);
  }

  while (true) {
    display_menu(grocery_items);
    std::cout << "Your order please: ";
    const int user_choice = read_menu_choice();

    if (user_choice == EXIT_CHOICE) {
      double total_price = 0.0;
      std::cout << "\nHere's your bill:\n";

      for (int i = 0; i < GROCECY_ITEM_COUNT; ++i) {
        if (grocery_items[i].get_qty_purchased() != 0) {
          std::cout << '"' << grocery_items[i].get_item_name()
                    << "\", quantity to purchase: "
                    << grocery_items[i].get_qty_purchased()
                    << ", price per unit: " << std::showbase
                    << std::put_money(grocery_items[i].get_item_price() * 100.0)
                    << ", subtotal: " << std::showbase
                    << std::put_money(
                         (grocery_items[i].get_qty_purchased()
                          * grocery_items[i].get_item_price())
                         * 100.0)
                    << '\n';
          total_price
            += (grocery_items[i].get_qty_purchased() * grocery_items[i].get_item_price());
        }
      }

      std::cout << "Total: " << std::showbase
                << std::put_money(total_price * 100.0) << '\n';

      std::cout << "\nThe order will be delivered by the end of the day.\n";
      return 0;
    }

    const int quantity = ask_for_quantity(grocery_items[user_choice]);
    grocery_items[user_choice].set_qty_purchased(
      grocery_items[user_choice].get_qty_purchased() + quantity);
    grocery_items[user_choice].set_qty_on_hand(
      grocery_items[user_choice].get_qty_on_hand() - quantity);
  }
}
