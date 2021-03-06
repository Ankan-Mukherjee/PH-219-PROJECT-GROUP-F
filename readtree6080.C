﻿/*
*   VARIABLES USED:
*   
    ╔══════════╤════════════════╤══════════╤═══════════════════════════════════════════════════════════╗
    ║ VARIABLE │   DATA TYPE    │   SIZE   │                        DESCRIPTION                        ║
    ╠══════════╪════════════════╪══════════╪═══════════════════════════════════════════════════════════╣
    ║    a     │   char array   │ 1*length │                 Stores the names of trees                 ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║    a1    │   char array   │ 1*length │                                                           ║
    ╟──────────┼────────────────┼──────────┤                                                           ║
    ║    a2    │   char array   │ 1*length │                                                           ║
    ╟──────────┼────────────────┼──────────┤                                                           ║
    ║    b1    │   char array   │ 1*length │                                                           ║
    ╟──────────┼────────────────┼──────────┤     Auxiliary variables for creating histogram titles     ║
    ║    b2    │   char array   │ 1*length │                                                           ║
    ╟──────────┼────────────────┼──────────┤                                                           ║
    ║    k1    │      int       │    -     │                                                           ║
    ╟──────────┼────────────────┼──────────┤                                                           ║
    ║    k2    │      int       │    -     │                                                           ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║    f     │     TFile*     │    -     │           Stores the file name of the ROOT file           ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║   tree   │     TTree*     │    -     │                  Stores the current tree                  ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║ entries  │     Int_t      │    -     │        Total number of entries in the current tree        ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║ maxTrack │     Int_t      │    -     │ Maximum size of array containing pT for each event, 10000 ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║    c2    │                │          │                Canvas for Histogram of pT                 ║
    ╟──────────┤    TCanvas*    │    -     ├───────────────────────────────────────────────────────────╢
    ║    c6    │                │          │              Canvas for Histogram of mean pT              ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║  ntrack  │     Int_t      │    -     │            Number of data points in each event            ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║    pT    │ Double_t array │ maxTrack │        Array for Transverse Momentum of each event        ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║    NT    │ Double_t array │ entries  │        Array of ntrack corresponding to each event        ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║  hmult   │                │          │                Histogram for multiplicity                 ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────╢
    ║   hpT    │     TH1D*      │    -     │                     Histogram for pT                      ║
    ╟──────────┤                │          ├───────────────────────────────────────────────────────────╢
    ║   hpTm   │                │          │                   Histogram for mean pT                   ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║    ii    │     Int_t      │    -     │                 Loop variable for events                  ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║  ntrks   │     Int_t      │    -     │      Temporarily stores ntrack for the current event      ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║  store   │    Double_t    │    -     │     Temporarily stores mean pT for the current event      ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║   gaus   │                │          │                 Function for Gaussian fit                 ║
    ╟──────────┤      TF1*      │    -     ├───────────────────────────────────────────────────────────╢
    ║   expo   │                │          │               Function for Exponential fit                ║
    ╟──────────┼────────────────┼──────────┼───────────────────────────────────────────────────────────╢
    ║ legend1  │                │          │                 Legend for histogram hpT                  ║
    ╟──────────┤    TLegend*    │    -     ├───────────────────────────────────────────────────────────╢
    ║ legend2  │                │          │                 Legend for histogram hpTm                 ║
    ╚══════════╧════════════════╧══════════╧═══════════════════════════════════════════════════════════╝

*   
*/

