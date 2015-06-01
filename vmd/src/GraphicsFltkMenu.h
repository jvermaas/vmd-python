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
 *      $RCSfile: GraphicsFltkMenu.h,v $
 *      $Author: johns $        $Locker:  $             $State: Exp $
 *      $Revision: 1.32 $       $Date: 2011/11/23 19:00:07 $
 *
 ***************************************************************************
 * DESCRIPTION:
 *  generated by Fast Light User Interface Designer (fluid) version 1.0011
 ***************************************************************************/

#ifndef graphicsmenu_h
#define graphicsmenu_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>
#include "VMDFltkMenu.h"
#include "NameList.h"

class GraphicsFltkRep;
class SelectionBuilder;
class Fl_Tabs;
class Fl_Counter;
class PBCControls;
class isosurface_cbdata;
class orbital_cbdata;
class quicksurf_cbdata;

/// VMDFltkMenu subclass implementing a GUI for controlling graphical
/// representations of molecules
class GraphicsFltkMenu : public VMDFltkMenu {
public:
  GraphicsFltkMenu(VMDApp *);
  ~GraphicsFltkMenu();

  int selectmol(int molno);
 
//private: // XXX should ideally make all this private
  VMDApp *app;
  int molindex;
  int repindex;

  void update_molchooser();
 
  void update_repbrowser(bool remember_position=false);
  void update_rep();
  void update_repindex();
  void update_pbc();
  void set_pbc(int, int);
  void reset_rep();

  /// put the given text into the selection input and perform the
  /// callback.  If txt is NULL, then restore the last known good
  /// selection text. 
  void update_selection(const char *txt);
  const char *selectiontext() const;

  /// Returns true if changes to reps should be applied immediately.
  int auto_update() const;

  /// sets selection autoupdate for the currently highlighted rep.
  void set_autoupdate(int);

  /// sets color autoupdate for the currently highlighted rep.
  void set_colorupdate(int); 

  /// Cause the current rep to use the current color scale data range values.
  void use_colorscale_minmax();

  /// Cause the current rep to autoscale its color scale data range.
  void use_colorscale_auto();

  char *create_repcmd();
  char *create_colorcmd();
  char *create_selcmd();
  char *create_matcmd();
  char *create_multiframecmd();

  void colindex_visible();
  void volindex_visible();
  void volindex_update();
  void show_repcontrols();
 
  void init_colorchooser();
  void init_materialchooser();
  void init_stylechooser();

  SelectionBuilder *selbuilder;

private:
  static void molchooser_cb(Fl_Widget *, void *);
  static void repbrowser_cb(Fl_Widget *, void *);
  static void repcontrol_cb(Fl_Widget *, void *);
  static void colorchooser_cb(Fl_Widget *, void *);
  static void materialchooser_cb(Fl_Widget *, void *);
  static void selectioninput_cb(Fl_Widget *, void *);
  static void createnew_cb(Fl_Widget *, void *);
  static void deleterep_cb(Fl_Widget *, void *);
  static void apply_cb(Fl_Widget *, void *);
  static void default_cb(Fl_Widget *, void *);
  static void smooth_cb(Fl_Widget *, void *);
  static void pbc_cb(Fl_Widget *, void *);
  static void multiframeinput_cb(Fl_Widget *, void *);
  static void isosurfacerepcontrol_cb(Fl_Widget *, void *);
  static void orbitalrepcontrol_cb(Fl_Widget *, void *);
  static void quicksurfrepcontrol_cb(Fl_Widget *, void *);

public:
  NameList<GraphicsFltkRep *> repcontrols;

private:
  ResizeArray<int> molactiverep;
  int lastmolindex;
 
  char colorcmdbuf[50];

  Fl_Box *repframe;
  Fl_Choice *molchooser;
  Fl_Browser *repbrowser;
  Fl_Choice *colorchooser;
  Fl_Choice *materialchooser;
  Fl_Choice *stylechooser;
  Fl_Input *selectioninput;
  Fl_Choice *colindexchooser;
  Fl_Choice *volindexchooser;
  Fl_Check_Button *applyautobutton;
  Fl_Button *applybutton;
  Fl_Button *createnewbutton;
  Fl_Button *deleterepbutton;
  Fl_Button *defaultbutton;
  Fl_Button *autoupdatebutton;
  Fl_Button *colorupdatebutton;
  Fl_Counter *smoothcounter;
  PBCControls *pbcControls;
  Fl_Input *colorscale_min, *colorscale_max;
  Fl_Input *multiframeinput;

  isosurface_cbdata * isosurfcbdata;
  orbital_cbdata * orbcbdata;
  quicksurf_cbdata * qsurfcbdata;

protected:
  int act_on_command(int, Command *);
};
#endif
