#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>
//#include <hash_map>
//#include <google/sparse_hash_map>
#include <unordered_map>

//using namespace std;
//using google::sparse_hash_map;



class Lock {

public:

    virtual void lock(void) = 0 ;

    virtual void unlock(void) = 0 ;

    virtual ~Lock(void) {};

};

class LockWithMutex : public Lock {

public:

    LockWithMutex(void)  { pthread_mutex_init(&mutex, NULL); }

    virtual void lock(void)  { pthread_mutex_lock(&mutex); }

    virtual void unlock(void)  { pthread_mutex_unlock(&mutex); }

    virtual ~LockWithMutex(void) { pthread_mutex_destroy(&mutex); }

private:    

    pthread_mutex_t mutex;

};



class Counter 
{

public:

    Counter(int c)
    {
        m_value = c;
    };

    int getAndIncrement() 
    {
        m_lock.lock();
        int temp = m_value;
        sleep(0);
        m_value = temp + 1;
        m_lock.unlock();
        return temp;
    };

    void Print(void)
    {
        std::cout << "Counter:" << m_value << "\n";
    }

private:

    LockWithMutex m_lock;
    int  m_value;

};

class NickThread 
{

public:

    NickThread(void) { };

    void SetCounter(Counter *myCounter) 
    { 
        m_Counter = myCounter; 
    }

    void Start(int thread_number) 
    {
        m_thread_number = thread_number; 
        pthread_create(&m_thread, NULL,(void * (*) (void*))( &NickThread::execute), this); 
    };

    pthread_t GetID(void) { return m_thread; }
    static void *execute(void *);
    
private:
    
    Counter     *m_Counter;
    pthread_t    m_thread;
    unsigned int m_thread_number;

};



void *NickThread::execute(void *myInput) 
{ 
    NickThread *mythis = (NickThread*)myInput;   
    mythis->m_Counter->getAndIncrement();
    pthread_exit(&(mythis->m_thread_number));
};


struct eqstr
{
    bool operator()(const std::string s1, const std::string s2) const
    {
        return (s1 == s2);
    }
};

class FileParser : public NickThread
{
    typedef  std::vector<std::string> myArray_t;
    typedef  std::unordered_map <std::string, int> mymap; 
    typedef  std::unordered_map <int, myArray_t> myMapOccurenceToWord_t;

public:
    
    FileParser() {}   
    void ReadAndParseTheFile(void);
    void PrintMapWordToOccurence(void);
    void PrintMapOccurenceToWords(void);
    void tokenize(const std::string& str, myArray_t& tokens);
    void CreateOccurenceToWord(void);
    void CreateThreads(void);

private:

    static const int threadCounter =10;
    mymap  MapWordToOccurence;
    mymap::const_iterator myMapIter;
    myMapOccurenceToWord_t MapOccurenceToWord;
    NickThread myThread[threadCounter];   

};

//const int FileParser::threadCounter = 10;

void FileParser::CreateThreads(void)
{
    
    unsigned int *pIndexThread;
    Counter myCounter(0);

    for(int i =0;i<threadCounter;i++)
    {
        myThread[i].SetCounter(&myCounter);
        myThread[i].Start(i);
    }

    for(int i =0;i<threadCounter;i++)
    {
        pthread_t mythread;
        pthread_join(myThread[i].GetID(), (void **) &pIndexThread);
        std::cout << "pThread Index: " << *pIndexThread << "\n";
    }

    std::cout << "This is done\n";

}

void FileParser::CreateOccurenceToWord(void)
{
    for(mymap::const_iterator myIter = MapWordToOccurence.begin(); myIter != MapWordToOccurence.end(); myIter++)
    {    
        std::cout << "value:" << myIter->first << ":" << myIter->second << ":\n";
        myMapOccurenceToWord_t::const_iterator myOccurenceIter = MapOccurenceToWord.find(myIter->second);
        MapOccurenceToWord[myIter->second].push_back(myIter->first);
    }
}

void FileParser::PrintMapWordToOccurence(void)
{
    std::cout << "Print Map: Word To Occurence---------------------------------------------------------\n";
    
    for(mymap::const_iterator myIter = MapWordToOccurence.begin();myIter != MapWordToOccurence.end(); myIter++)
    {    
        std::cout << "value:" << myIter->first << ":" << myIter->second << ":\n";
     
    }
    std::cout << "Map Word To Occurence has been printed----------------------------------------------\n";
}

void FileParser::PrintMapOccurenceToWords(void)
{
    for(myMapOccurenceToWord_t::const_iterator myIter = MapOccurenceToWord.begin();myIter != MapOccurenceToWord.end(); myIter++)
    {
        std::cout << myIter->first << "->";
        
        for(std::vector<std::string>::const_iterator it =  myIter->second.begin();it!= myIter->second.end();++it)
        {
            std::cout << *it << ",";
        }
        std::cout << "\n";
    }
}

void FileParser::tokenize(const std::string& str, myArray_t& tokens)
{
    std::string::const_iterator myIterator = str.begin();
    std::string::const_iterator begin_pos = myIterator;
    bool inAword = false;

    while( myIterator!=str.end())
    {
        std::string::value_type c=*myIterator;

        if  ((c >= 'A' && c <= 'Z') || (c >= 'a' & c <= 'z'))
        {
            if (inAword == false) {begin_pos = myIterator;inAword = true;}
        }
        else
        {                 
            if (inAword && ( myIterator-begin_pos)>0)
            {                
                tokens.push_back(std::string(begin_pos, myIterator));
                inAword = false;
            }
        }       
        myIterator++;
    }

    if (inAword && ( myIterator-begin_pos)>0)
    {                
        tokens.push_back(std::string(begin_pos, myIterator));
        inAword = false;
    }
};


void FileParser::ReadAndParseTheFile(void)
{

    std::ifstream myFile;    

    myFile.open("toto.txt");

    if (myFile.is_open() == false)
    {
        std::cerr << "The file toto.txt does not exist\n";
        exit(-1);
    }
  
    for(std::string myString;std::getline(myFile, myString); )
    {
        myArray_t myVectorOfTokens;
        tokenize(myString, myVectorOfTokens);
     
        for(std::vector<std::string>::iterator it =  myVectorOfTokens.begin();it!= myVectorOfTokens.end();++it)
        {
            MapWordToOccurence.find(*it);
           
            if (myMapIter == MapWordToOccurence.end())
            {
                MapWordToOccurence[*it] = 1;
            }
            else
            {
                MapWordToOccurence[*it]+=1;
            }
        }
    }

    CreateOccurenceToWord();
    PrintMapWordToOccurence();
    PrintMapOccurenceToWords();
    exit(-1);
    
}

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
    
    return 0;
}