void readtree6080()
{
  
  /*********************************************************************
    _____________________________________________
    |   READING THE TREE                        |
    |   CHANGE TREE NAME AS PER CONVENIENCE     |
    |   entries = NUMBER OF ENTRIES             |
    |___________________________________________|

  ***********************************************************************/

  /*********************************************************************

  TREES AVAILABLE:

  pytree;100
  pytree;99
  pytree2040;28
  pytree2040;27
  pytree4060;24
  pytree4060;23
  pytree020;24
  pytree020;23
  pytree6080;16
  pytree6080;15
  pytree80100;7
  pytree80100;6
  pytree100;3
  pytree100;2

  *********************************************************************/

  char a[]="pytree6080";

  TFile *f=new TFile("13TeV_CR0_RHoff.root");
  TTree *tree = (TTree*)f->Get(a);
  Int_t entries = tree->GetEntries();

  const Int_t maxTrack=10000;


  /*********************************************************************
    _____________________________________________
    |   CREATING HISTOGRAMS TITLES              |
    |___________________________________________|

  *********************************************************************/


  char a1[]="Histogram for pT for ";
  char a2[]="Histogram for <pT> for ";
  char b1[100];
  char b2[100];
  int k1=0;
  int k2=0;
  while (a1[k1] != '\0') 
  { 
        b1[k2] = a1[k1]; 
        k1++; 
        k2++; 
  } 
  k1 = 0; 
  while (a[k1] != '\0') 
  { 
      b1[k2] = a[k1]; 
      k1++; 
      k2++; 
  } 
  b1[k2]='\0';

  k1=0;
  k2=0;
  while (a2[k1] != '\0') 
  { 
        b2[k2] = a2[k1]; 
        k1++; 
        k2++; 
  } 
  k1 = 0; 
  while (a[k1] != '\0') 
  { 
      b2[k2] = a[k1]; 
      k1++; 
      k2++; 
  } 
  b2[k2]='\0';


  





  /*********************************************************************
    _____________________________________________
    |   DEFINING THE CANVASES                   |
    |   CANVAS c2: TRANSVERSE MOMENTUM          |
    |   CANVAS c6: MEAN TRANSVERSE MOMENTUM     |
    |___________________________________________|

  *********************************************************************/

  TCanvas *c2=new TCanvas("c2","Transverse Momentum",200,10,800,600);
  TCanvas *c6=new TCanvas("c6","Mean Transverse Momentum",200,10,800,600);






  /*********************************************************************
    _____________________________________________
    |   INITIALISING THE CORRESPONDING ARRAYS,  |
    |   TREES AND HISTOGRAMS                    |
    |___________________________________________|

  *********************************************************************/
   
  Int_t ntrack = 0;
  Double_t pT[maxTrack];
  Double_t NT[entries];


  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("pT",&pT);
 


  TH1D *hmult =  new TH1D("hmult","Multiplicity",100,0,100.0);
  TH1D *hpT   =  new TH1D("hpT","Transverse Momentum", 100,0,3.0);
  TH1D *hpTm   =  new TH1D("hpTm","Mean Transverse Momentum", 100,0,3.0);




  /*********************************************************************
    _____________________________________________
    |   FILLING THE HISTOGRAMS                  |
    |___________________________________________|

  *********************************************************************/

  for(Int_t ii=0; ii<entries; ii++)  
  {//Event loop starts here
           
        tree->GetEntry(ii);
        Int_t ntrks = ntrack;
        NT[ii]=ntrks;
        hmult->Fill(ntrks);
        for(int i=0;i<ntrks;i++)
        {
            hpT->Fill(pT[i]);
        }
        Double_t store=TMath::Mean(pT,pT+ntrks);
        hpTm->Fill(store);
  }
  cout<<"\n\n"<<a<<"\n\n"<<endl;

  
  
  
  
  
  /*********************************************************************
    _____________________________________________
    |   AESTHETICS OF THE HISTOGRAMS            |
    |___________________________________________|

  *********************************************************************/

  hpT->SetTitle(b1);
  hpT->GetXaxis()->SetTitle("pT (GeV/c)");
  hpT->GetYaxis()->SetTitle("Count");
  hpT->SetLineColor(kBlue);
  hpT->SetFillColor(kCyan-10);
  hpT->SetStats(0);
  hpTm->SetTitle(b2);
  hpTm->GetXaxis()->SetTitle("<pT> (GeV/c)");
  hpTm->GetYaxis()->SetTitle("Count");
  hpTm->SetLineColor(kBlue);
  hpTm->SetFillColor(kCyan-10);
  hpTm->SetStats(0);





    /*********************************************************************
    _____________________________________________
    |   FITTING THE HISTOGRAMS                  |
    |___________________________________________|

  *********************************************************************/

   TF1 *gaus=new TF1("gaus","gaus",-0.5,0.5);
   gaus->SetParameters(hpTm->GetMaximum(), hpTm->GetMean(), hpTm->GetRMS()); 
   gaus->SetLineColor(kRed);
   hpTm->Fit("gaus");
   TF1 *expo=new TF1("expo","expo",-0.5,0.5);
   expo->SetParameters(hpT->GetMean(), -hpT->GetMean()); 
   expo->SetLineColor(kRed);
   hpT->Fit("expo");


   /*********************************************************************
    _____________________________________________
    |   DEFINING THE LEGEND                     |
    |___________________________________________|

  *********************************************************************/



   TLegend *legend1 = new TLegend(0.45,0.7,0.9,0.9);
   legend1->SetHeader("Legend","C");
   legend1->AddEntry(hpT,"Histogram for pT","f");
   legend1->AddEntry(expo,"Exponential Fit","l");
   legend1->SetFillColor(kYellow-10);
   TLegend *legend2 = new TLegend(0.45,0.7,0.9,0.9);
   legend2->SetHeader("Legend","C");
   legend2->AddEntry(hpT,"Histogram for <pT>","f");
   legend2->AddEntry(gaus,"Gaussian Fit","l");
   legend2->SetFillColor(kYellow-10);
   


  /*********************************************************************
    _____________________________________________
    |   DRAWING THE HISTOGRAMS                  |
    |___________________________________________|

  *********************************************************************/

  c2->cd();
  c2->SetLogy();
  hpT->Draw();
  legend1->Draw();
  c6->cd();
  c6->SetLogy();
  hpTm->Draw();
  legend2->Draw();





}


/*********************************END**********************************/