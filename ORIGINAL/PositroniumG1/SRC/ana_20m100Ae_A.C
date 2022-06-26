void ana_20m100Ae_A(TString Fname="../Data/ana_20m100Ae_A.ana"){
  TTree* tree = new TTree("tree","data from ascii file");
  tree->ReadFile(Form("%s",Fname.Data()),"ADC/F:Tn/F:Tf/F:E/F:DV/F:Rep/F:SBA/F:SNA/F:W/F:PV/F:FWHMBA/F:FWHMNA/F:SLOPE/F:SURFNA/F:PkNa/F:Analysis/F");



  
  tree->Draw("PV:E","","goff");
  TGraph* gra = new TGraph(tree->GetSelectedRows(),tree->GetV2(),tree->GetV1());
  TCanvas* c1 = new TCanvas();
  gra->Draw("ap");
  gra->SetMarkerStyle(8);
  gra->SetLineWidth(2);
  gPad->SetLogx();




  TF1* flin = new TF1("flin","[2]/(1+pow(x/[0],[1]))+[3]",0,30);
  flin->SetParameter(0,5);
  flin->FixParameter(1,1.6);
  flin->SetParameter(2,0.04);
  flin->SetParameter(3,0.01);

  gra->Fit("flin");
  gra->GetXaxis()->SetTitle("Energy [keV]");
  gra->GetYaxis()->SetTitle("PV");
  return;
  double p1=flin->GetParameter(1);
  double p0=flin->GetParameter(0);
 
  return;
  /////     error ///////
  TCanvas* c2 = new TCanvas();
  
  tree->Draw(Form("sig*%e:ene:(esig)*%e:ene*0.001",1/p1,1/p1),"","goff");
  TGraphErrors* gra2 = new TGraphErrors(tree->GetSelectedRows(),tree->GetV2(),tree->GetV1(),tree->GetV4(),tree->GetV3());
  gra2->Draw("ap");
  gra2->SetMarkerStyle(8);
  gra2->SetLineWidth(2);
  TF1* fsig = new TF1("fsig","sqrt([1]*[1]*x+[0]*[0])",0,1500);
  fsig->SetParameter(0,10);
  fsig->SetParameter(1,5);
  
  gra2->Fit("fsig");
  gra2->GetXaxis()->SetTitle("Energy [keV]");
  gra2->GetYaxis()->SetTitle("#sigma [keV]");

  cout << "expected sigma@ 662 keV = " << fsig->Eval(662) << endl;
  cout << "expected sigma@ 59.5 keV = " << fsig->Eval(59.5) << endl;

  cout << "Alias ENaI1 " << Form("(-A2+%e)*%e",-p0,1./p1) << endl;
  return;
}
