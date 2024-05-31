#pragma once
#include <string>

class GroceryItem {
public:
  GroceryItem();

  void set_item_name(std::string name);

  void set_item_price(double price);

  void set_qty_on_hand(int quantity);

  void set_qty_purchased(int quantity);

  std::string get_item_name() const;

  double get_item_price() const;

  int get_qty_on_hand() const;

  int get_qty_purchased() const;

private:
  std::string item_name;
  double      item_price;
  int         quantity_on_hand;
  int         qty_purchased;
};
