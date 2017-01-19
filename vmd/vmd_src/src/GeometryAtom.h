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
 *      $RCSfile: GeometryAtom.h,v $
 *      $Author: johns $        $Locker:  $                $State: Exp $
 *      $Revision: 1.24 $      $Date: 2016/11/28 03:05:00 $
 *
 ***************************************************************************
 * DESCRIPTION:
 *
 * Draws a marker for a specified atom into the display list for a Displayable
 *
 ***************************************************************************/
#ifndef GEOMETRYATOM_H
#define GEOMETRYATOM_H

#include "GeometryMol.h"

/// GeometryMol subclass to label an atom
class GeometryAtom : public GeometryMol {

public:
  /// constructor: molecule id, atom index, molecule list
  GeometryAtom(int, int, const int *cell, MoleculeList *, CommandQueue *, Displayable *);
  
  // public virtual routines
  virtual void set_pick(void);     ///< use the TCL variables
  virtual void create_cmd_list();
};

#endif

