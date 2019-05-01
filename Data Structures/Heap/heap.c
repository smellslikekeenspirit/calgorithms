// This file is under git.
// heap.c implements the interface to a Heap Data Type.
// @author bks: Prionti Nasir, pdn3628@rit.edu
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


/// definition for the Heap struct
struct Heap_S{
	const void **array;
        size_t capacity;
	size_t size;
	int (*compFun)( const void *, const void *);
        void (*dumpEntry)( const void *, FILE *) ;
};


#include "heap.h"


/// createHeap constructs an empty heap.
/// @return a heap object (pointer)
/// @pre compFun and dumpEntry are not NULL.
/// @post the heap is not NULL (i.e. there was enough storage).
///
Heap createHeap( size_t capacity
               , int (*compFun)( const void * lhs, const void * rhs )
               , void (*dumpEntry)( const void * item, FILE * outfp ) ) {
	Heap new = calloc(1, sizeof(struct Heap_S));
        new->array = calloc(capacity, sizeof(void *));
	new->capacity = capacity;
	new->dumpEntry = dumpEntry;
	new->compFun = compFun;
	new->size = 0;
	return new;
}
/// destroyHeap deletes all dynamic heap storage.
/// @param aHeap the subject heap
/// @pre aHeap is a valid heap data type reference.
/// @pre client previously removed and deleted all entries that
/// involved dynamic memory allocation.
/// @post the aHeap reference is no longer valid.
///
void destroyHeap( Heap aHeap ){
	free(aHeap);
}

/// @param aHeap the subject heap
/// @return the current number of active entries in the heap.
/// @pre aHeap is a valid heap data type reference.
///
size_t sizeHeap( Heap aHeap ){
	return aHeap->size;
}

/// topHeap returns an immutable pointer to the topmost item in the heap.
/// @param aHeap the subject heap
/// @return an immutable pointer to the topmost item.
/// @pre aHeap is a non-empty, valid heap data type instance.
/// @post the internal state of aHeap has not changed.
///
const void * topHeap( const Heap aHeap ){
	return aHeap->array[0];
}

/// returns index of parent of given element
int parent(int idx){
        return ((idx-1)/2);
}

/// returns index of left child of given element
int lChild(int idx){
        return (2*idx)+1;
}

/// returns index of right child of given element
int rChild(int idx){
        return (2*idx)+2;
}

/// returns index of element that should come first
int firstOf3(Heap heap, int idx){
	int lt = lChild(idx);
        int rt = rChild(idx);
        void *lVal;
        void *rVal;
	void *thisVal = (void *)(heap->array[idx]);
	if (rt < (int)heap->size){
		lVal = (void *)(heap->array[lt]);
		rVal = (void *)(heap->array[rt]);
		if ( heap->compFun(lVal, thisVal) || heap->compFun(rVal, thisVal) ){
			if (heap->compFun(lVal, rVal)){
				return lt;
			}
			else{
				return rt;
			}
		}
		else{
			return idx;
		}
	}
	else if (lt < (int)heap->size){
		lVal = (void *)(heap->array[lt]);
		if (heap->compFun(lVal, thisVal)){
			return lt;
		}
		else{
			return idx;
		}
	}else{
		return idx;
	}
}

/// Move the value at startIndex down to its proper spot in
/// the given heap. Assume that the value does not have
/// to move up

void siftDown(Heap heap, int start){
	int i = start;
        void **a = (void **)heap->array;
        int swap = firstOf3(heap, i);
        while (swap != i){
        	void *tmp = a[swap];
                a[swap] = a[i];
                a[i] = tmp;
                heap->array = (const void **)a;
                i = swap;
		swap = firstOf3(heap, i);
        }
        heap->array = (const void **)a;
        
}

/// removes an item from the heap array
///
void  **removeFromIdx(void** arr, int size, int idx)
{
    void **tmp = malloc((size - 1) * sizeof(void *)); 
    if (idx != 0){
        memcpy(tmp, arr, idx * sizeof(void *)); 
    }
    if (idx != (size - 1)){
        memcpy(tmp+idx, arr+idx+1, (size - idx - 1) * sizeof(void *));
    }
    free(arr);
    return tmp;
}


/// removeTop removes the topmost item from the heap.
/// @param aHeap the subject heap
/// @return a pointer to the removed item.
/// @pre aHeap is a non-empty, valid heap data type instance.
/// @post client assumes ownership of the item removed.
///
void * removeTopHeap( Heap aHeap ){

	void * top = (void *)topHeap(aHeap);
        void **a = (void **)aHeap->array;
        aHeap->size--;
        a[0] = a[sizeHeap(aHeap)];
	void **ptr = removeFromIdx(a, sizeHeap(aHeap)+1, sizeHeap(aHeap));
        if (ptr != NULL){
            a = ptr;
        }else{
            printf("Reallocation failed!");
        }
        aHeap->array = (const void **)a;
        siftDown(aHeap, 0);
	return top;
}

/// Move the value at startIndex up to its proper spot in
/// the given heap. Assume that the value does not have
/// to move down
///
void siftUp(Heap aHeap, int start){
        int i = start;
        void **a = (void **)aHeap->array;
        while(i>0 && !aHeap->compFun( a[parent(i)], a[i] )){
                void *tmp = a[parent(i)];
                a[parent(i)] = a[i];
                a[i] = tmp;
                i = parent(i);
        }
        aHeap->array = (const void **)a;
}

/// insertHeapItem inserts an item into the heap.
/// @param aHeap the subject heap
/// @param item the item to insert into the heap
/// @pre aHeap is a valid heap data type instance.
/// @post heap assumes (temporary) ownership/custody of the item, and
/// the client must not delete the memory while heap owns it.
///

void insertHeapItem( Heap aHeap, const void * item ){
        if (aHeap->capacity == aHeap->size){
                void **ptr = realloc(aHeap->array, aHeap->capacity*2*sizeof(void *));
                if (ptr != NULL){
                    aHeap->array = (const void **)ptr;
                    aHeap->capacity *= 2;
                }else{
                    printf("Reallocation failed!");
                }
        }
        aHeap->array[sizeHeap(aHeap)] = item;
        siftUp(aHeap, (int)aHeap->size);
        aHeap->size++;
}


/// dumpHeap prints the heap content to the specified output file stream.
/// @param aHeap the subject heap
/// @param outfp the output file stream
/// @pre aHeap is a valid heap data type instance.
/// @post the internal state of aHeap has not changed.
///
void dumpHeap( Heap aHeap, FILE * outfp ){
	unsigned int i = 0;
	while(i<sizeHeap(aHeap)){
		aHeap->dumpEntry(aHeap->array[i], outfp);
                i++;
	}
}

