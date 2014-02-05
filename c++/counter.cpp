#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>
//#include <hash_map>
//#include <google/sparse_hash_map>
#include <unordered_map>
#include "sortedArray.hh"
#include "FileParser.hh"

//using namespace std;
//using google::sparse_hash_map;


struct eqstr
{
    bool operator()(const std::string s1, const std::string s2) const
    {
        return (s1 == s2);
    }
};

class Manager {
public:

    Manager(std::string myFileName) : m_fileName(myFileName) {};
    void GetTaskDefinition(void);
    void MakeDecision(void);
    void Execute(void) {FileParser myFileParser; myFileParser.ReadAndParseTheFile();}

private:

    std::string m_fileName;
    size_t m_sizeOfTheFile;
    unsigned int m_threadValue;
    unsigned int m_tasks;
};

void Manager::GetTaskDefinition(void)
{
    std::streampos begin,end;
    std::ifstream myfile (m_fileName);
    begin = myfile.tellg();
    myfile.seekg (0, std::ios::end);
    end = myfile.tellg();
    myfile.close();
    size_t m_sizeOfTheFile = end-begin;
    m_threadValue = 16;
    m_tasks = m_sizeOfTheFile/m_threadValue;
    std::cout << m_fileName << ":" << m_sizeOfTheFile << "\n";
}


int main()
{
    
    Manager myManager("toto.txt");
    myManager.GetTaskDefinition();
    SortedArray<int>  my_array;
    
    my_array.m_array[0] = -1;
    my_array.m_array[1] = -5;
    my_array.m_array[2] = 18;
    my_array.m_array[3] = 7;
    my_array.m_array[4] = 0;

    my_array.printArray();
    my_array.qsort(0, SortedArray<int>::m_sizeofTheArray-1);
    my_array.printArray();
    
    return 0;
}
