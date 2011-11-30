/*

  This macro will add histograms from a list of root files and write them
  to a target root file. The target file is newly created and must not be
  identical to one of the source files.

  Syntax:

  hist_add targetfile source1 source2 ...

  Author: Sven A. Schmidt, sven.schmidt@cern.ch
  Date:   13.2.2001

  This code is based on the hadd.C example by Rene Brun and Dirk Geppert,
  which had a problem with directories more than one level deep.

  I have tested this macro on rootfiles with one and two dimensional 
  histograms, and two levels of subdirectories. Feel free to send comments 
  or bug reports to me.

 */


#include <TROOT.h>
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include <string.h>
#include <iostream.h>

void MergeRootfile( TDirectory *target, TList *sourcelist );

TList *FileList;
TFile *Target;


int merge_hadd_babar() {

  Target = TFile::Open( "/raid4/perrozzi/analysis/k0reco_pt_mean_all.root", "RECREATE" );

  FileList = new TList();

  // ************************************************************
  // List of Files

//  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_1over8.root"));
/*  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_2over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_3over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_4over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_5over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_6over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_7over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_phi_Ks_gen_rec_8over8.root"));
*/
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_pt_mean_2over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_pt_mean_3over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_pt_mean_4over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_pt_mean_5over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_pt_mean_6over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_pt_mean_7over8.root"));
  FileList->Add( TFile::Open("/raid4/perrozzi/analysis/k0reco_pt_mean_8over8.root"));

  cout << "going to call merging routine..." << endl;
  MergeRootfile( Target, FileList);
  cout << "done." << endl;

}



// Merge all files from sourcelist into the target directory.
// The directory level (depth) is determined by the target directory's
// current level
void MergeRootfile( TDirectory *target, TList *sourcelist ) {

  //  cout << "Target path: " << target->GetPath() << endl;
  TString path( (char*)strstr( target->GetPath(), ":" ) );
  path.Remove( 0, 2 );

  TFile *first_source = (TFile*)sourcelist->First();
  first_source->cd( path );
  TDirectory *current_sourcedir = gDirectory;

  // loop over all keys in this directory
  TIter nextkey( current_sourcedir->GetListOfKeys() );
  TKey *key;
  while (key = (TKey*)nextkey() ) {

    // read object from first source file
    first_source->cd( path );
    TObject *obj = key->ReadObj();

    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      // descendant of TH1 -> merge it

      //      cout << "Merging histogram " << obj->GetName() << endl;
      TH1 *h1 = (TH1*)obj;

      // loop over all source files and add the content of the
      // correspondant histogram to the one pointed to by "h1"
      TFile *nextsource = (TFile*)sourcelist->After( first_source );
      while ( nextsource ) {
	
	// make sure we are at the correct directory level by cd'ing to path
	nextsource->cd( path );
	TH1 *h2 = (TH1*)gDirectory->Get( h1->GetName() );
	if ( h2 ) {
	  h1->Add( h2 );
	  delete h2; // don't know if this is necessary, i.e. if 
                     // h2 is created by the call to gDirectory above.
	}

	nextsource = (TFile*)sourcelist->After( nextsource );
      }

    } else if ( obj->IsA()->InheritsFrom( "TDirectory" ) ) {
      // it's a subdirectory

      cout << "Found subdirectory " << obj->GetName() << endl;

      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );

      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      MergeRootfile( newdir, sourcelist );

    } else {
      // object is of no type that we know or can handle
      cout << "Unknown object type, name: " 
	   << obj->GetName() << " title: " << obj->GetTitle() << endl;
    }

    // now write the merged histogram (which is "in" obj) to the target file
    // note that this will just store obj in the current directory level,
    // which is not persistent until the complete directory itself is stored
    // by "target->Write()" below
    if ( obj ) {
      target->cd();
      obj->Write( key->GetName() );
    }

  } // while ( ( TKey *key = (TKey*)nextkey() ) )

  // save modifications to target file
  target->Write();

}

