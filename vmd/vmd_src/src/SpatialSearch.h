/***************************************************************************
 *cr                                                                       
 *cr            (C) Copyright 1995-2016 The Board of Trustees of the           
 *cr                        University of Illinois                       
 *cr                         All Rights Reserved                        
 *cr                                                                   
 ***************************************************************************/

/***************************************************************************
 * RCS INFORMATION:
 *
 *	$RCSfile: SpatialSearch.h,v $
 *	$Author: johns $	$Locker:  $		$State: Exp $
 *	$Revision: 1.6 $	$Date: 2016/11/28 03:05:04 $
 *
 ***************************************************************************
 * DESCRIPTION:
 *
 * Distance based bond search code 
 *
 ***************************************************************************/
#ifndef SPATIALSEARCH_H__
#define SPATIALSEARCH_H__

#include "ResizeArray.h"

/// linked list of atom index pairs generated by the vmd_gridsearch1 
/// and vmd_gridsearch2
/// XXX on 64-bit machines the next pointers are as large as the atom index
/// data in each node, so half of the memory is wasted in pointer chasing.
/// Calling malloc/free once per pair when building the linked list
/// is a severe multithreading scalability bottleneck due to OS-level 
/// mutex locks in malloc/free and/or the kernel VM.
/// On Linux, it is also problematic due to the threaded version of 
/// malloc allocating huge blocks and fragmenting memory tremendously.
/// This implementation should not be used for any threaded code.
struct GridSearchPair {
  int ind1, ind2;
  GridSearchPair *next;
};


/// Linked list of ResizeArrays containing pairlists, optimized for
/// multithreading.  Compared with the GridSearchPair linked list,
/// The list of ResizeArrays uses half as much memory per pair, reduces
/// the malloc calls so they are logarithmic rather than linear with
/// the number of bonds, and reduces free call count to one per-thread down
/// from one per-bond.  Since the ResizeArray results in a contiguous block
/// of memory, the traversal coherency is also significantly improved.
/// Ultimately we should convert all of the grid search routines to use
/// this type of data structure, or one like it.
struct GridSearchPairlist {
  ResizeArray<int> *pairlist;
  GridSearchPairlist *next;
};

/// Build neighborlist
int make_neighborlist(int **nbrlist, int xb, int yb, int zb);

/// Grid search for the case of a single set of atoms. It ignore pairs 
/// between atoms with identical coords.  The maxpairs parameter is 
/// set to -1 for no-limit pairlist calculation, or a maximum value otherwise.
GridSearchPair *vmd_gridsearch1(const float *pos, int n, const int *on, 
                                float dist, int allow_double_counting, 
                                int maxpairs);

/// Grid search for two different sets of atoms in same molecule.
/// (will eventually be obsoleted by the faster and more useful 
/// vmd_gridsearch3).
/// right now, is still needed by measure hbonds (until problems resolved)
/// The maxpairs parameter is set to -1 for no-limit pairlist calculation, 
/// or a maximum value otherwise.
GridSearchPair *vmd_gridsearch2(const float *pos, int natoms, const int *A, 
                                const int *B, float pairdist, int maxpairs);

/// Grid search for two different sets of atoms and/or molecules.
/// By default, if (posA == posB), all bonds are unique. Otherwise, 
/// double-counting is allowed. This can be overridden by setting
/// the allow_double_counting param (true=1, false=0, or default=-1).
/// The maxpairs parameter is set to -1 for no-limit pairlist calculation, 
/// or a maximum value otherwise.
GridSearchPair *vmd_gridsearch3(const float *posA, int natomsA, const int *A, 
                                const float *posB,int natomsB, const int *B,
                                float pairdist, int allow_double_counting, 
                                int maxpairs);

/// Find axis-aligned bounding box for all atoms in the list
void find_minmax_all(const float *pos, int n, float *min, float *max);


/// Find axis-aligned bounding box for selected atoms in the list
/// Return true if minmax was found, false if all flags are zero.
int find_minmax_selected(int n, const int *flgs, const float *pos,
                         float &_xmin, float &_ymin, float &_zmin,
                         float &_xmax, float &_ymax, float &_zmax);


/// Find axis-aligned bounding box for selected atoms in the list
void find_minmax(const float *pos, int n, const int *on,
                 float *min, float *max, int *oncount);


/// Find selected atoms within a specified distance of a second set of points
void find_within(const float *xyz, int *flgs, const int *others,
                 int num, float r);

#endif
