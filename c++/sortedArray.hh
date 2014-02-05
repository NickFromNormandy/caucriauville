template <class T>
class SortedArray {
private:

public:
  static const int m_sizeofTheArray = 4;
  SortedArray(void);
  T m_array[m_sizeofTheArray];
  int partition(int left, int right, int pivoIndex);
  void qsort(int left, int right);
  virtual int comp(T x, T y) { return (x<y); }
  void printArray(void);
  void swap(int x, int y) { std::cout << "Swap(" << x << "," << y << ")\n"; T v = m_array[x]; m_array[x]=m_array[y];m_array[y]=v; printArray();}
  
};

template <class T>
SortedArray<T>::SortedArray(void)
{
  srand(time(NULL));
  
}

template <class T>
void SortedArray<T>::printArray(void)
{
  int i;
  std::cout << "this is the array\n";
  for(i=0;i< m_sizeofTheArray;i++)
  {
    std::cout << m_array[i] << ",";
  }
  std::cout << "\n";
}

template<class T>
void SortedArray<T>::qsort(int left, int right)
{
  if (left >= right)
    return;
  int pivotIndex = (left+right)/2;
  int pivotNewIndex = partition(left, right, pivotIndex);
  qsort(left, pivotNewIndex-1);
  qsort(pivotNewIndex+1, right);

}

template <class T>
int SortedArray<T>::partition(int left, int right, int pivotIndex)
{

  int pivotValue = m_array[pivotIndex];

  swap(pivotIndex,right);
  int storeIndex = left;
  std::cout << "left:" << left << " right:" << right << " pivotIndex:" << pivotIndex << " pivotValue:" << pivotValue << "\n";
  for(int i=left;i<right;i++)
  {
    
    if (comp(m_array[i], pivotValue))
    {
      std::cout << "we actually do the partition\n";
      swap(i, storeIndex);
      storeIndex = storeIndex + 1;
    }

  }
  
  swap(storeIndex, right);
  return storeIndex;

};