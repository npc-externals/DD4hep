// $Id: Geant4Data.h 513 2013-04-05 14:31:53Z gaede $
//====================================================================
//  AIDA Detector description implementation
//--------------------------------------------------------------------
//
//  Define the ROOT dictionaries for all data classes to be saved 
//  which are created by the DDG4 examples.
//
//  Author     : M.Frank
//
//====================================================================
#include "DD4hep/LCDD.h"
#include "TGeoManager.h"
#include "TEveGeoNode.h"
#include "TGLViewer.h"
#include "TGLUtil.h"
#include "TGLClip.h"
#include "TMap.h"
#include "TEveElement.h"
#include "TSysEvtHandler.h"
#include "TTimer.h"
#include "TVirtualPad.h"

#define private public
#include "TEveManager.h"

using namespace DD4hep::Geometry;

void TEve()    {
  LCDD& lcdd = LCDD::getInstance();
  const char* fname = "file:../DD4hep.trunk/DDExamples/CLICSiD/compact/compact.xml";
  lcdd.apply("DD4hepCompactLoader",1,(char**)&fname);

  TEveManager::Create();
  //TFile::SetCacheFileDir(".");
  //gGeoManager = gEve->GetGeometry("LHCb.gdml");
  //gGeoManager = gEve->GetGeometry("lhcbfull_v1.root");

  gEve->fGeometries->Add(new TObjString(fname),&lcdd.manager());
  //gGeoManager->DefaultColors();

  TEveGeoTopNode* tn = new TEveGeoTopNode(gGeoManager, gGeoManager->GetTopNode());
  tn->SetVisLevel(4);
  gEve->AddGlobalElement(tn);

  gEve->FullRedraw3D(kTRUE);

  // EClipType not exported to CINT (see TGLUtil.h):
  // 0 - no clip, 1 - clip plane, 2 - clip box
  TGLViewer *v = gEve->GetDefaultGLViewer();
  v->GetClipSet()->SetClipType(TGLClip::kClipPlane);
  v->ColorSet().Background().SetColor(kMagenta+4);
  v->SetGuideState(TGLUtil::kAxesEdge, kTRUE, kFALSE, 0);
  v->RefreshPadEditor(v);
  v->CurrentCamera().RotateRad(-1.2, 0.5);
  v->DoDraw();
}