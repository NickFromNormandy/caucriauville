#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
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

typedef  std::unordered_map <std::string, int> mymap; 

class FileParser
{

public:

    FileParser() {}
   
    void ReadAndParseTheFile(void);
    void PrintMapWordToOccurence(void);
    void tokenize(const std::string& str, std::vector<std::string>& tokens);

private:

    mymap  MapWordToOccurence;
    mymap::const_iterator myMapIter;
};

void FileParser::PrintMapWordToOccurence(void)
{
    std::cout << "Print Map: Word To Occurence\n";
    mymap::const_iterator myIter = MapWordToOccurence.begin();

    for(;myIter != MapWordToOccurence.end(); myIter++)
    {    
        std::cout << "value:" << myIter->first << ":" << myIter->second << ":\n";
    }
    std::cout << "Print has been printed\n";
}


void FileParser::tokenize(const std::string& str, std::vector<std::string>& tokens)
{
    std::string::const_iterator myIterator = str.begin();
    std::string::const_iterator begin_pos = myIterator;
    

    while(begin_pos!=str.end())
    {
        
        while( myIterator!=str.end())
        {
            std::string::value_type c=*myIterator;
            if  ((c >= 'A' && c <= 'Z') || (c >= 'a' & c <= 'z'))
            {
                tokens.push_back(std::string(begin_pos, myIterator));
                myIterator++;               
            }
            else
            {
                
                myIterator++;
                break;
            }
        }
       
        if (myIterator == str.end())
        {
        
            break;
        }

        begin_pos = myIterator;
    }
};

void FileParser::ReadAndParseTheFile(void)
{
    Counter myCounter(0);
    std::ifstream myFile;    

    myFile.open("toto.txt");

    if (myFile.is_open() == false)
    {
        std::cerr << "The file toto.txt does not exist\n";
        exit(-1);
    }
  
    for(std::string myString;std::getline(myFile, myString); )
    {
        std::vector<std::string> myVectorOfTokens;
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

    PrintMapWordToOccurence();
    exit(-1);

    const int threadCounter = 10;
    unsigned int *pIndexThread;
    NickThread myThread[threadCounter];   

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

int main()
{
    FileParser myFileParser;

    myFileParser.ReadAndParseTheFile();
    return 0;
}
