template <class T>
class SortedArray {
private:

public:
  static const int m_sizeofTheArray = 5;
  SortedArray(void);
  T m_array[m_sizeofTheArray];
  int partition(int left, int right, int pivoIndex);
  void qsort(int left, int right);
  virtual int comp(T x, T y) { return (x<y); }
  void printArray(void);
  void swap(int x, int y) {  std::cout << "Swap(" << x << "," << y << ")\n"; T v = m_array[x]; m_array[x]=m_array[y];m_array[y]=v; printArray();}
  
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
  std::cout << "### begin qsor" << left << "," << right <<" \n";
  if (left >= right)
    {
      std::cout << "left is bigger than right!\n";
    return;
    } 
  int pivotIndex = (left+right)/2;
  int pivotNewIndex = partition(left, right, pivotIndex);
  qsort(left, pivotNewIndex-1);
  qsort(pivotNewIndex+1, right);
  std::cout << "### end qsor" << left << "," << right <<" \n";
}

/**

   Precondition:
   =============

   - For a given subsequence denoted by the indexes left and right and the index Pivot
   - pivot belonge to the range [left, right]

   Postcondition:
   =============

   - a partition has been created
   - all values smaller than the pivot value are on the left of the pivot
   - all values greater than the pivot value are on the right of the pivot
   - storeIndex is the new position of the pivot value
   -
*/

template <class T>
int SortedArray<T>::partition(int left, int right, int pivotIndex)
{

  int pivotValue = m_array[pivotIndex];
  std::cout << "======================== begin Partition" << left << "," << right << "\n";
  swap(pivotIndex,right);
  int storeIndex = left;
  std::cout << "left:" << left << " right:" << right << " pivotIndex:" << pivotIndex << " pivotValue:" << pivotValue << "\n";
  for(int i=left;i<right;i++)
  {
    
    if (comp(m_array[i], pivotValue))
    {
      std::cout << "we actually do move an item smaller than: " << pivotValue << "\n";
      swap(i, storeIndex);
      storeIndex = storeIndex + 1;
    }

  }
  
  swap(storeIndex, right);
  std::cout << "storeIndex:" << storeIndex << "\n";
  std::cout << "======================== end Partition" << left << "," << right << "\n";
 
  return storeIndex;

};
