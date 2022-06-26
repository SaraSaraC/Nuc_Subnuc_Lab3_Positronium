void Pos_Cal(TString Fname="../DATA/20m100a_A.dat"){
  TTree* tree = new TTree("tree","data from ascii file");
  tree->ReadFile(Form("%s",Fname.Data()),"ADC/F:Tn/F:Tf/F:E/F:DV/F:Rep/F:SBA/F:SNA/F:W/F:PV/F:FWHMBA/F:FWHMNA/F:SLOPE/F:SURFNA/F:PkNa/F:Analysis/F");

  tree->Draw("E:PV","","goff");
  TGraph* gra = new TGraph(tree->GetSelectedRows(),tree->GetV1(),tree->GetV2());
  TCanvas* c1 = new TCanvas();
  gra->Draw("ap");
  gra->SetMarkerStyle(8);
  gra->SetLineWidth(2);
  gPad->SetLogx();

  TF1* fpos = new TF1("fpos","[0] + [1]/(1+pow(x/[2],[3]))",0,30);
  fpos->SetParameter(0,0.01);
  fpos->SetParameter(1,0.04);
  fpos->SetParameter(2,10);
  fpos->FixParameter(3,1.6);
  gra->Fit("fpos");//Same weight for everyone
  
  gra->GetXaxis()->SetTitle("Energy [keV]");
  gra->GetYaxis()->SetTitle("PV");
	
	
  double E0=fpos->GetParameter(2);
  double dE0=fpos->GetParError(2);
  cout<<pow(E0,1.6)*40/2.2<<"nm"<<endl;
  return;
  }
