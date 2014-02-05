#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <unordered_map>
#include <algorithm>

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
  void ComputeBestBagBruteForce();
  void ComputeBestBag();
  void PrintChoice();
private:
  void ComputeOneCase(unsigned int members, int& weight, int& value);
  int          m_weight;
  int          m_value;
  int          m_case;
  int          m_matrix[100][100];
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
  for(int j=0;j<=m_weight;j++)
    m_matrix[0][j]=0;

  int n = m_items.size();
  
  for(int i=1;i<=n;i++)
  {
    for(int j=0;j<=m_weight;j++)
    {
      if (m_items[i].getWeight() <= j)
      {
	int v1=  m_matrix[i-1][j];
	int v2=  m_matrix[i-1][j-m_items[i-1].getWeight()];
	m_matrix[i][j] = std::max(v1,v2)+m_items[i-1].getValue();
      }
      else
      {
	m_matrix[i][j] = m_matrix[i-1][j];
      }
    }
  }

  std::cout << "Polynormal:" << m_matrix[n][m_weight];
			
}

void BackPack::ComputeBestBagBruteForce()
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
  BackPack myBackPack(15, myVector);

  std::cout << "Polynomial case------------------------------------------\n";
  myBackPack.ComputeBestBag();  
  myBackPack.PrintChoice();
  std::cout << "Brute force case------------------------------------------\n";
  myBackPack.ComputeBestBagBruteForce();  
  myBackPack.PrintChoice();
  // myVector.print();
}
