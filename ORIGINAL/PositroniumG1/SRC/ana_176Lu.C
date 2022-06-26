void ana_176Lu(TString Fname="../Data/176Lu.asc"){
 TTree* tree = new TTree("tree","data from ascii file");

 tree->ReadFile(Form("%s",Fname.Data()),"N/F");  

 tree->Draw("N");

 double bins[10000];
 for (int i=0; i<10000; i++)
   bins[i]=i*1.;
 

  TGraph* gra = new TGraph(tree->GetSelectedRows(),bins,tree->GetV1());      
  TCanvas* c1 = new TCanvas();                                                        
  gra->Draw("ap");                                                                    
  gra->SetMarkerStyle(8);                                                             
  gra->SetLineWidth(2);                                                               

  gra->Fit("gaus","","",1500,2500);



  
  //  cout<<tree->GetSelectedRows();
 
  //  TGraph* h=new TGraph(Fname.Data());
  //h->Draw("ap");




}
