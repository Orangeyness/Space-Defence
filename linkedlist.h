#ifndef _LINKEDLISTS_
#define _LINKEDLISTS_

namespace linkedLists {
	template <class T> 
	class LinkedList;

	template <class T>
	class LinkedListNode {
		private:
			T myValue;

		public:	
			LinkedList<T> *Parent;
			LinkedListNode<T> *Previous;
			LinkedListNode<T> *Next;

			LinkedListNode(T Value);
			LinkedListNode(T Value, LinkedList<T>* Parent);		

			LinkedListNode<T>* addValueBefore(T Value);	
			LinkedListNode<T>* addValueAfter(T Value);

			T getValue();	
			LinkedListNode<T>* getNext();
			LinkedListNode<T>* getPrevious();
			LinkedList<T>* getList();

			void remove();		
		};

	template <class T> 
	class LinkedList {
		public:
			int nodeCount;
			LinkedListNode<T> *First;
			LinkedListNode<T> *Last;

			LinkedList();
			~LinkedList();
			
			LinkedListNode<T>* get(int i);
			LinkedListNode<T>* getFirst();
			LinkedListNode<T>* getLast();

			T getValue(int i);
			T getFirstValue();
			T getLastValue();

			LinkedListNode<T>* addBefore(T Value, int i);
			LinkedListNode<T>* addAfter(T Value, int i);
			LinkedListNode<T>* addFirst(T Value);	
			LinkedListNode<T>* addLast(T Value);	

			void remove(int i);
			void removeFirst();
			void removeLast();

		};


	template <class T> LinkedList<T>::LinkedList() {
		First = NULL;
		Last = NULL;
		nodeCount = 0;	
		}

	template <class T> LinkedList<T>::~LinkedList(){	
		while(First != NULL) {
			First->remove();
			}	
		}

	template <class T> LinkedListNode<T>* LinkedList<T>::get(int i) {
		if (i < 0 || i >= nodeCount) return NULL;
		int j = 0;
		LinkedListNode<T> *nodeI = First;
		while (j < i) {
			nodeI = nodeI->Next;
			j ++;
			}		
		return nodeI;
		}

	template <class T> LinkedListNode<T>* LinkedList<T>::getFirst() {
		return this->First;		
		}

	template <class T> LinkedListNode<T>* LinkedList<T>::getLast() {
		return this->Last;		
		}

	template <class T> T LinkedList<T>::getValue(int i) {
		return this->get(i)->getValue();	
		}

	template <class T> T LinkedList<T>::getFirstValue() {
		return this->getFirst()->getValue();		
		}

	template <class T> T LinkedList<T>::getLastValue() {
		return this->getLast()->getValue();		
		}

	template <class T> LinkedListNode<T>* LinkedList<T>::addBefore(T Value, int i) {
		LinkedListNode<T> *node = get(i);
		if (node == NULL) return NULL;
		return node->addValueBefore(Value);
		}

	template <class T> LinkedListNode<T>* LinkedList<T>::addAfter(T Value, int i) {
		LinkedListNode<T> *node = get(i);
		if (node == NULL) return NULL;
		return node->addValueAfter(Value);
		}

	template <class T> LinkedListNode<T>* LinkedList<T>::addFirst(T Value) {
		if (First == NULL) {
			First = new LinkedListNode<T>(Value, this);
			Last = First;
			nodeCount ++;
			return First;			
			}
		return First->addValueBefore(Value);
		}	

	template <class T> LinkedListNode<T>* LinkedList<T>::addLast(T Value) {
		if (First == NULL) {
			First = new LinkedListNode<T>(Value, this);
			Last = First;
			nodeCount ++;
			return First;			
			}
		return Last->addValueAfter(Value);
		}	

	template <class T> void LinkedList<T>::remove(int i) {
		get(i)->remove();		
		}

	template <class T> void LinkedList<T>::removeFirst() {
		First->remove();		
		}

	template <class T> void LinkedList<T>::removeLast() {
		Last->remove();		
		}
	//---

	template <class T> 
	LinkedListNode<T>::LinkedListNode(T Value) {
		myValue = Value;
		Previous = NULL;
		Next = NULL;
		Parent = NULL;
		}

	template <class T> 
	LinkedListNode<T>::LinkedListNode(T Value, LinkedList<T>* pList) {
		myValue = Value;
		Previous = NULL;
		Next = NULL;
		Parent = pList;
		}

	template <class T> 
	T LinkedListNode<T>::getValue() {
		return myValue;	
		}

	template <class T> LinkedListNode<T>* LinkedListNode<T>::addValueBefore(T Value) {
		LinkedListNode<T> *NewNode = new LinkedListNode<T>(Value, Parent);
		if (Previous != NULL) {
			Previous->Next = NewNode;		
			NewNode->Previous = Previous;		
			}
		if (Parent != NULL) {
			Parent->nodeCount ++;			
			if (Parent->First == this || Parent->First == NULL || Previous == NULL) {
				Parent->First = NewNode;
				}			
			}
		Previous = NewNode;
		NewNode->Next = this;
		NewNode->Parent = Parent;	
		return NewNode;
		}

	template <class T> LinkedListNode<T>* LinkedListNode<T>::addValueAfter(T Value) {
		LinkedListNode<T> *NewNode = new LinkedListNode<T>(Value, Parent);
		if (Next != NULL) {
			Next->Previous = NewNode;		
			NewNode->Next = Next;		
			}
		if (Parent != NULL) {
			Parent->nodeCount ++;			
			if (Parent->Last == this || Parent->Last == NULL || Next == NULL) {
				Parent->Last = NewNode;
				}			
			}
		Next = NewNode;
		NewNode->Previous = this;	
		NewNode->Parent = Parent;
		return NewNode;
		}

	template <class T> void LinkedListNode<T>::remove() {
		if (Next != NULL && Next->Previous == this) {
			Next->Previous = Previous;		
			}	
		if (Previous != NULL && Previous->Next == this) {
			Previous->Next = Next;		
			}
		if (Parent != NULL) {
			Parent->nodeCount --;			
			if (Parent->Last == this || Parent->Last == NULL) {
				if (Previous != NULL) {
					Parent->Last = Previous;					
					}
						else
					{
					Parent->Last = NULL;
					}
				}			
			if (Parent->First == this || Parent->First == NULL) {
				if (Next != NULL) {
					Parent->First = Next;					
					}
						else
					{
					Parent->First = NULL;
					}
				}			
			}	
		delete this;
		}

	template <class T> LinkedListNode<T>* LinkedListNode<T>::getNext() {
		return Next; 	
		} 
	template <class T> LinkedListNode<T>* LinkedListNode<T>::getPrevious() {
		return Previous; 	
		} 

	template <class T> LinkedList<T>* LinkedListNode<T>::getList() {
		return Parent;	
		}	
	}
#endif
