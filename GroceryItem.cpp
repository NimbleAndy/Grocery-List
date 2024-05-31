#include "GroceryItem.h"

GroceryItem::GroceryItem()
  : item_name(), item_price(), quantity_on_hand(), qty_purchased()
{
}

void GroceryItem::set_item_name(std::string name)
{
  item_name = name;
}

void GroceryItem::set_item_price(double price)
{
  item_price = price;
}

void GroceryItem::set_qty_on_hand(int quantity)
{
  quantity_on_hand = quantity;
}

void GroceryItem::set_qty_purchased(int quantity)
{
  qty_purchased = quantity;
}

std::string GroceryItem::get_item_name() const
{
  return item_name;
}

double GroceryItem::get_item_price() const
{
  return item_price;
}

int GroceryItem::get_qty_on_hand() const
{
  return quantity_on_hand;
}

int GroceryItem::get_qty_purchased() const
{
  return qty_purchased;
}
