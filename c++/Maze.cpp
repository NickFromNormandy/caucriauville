#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <unordered_map>
#include <algorithm>


class Maze
{

private:

  int m_matrix[100][100];
  bool m_marked[100];
public:

  Maze(); 
  void set(int x, int y, int cost) { m_matrix[x][y]=cost;}
  bool find(int source, int final);
  void print(void);

};

Maze::Maze()
{

  for(int i=0;i<100;i++)
    {
      {
      for(int j=0;j<100;j++) 
	m_matrix[i][j]=0; 
      }
      m_marked[i]=false;
    }

};

bool Maze::find(int source, int final)
{
  m_marked[source]=true;
  if (source == final) 
    {
      std::cout << "step:" << source << "\n";
      std::cout << "we got it!\n";
      return true;
    }
  else
    {
      for(int i =0;i<100;i++)
	{
	  if (m_matrix[source][i]!=0 && m_marked[i]==false && find(i,final)==true)
	    std::cout << "step:" << source << "\n";
	    return true;
	}

      
      return false;
    }
}

void Maze::print(void)
{

}

int main()
{
  
  Maze myMaze;
  // A
  myMaze.set(0,1,1);
  myMaze.set(0,3,1);

  // B
  myMaze.set(1,0,1);
  myMaze.set(1,2,1);

  // C
  myMaze.set(2,0,1);
  myMaze.set(2,5,1);

  // D
  myMaze.set(3,0,1);
  myMaze.set(3,4,1);

  //E
  myMaze.set(4,3,1);
  
  //F
  myMaze.set(5,2,1);
  
  if (myMaze.find(0,5))
    {
      std::cout << "We got it\n";
    }
  else
    {
      std::cout << "We did not find it\n";
    }

  myMaze.print();
}
