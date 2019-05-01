
// HeapADT.h declares the interface to a Heap Data Type.
// @author bks: ben k steele, bks@cs.rit.edu
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef HEAPADT_H
#define HEAPADT_H

/// General Notes on HeapDT Operation
/// The operations identified below are the public interface to HeapDT.
/// Wherever a function has a precondition, and
/// that precondition is violated by client code, and
/// that precondition violation is detectable by the heap code,
/// then the function will assert failure and abort.
/// Similarly, wherever a function has a postcondition, and
/// that postcondition is violated by client code, then the function
/// will assert failure and abort.
///
/// The Heap data type is opaque to clients.
///
typedef struct Heap_S * Heap;

/// createHeap constructs an empty heap.
/// @return a heap object (pointer)
/// @pre compFun and dumpEntry are not NULL.
/// @post the heap is not NULL (i.e. there was enough storage).
///
Heap createHeap( size_t capacity
               , int (*compFun)( const void * lhs, const void * rhs )
               , void (*dumpEntry)( const void * item, FILE * outfp ) ) ;


/// destroyHeap deletes all dynamic heap storage.
/// @param aHeap the subject heap
/// @pre aHeap is a valid heap data type reference.
/// @pre client previously removed and deleted all entries that
/// involved dynamic memory allocation.
/// @post the aHeap reference is no longer valid.
///
void destroyHeap( Heap aHeap );

/// @param aHeap the subject heap
/// @return the current number of active entries in the heap.
/// @pre aHeap is a valid heap data type reference.
///
size_t sizeHeap( Heap aHeap );

/// topHeap returns an immutable pointer to the topmost item in the heap.
/// @param aHeap the subject heap
/// @return an immutable pointer to the topmost item.
/// @pre aHeap is a non-empty, valid heap data type instance.
/// @post the internal state of aHeap has not changed.
///
const void * topHeap( const Heap aHeap );

/// removeTop removes the topmost item from the heap.
/// @param aHeap the subject heap
/// @return a pointer to the removed item.
/// @pre aHeap is a non-empty, valid heap data type instance.
/// @post client assumes ownership of the item removed.
///
void * removeTopHeap( Heap aHeap );

/// insertHeapItem inserts an item into the heap.
/// @param aHeap the subject heap
/// @param item the item to insert into the heap
/// @pre aHeap is a valid heap data type instance.
/// @post heap assumes (temporary) ownership/custody of the item, and
/// the client must not delete the memory while heap owns it.
///
void insertHeapItem( Heap aHeap, const void * item );

/// dumpHeap prints the heap content to the specified output file stream.
/// @param aHeap the subject heap
/// @param outfp the output file stream
/// @pre aHeap is a valid heap data type instance.
/// @post the internal state of aHeap has not changed.
///
void dumpHeap( Heap aHeap, FILE * outfp );


#endif // HEAPADT_H
// // // // // // // // // // // // // // // // // // // // // // // // 
// RCS Revisions:
// $Log$
