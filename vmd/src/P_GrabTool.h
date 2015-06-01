/***************************************************************************
 *cr                                                                       
 *cr            (C) Copyright 1995-2011 The Board of Trustees of the           
 *cr                        University of Illinois                       
 *cr                         All Rights Reserved                        
 *cr                                                                   
 ***************************************************************************/

/***************************************************************************
 * RCS INFORMATION:
 *
 *	$RCSfile: P_GrabTool.h,v $
 *	$Author: johns $	$Locker:  $		$State: Exp $
 *	$Revision: 1.24 $	$Date: 2010/12/16 04:08:30 $
 *
 ***************************************************************************/

/// The grab tool allows users to move molecules around.
/** The grab tool is the most basic of tools, as evidenced by the
 minimal amount of code it contains.  All it does is allow users
 to grab molecules and move them around, using the functionality
 provided by UIVR, and maybe provide some force feedback. */

#include "P_Tool.h"
class GrabTool : public Tool {
 public:
  GrabTool(int id, VMDApp *, Displayable *);
  virtual void do_event();

  const char *type_name() const { return "grab"; }
 private:
  int targetting;
};


