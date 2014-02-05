#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <unordered_map>

class Item
{

private:
  int         m_value;
  int         m_weight;
  std::string m_name;

public:

  Item(std::string name, int weight, int value) :
    m_value(value), m_weight(weight), m_name(name) {};

  int getWeight() { return m_weight; };
  int getValue()  { return m_value; };
  std::string getName() { return m_name; };
  void print() { std::cout << "item:" << m_name << " value: $" << m_value << " weight:" << m_weight << "kg\n";};
};

class SetOfItems : public std::vector<Item> 
{
public:
  void print(void) { std::cout << "print all items\n"; for(int i=0;i<size();i++) this->operator[](i).print(); }
};

class BackPack 
{
public:
  BackPack(int weight, SetOfItems &myItems) : m_weight(weight),  m_items(myItems), m_value(0) {};
  void ComputeBestBag();
  void PrintChoice();
private:
  void ComputeOneCase(unsigned int members, int& weight, int& value);
  int          m_weight;
  int          m_value;
  int          m_case;
  SetOfItems&  m_items;
};

void BackPack::ComputeOneCase(unsigned int members, int& weight, int& value)
{
  weight = 0;
  value = 0;
  for(int i=0;i < m_items.size() && i<sizeof(members)*8;i++)
  {
    unsigned int bitmask = (1 << i);
    
    if (members & bitmask )
    {
      
      weight = weight + m_items.operator[](i).getWeight();
      value = value + m_items[i].getValue();
      
     
    }
  }
}

void BackPack::ComputeBestBag()
{
  int NumberOfItems = m_items.size();
  int choices = (1 << NumberOfItems);
  m_value =0;
  m_case=0;

  for(int i=0;i<choices;i++)
  {
    int weight=0, value=0;
    ComputeOneCase(i, weight, value);
   
    if (weight <= m_weight && value > m_value)
    {
  
      m_value = value;
      m_case = i;
    }
  }

}

void BackPack::PrintChoice()
{
  std::cout << "There was " << m_items.size() << " items\n";
  std::cout << "Max weight " << m_weight << "\n";
  std::cout << "Case " << m_case << "\n";

  //  std::cout << "Max weight " << m_weight << "\n";

  for(int i=0;i< m_items.size() && i<sizeof(m_case)*8;i++)
  {
    unsigned int bitmask = (1 << i);

    if (m_case & bitmask)
    {
      std::cout << "item nth:" << i << "\n";
      m_items[i].print();
    }

  }

}

main()
{
  SetOfItems myVector;
  myVector.push_back( Item("Gray", 1, 2));
  myVector.push_back(Item("Orange", 1, 1));
  myVector.push_back(Item("Blue", 2, 2));
  myVector.push_back(Item("Yellow", 4, 10));
  myVector.push_back(Item("Green", 12, 2));
  myVector.push_back( Item("Gray", 1, 2));
  myVector.push_back(Item("Orange", 1, 1));
  myVector.push_back(Item("Blue", 2, 2));
  myVector.push_back(Item("Yellow", 4, 10));
  myVector.push_back(Item("Green", 12, 2));
  myVector.push_back( Item("Gray", 1, 2));
  myVector.push_back(Item("Orange", 1, 1));
  myVector.push_back(Item("Blue", 2, 2));
  myVector.push_back(Item("Yellow", 4, 10));
  BackPack myBackPack(15, myVector);
  myBackPack.ComputeBestBag();  
  myBackPack.PrintChoice();
  myVector.print();
}
