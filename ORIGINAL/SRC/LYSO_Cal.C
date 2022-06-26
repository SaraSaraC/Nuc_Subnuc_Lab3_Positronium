void LYSO_Cal(TString Fname="../DATA/176Lu.asc"){
  TTree* tree = new TTree("tree","data from ascii file");
  tree->ReadFile(Form("%s",Fname.Data()),"NN/I");

  tree->Draw("NN","","goff");
  double bin[10000];
  for(int i=0; i<10000;i++){bin[i]=i;}
  
  TGraph* gra = new TGraph(tree->GetSelectedRows(),bin,tree->GetV1());
  TCanvas* c1 = new TCanvas();
  gra->Draw("ap");
  gra->SetMarkerStyle(8);
  gra->SetLineWidth(2);
  gPad->SetLogy();

  TF1* fpos = new TF1("fpos","[0] + [1]*x + gaus(2)",0,10000);
  fpos->SetParameter(0,1);
  fpos->SetParameter(1,1/1000);
  fpos->SetParameter(2,100);
  fpos->SetParameter(3,2090);
  fpos->SetParameter(4,50);
  gra->Fit("fpos","L","",2050,2150);
  
  gra->GetXaxis()->SetTitle("Energy [keV]");
  gra->GetYaxis()->SetTitle("Counts");
	
	
  return;
  }
