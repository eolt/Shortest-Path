#include <iostream>

using namespace std;

template <class Type>
struct nodeType
{
   Type info;
   nodeType<Type> *link;
};


template <class Type>
class linkedList {
private: 
   int count;
   nodeType<Type> *first;
   nodeType<Type> *last;
public:
   linkedList();
   int length();
   void insertLast(const Type& newItem);
   void insertFirst(const Type& newItem);
   void deleteNode(const Type& deleteItem);
   void destroyList();
   string print() const;
   ~linkedList();
   nodeType<Type> *begin(){return first;}
   nodeType<Type> *end(){return NULL;}
}; 


template <class Type>
linkedList<Type>::linkedList() 
{
   first = NULL;
   last = NULL;
   count = 0;
}

template <class Type>
int linkedList<Type>::length() 
{
   return count;
}

template <class Type>
void linkedList<Type>::insertLast(const Type& newItem)
{
   nodeType<Type> *newNode; //pointer to create the new node
   newNode = new nodeType<Type>; //create the new node
   newNode->info = newItem; //store the new item in the node
   newNode->link = NULL; //set the link field of newNode to NULL

   if (first == NULL) //if the list is empty, newNode is both the first and last node
   {
      first = newNode;
      last = newNode;
      count++; //increment count
   }
   else //the list is not empty, insert newNode after last
   {
      last->link = newNode; //insert newNode after last
      last = newNode; //make last point to the actual last node in the list
      count++; //increment count
   }
}

template <class Type>
void linkedList<Type>::insertFirst(const Type& newItem)
{
   nodeType<Type> *newNode; //pointer to create the new node
   newNode = new nodeType<Type>; //create the new node
   newNode->info = newItem; //store the new item in the node
   newNode->link = first; //insert newNode before first
   first = newNode; //make first point to the actual first node
   count++; //increment count
   
   if (last == NULL) //if the list was empty, newNode is also the last node in the list
      last = newNode;
}//end insertFirst

template <class Type>
string linkedList<Type>::print() const
{
   string result;
   nodeType<Type> *current; //pointer to traverse the list
   current = first; //set current point to the first node
   while (current != NULL) //while more data to print
   {
      result += to_string(current->info) + " ";
      current = current->link;
   }
   result.pop_back();
   return result;
}

template <class Type>
void linkedList<Type>::destroyList()
{
   nodeType<Type> *temp; //pointer to deallocate the memory occupied by the node
   while (first != NULL) //while there are nodes in the list
   {
      temp = first; //set temp to the current node
      first = first->link; //advance first to the next node
      delete temp; //deallocate the memory occupied by temp
   }
   last = NULL; //initialize last to NULL; first has already been set to NULL by the while loop
   count = 0;
}

template <class Type>
linkedList<Type>::~linkedList()
{
   destroyList();
}

template <class Type>
void linkedList<Type>::deleteNode(const Type& deleteItem)
{
   nodeType<Type> *current; //pointer to traverse the list
   nodeType<Type> *trailCurrent; //pointer just before current
   bool found;
   if (first == NULL) //Case 1: the list is empty.
      cout << "Cannot delete from an empty list." << endl;
   else
   {
      if (first->info == deleteItem) //Case 2: delete first node
      {
         current = first;
         first = first->link;
         count--;
         if (first == NULL) //the list has only one node
            last = NULL;
         delete current;
      }
      else //search the list for the node with the given info
      {
         found = false;
         trailCurrent = first; //set trailCurrent to point to the first node
         current = first->link; //set current to point to the second node
         while (current != NULL && !found)
         {
            if (current->info != deleteItem)
            {
               trailCurrent = current;
               current = current-> link;
            }
            else
               found = true;
         }//end while
         if (found) //Case 3; if found, delete the node
         {
            trailCurrent->link = current->link;
            count--;
            if (last == current) //node to be deleted was the last node
               last = trailCurrent; //update the value of last
            delete current; //delete the node from the list
         }
         else
         cout << "The item to be deleted is not in the list." << endl;
      }//end else
   }//end else
}//end deleteNode
