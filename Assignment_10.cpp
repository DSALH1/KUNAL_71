#include <bits/stdc++.h>
using namespace std;
class Heap{
    public:
       int arr[100];
       int size;
       Heap()
       {
         arr[0] = -1;
         size = 0;
       }

       void insert(int val)
       {
          size = size + 1;
          int index = size;
          arr[index] = val;
          while(index>1)
          {
             int parent = index/2;
             if(arr[parent] < arr[index])
             {
                swap(arr[parent], arr[index]);
                index = parent;
             }
             else
             {
                return;
             }
          }
       }
       void print()
       {
          for(int i=1; i<=size; i++)
          {
            cout << arr[i] <<" ";
          }
          cout <<endl;
       }
       void deleteFromHeap()
       {
         if(size == 0)
         {
            cout<<"Nothing to delete"<<endl;
            return;
         }

         arr[1] = arr[size];
         size--;

         int i=1;
         while(i<size)
         {
            int leftIndex = 2*i;
            int rightIndex = 2*i+1;

            if(leftIndex < size && arr[i] < arr[leftIndex])
            {
               swap(arr[i], arr[leftIndex]);
               i = leftIndex;
            }
            else if(rightIndex < size && arr[i] < arr[rightIndex])
            {
                swap(arr[i], arr[rightIndex]);
                i = rightIndex;
            }
            else
            {
                return;
            }
         }
       }
};
void heapify (int arr[], int n, int i)
{
    int largest = i;
    int left = 2*i;
    int right = 2*i + 1;
    if(left < n and arr[largest] < arr[left])
    {
        largest = left;
    }
    if(right < n and arr[largest] < arr[right])
    {
        largest = right;
    }
    if(largest != i)
    {
        swap(arr[largest], arr[i]);
        heapify(arr,n,largest);
    }
}
void heapsort(int arr[], int n)
{
   int size = n;
   while(size > 1)
   {
      swap(arr[size], arr[1]);
      size--;
      heapify(arr,size,1);
   }
}
int main()
{
   Heap h;
   h.insert(20);
   h.insert(50);
   h.insert(10);
   h.insert(26);
   h.print();
   h.deleteFromHeap();
   h.print();
   int ar[6] = {-1, 54, 53, 55, 52, 50};
   int n = 5;
   for(int i=n/2; i>0; i--)
   {
      heapify(ar,n,i);
   }
   cout<<"Printing the heap"<<endl;
   for(int i=1; i<=n; i++)
   {
     cout<<ar[i]<<" ";
   }cout<<endl;

   return 0;
}