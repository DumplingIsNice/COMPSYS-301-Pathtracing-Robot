//#ifndef NODELIST_H
//#define NODELIST_H
//
///*
//	Node List
//
//	!!! NodeList has replaced the deprecated SLList !!!
//
//	For optimisation purposes no checks are performed that that inputs
//	are valid.
//
//	IF YOU INCORRECTLY PASS NULL TO FUNCTIONS YOU WILL CORRUPT YOUR DATA
//	AND/OR CRASH THE SYSTEM.
//
//	The field 'node' is handled very loosely to support easily changing
//	struct types. NodeList operations should never interact with 'node'
//	beyond exposing it for external operations.
//	e.g.	... element->node ...			// okay
//			... element->node->value ...	// wrong; inherent assumption
//	Operations on 'node' should be handled with the NodeDataOps file.
//*/
//
//#include "List.h"
//
//
//// Free() the NodeListElement structs, and their valid NodeData structs.
////void DestroyNodeListElementsAndContents(NodeList* list);
//
//
//#endif // !NODELIST_H
