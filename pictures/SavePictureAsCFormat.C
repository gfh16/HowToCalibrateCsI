void figure_LightEfficiency_TEL05_CSI00()
{
//=========Macro generated from canvas: c1/
//=========  (Wed Oct 17 20:13:03 2018) by ROOT version6.04/02
   TCanvas *c1 = new TCanvas("c1", "",1024,768);
   c1->Range(-3.28043,3.96343,-0.2966599,8.95369);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogx();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t Graph_fx1[18] = {
   0.00461995,
   0.00367583,
   0.00308495,
   0.00267921,
   0.0023828,
   0.00215645,
   0.00197777,
   0.00183301,
   0.00171329,
   0.00161257,
   0.00152665,
   0.00145246,
   0.00138774,
   0.00133078,
   0.00128027,
   0.00123515,
   0.00119461,
   0.00115799};
   Double_t Graph_fy1[18] = {
   6.3869,
   6.20501,
   6.06113,
   5.93568,
   5.82114,
   5.71352,
   5.61012,
   5.51111,
   5.41357,
   5.32032,
   5.23022,
   5.14008,
   5.05322,
   4.96741,
   4.88462,
   4.80243,
   4.72298,
   4.64392};
   TGraph *graph = new TGraph(18,Graph_fx1,Graph_fy1);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,0.000811794,0.004966146);
   Graph_Graph1->SetMinimum(4.469622);
   Graph_Graph1->SetMaximum(6.561198);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx2[17] = {
   0.00569391,
   0.00478161,
   0.00414409,
   0.0036729,
   0.00331005,
   0.00302174,
   0.00278697,
   0.00259194,
   0.00242726,
   0.00228628,
   0.00216421,
   0.00205742,
   0.00196319,
   0.00187942,
   0.00180444,
   0.00173691,
   0.00167578};
   Double_t Graph_fy2[17] = {
   6.51202,
   6.42825,
   6.35398,
   6.28428,
   6.21624,
   6.15094,
   6.08618,
   6.02138,
   5.95842,
   5.89725,
   5.8361,
   5.77618,
   5.71658,
   5.65801,
   5.60083,
   5.54376,
   5.48849};
   graph = new TGraph(17,Graph_fx2,Graph_fy2);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Graph",100,0.001273967,0.006095723);
   Graph_Graph2->SetMinimum(5.386137);
   Graph_Graph2->SetMaximum(6.614373);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx3[17] = {
   0.00776674,
   0.00658504,
   0.00573474,
   0.00509454,
   0.00459515,
   0.00419454,
   0.00386587,
   0.00359122,
   0.00335815,
   0.00315782,
   0.0029837,
   0.00283095,
   0.00269578,
   0.0025753,
   0.00246722,
   0.0023697,
   0.00228126};
   Double_t Graph_fy3[17] = {
   6.65595,
   6.6133,
   6.57401,
   6.53464,
   6.49453,
   6.45329,
   6.41163,
   6.37019,
   6.32603,
   6.28215,
   6.23949,
   6.19687,
   6.15318,
   6.1104,
   6.06792,
   6.02576,
   5.98414};
   graph = new TGraph(17,Graph_fx3,Graph_fy3);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","Graph",100,0.001732712,0.008315288);
   Graph_Graph3->SetMinimum(5.916959);
   Graph_Graph3->SetMaximum(6.723131);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3->SetLineColor(ci);
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetZaxis()->SetLabelFont(42);
   Graph_Graph3->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph3);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx4[17] = {
   0.0288235,
   0.0245294,
   0.0214281,
   0.0190842,
   0.0172497,
   0.0157738,
   0.0145601,
   0.0135436,
   0.0126798,
   0.0119361,
   0.0112889,
   0.0107204,
   0.010217,
   0.00976786,
   0.00936463,
   0.00900057,
   0.00867015};
   Double_t Graph_fy4[17] = {
   7.5443,
   7.55042,
   7.54551,
   7.52884,
   7.50169,
   7.46537,
   7.4202,
   7.37003,
   7.31379,
   7.25034,
   7.18627,
   7.11886,
   7.04864,
   6.97771,
   6.90428,
   6.83141,
   6.75713};
   graph = new TGraph(17,Graph_fx4,Graph_fy4);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#00cc00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","Graph",100,0.006654815,0.03083883);
   Graph_Graph4->SetMinimum(6.677801);
   Graph_Graph4->SetMaximum(7.629749);
   Graph_Graph4->SetDirectory(0);
   Graph_Graph4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph4->SetLineColor(ci);
   Graph_Graph4->GetXaxis()->SetLabelFont(42);
   Graph_Graph4->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleFont(42);
   Graph_Graph4->GetYaxis()->SetLabelFont(42);
   Graph_Graph4->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleFont(42);
   Graph_Graph4->GetZaxis()->SetLabelFont(42);
   Graph_Graph4->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph4);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx5[16] = {
   0.0294601,
   0.0258699,
   0.0231142,
   0.020934,
   0.019166,
   0.0177029,
   0.0164717,
   0.0154208,
   0.0145131,
   0.013721,
   0.0130233,
   0.0124041,
   0.0118506,
   0.0113529,
   0.0109028,
   0.0104936};
   Double_t Graph_fy5[16] = {
   7.54143,
   7.59273,
   7.62823,
   7.64888,
   7.65599,
   7.65272,
   7.63885,
   7.61666,
   7.58737,
   7.55144,
   7.51115,
   7.46731,
   7.41884,
   7.36931,
   7.31617,
   7.26175};
   graph = new TGraph(16,Graph_fx5,Graph_fy5);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#00cc00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph5 = new TH1F("Graph_Graph5","Graph",100,0.00859695,0.03135675);
   Graph_Graph5->SetMinimum(7.222326);
   Graph_Graph5->SetMaximum(7.695414);
   Graph_Graph5->SetDirectory(0);
   Graph_Graph5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph5->SetLineColor(ci);
   Graph_Graph5->GetXaxis()->SetLabelFont(42);
   Graph_Graph5->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetXaxis()->SetTitleFont(42);
   Graph_Graph5->GetYaxis()->SetLabelFont(42);
   Graph_Graph5->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetYaxis()->SetTitleFont(42);
   Graph_Graph5->GetZaxis()->SetLabelFont(42);
   Graph_Graph5->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph5);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx6[15] = {
   0.0391658,
   0.0356264,
   0.0326948,
   0.0302212,
   0.028114,
   0.0263,
   0.024723,
   0.0233398,
   0.022117,
   0.0210281,
   0.0200522,
   0.0191726,
   0.0183757,
   0.0176501,
   0.0169867};
   Double_t Graph_fy6[15] = {
   7.31148,
   7.4018,
   7.49197,
   7.56846,
   7.63328,
   7.68928,
   7.73553,
   7.77355,
   7.80473,
   7.82646,
   7.84381,
   7.85644,
   7.86164,
   7.86492,
   7.86164};
   graph = new TGraph(15,Graph_fx6,Graph_fy6);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#00cc00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph6 = new TH1F("Graph_Graph6","Graph",100,0.01476879,0.04138371);
   Graph_Graph6->SetMinimum(7.256136);
   Graph_Graph6->SetMaximum(7.920264);
   Graph_Graph6->SetDirectory(0);
   Graph_Graph6->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph6->SetLineColor(ci);
   Graph_Graph6->GetXaxis()->SetLabelFont(42);
   Graph_Graph6->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetXaxis()->SetTitleFont(42);
   Graph_Graph6->GetYaxis()->SetLabelFont(42);
   Graph_Graph6->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetYaxis()->SetTitleFont(42);
   Graph_Graph6->GetZaxis()->SetLabelFont(42);
   Graph_Graph6->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph6);
   
   multigraph->Add(graph,"");
      
   Double_t Graph_fx7[18] = {
   0.126708,
   0.107538,
   0.0941192,
   0.0851317,
   0.0777519,
   0.0716094,
   0.066411,
   0.0619585,
   0.0581056,
   0.0547406,
   0.0517768,
   0.0491466,
   0.0467968,
   0.0446846,
   0.0427756,
   0.0410416,
   0.0394595,
   0.03801};
   Double_t Graph_fy7[18] = {
  5.472081224,
  6.074440964,
  6.496086498,
  6.778491723,
  7.010379798,
  7.203389433,
   7.38091,
   7.50534,
   7.61914,
   7.72425,
   7.81932,
   7.90679,
   7.98432,
   8.05463,
   8.11778,
   8.17424,
   8.22348,
   8.26712};
   graph = new TGraph(18,Graph_fx7,Graph_fy7);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#3399ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph7 = new TH1F("Graph_Graph7","Graph",100,0.0291402,0.1355778);
   Graph_Graph7->SetMinimum(5.988888);
   Graph_Graph7->SetMaximum(8.474232);
   Graph_Graph7->SetDirectory(0);
   Graph_Graph7->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph7->SetLineColor(ci);
   Graph_Graph7->GetXaxis()->SetLabelFont(42);
   Graph_Graph7->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetXaxis()->SetTitleFont(42);
   Graph_Graph7->GetYaxis()->SetLabelFont(42);
   Graph_Graph7->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetYaxis()->SetTitleFont(42);
   Graph_Graph7->GetZaxis()->SetLabelFont(42);
   Graph_Graph7->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph7);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx8[17] = {
   0.116968,
   0.102605,
   0.0918138,
   0.0845054,
   0.0780971,
   0.0726328,
   0.0679192,
   0.0638118,
   0.0602049,
   0.0570139,
   0.0541717,
   0.051624,
   0.0493277,
   0.0472472,
   0.0453533,
   0.043622,
   0.042033  };
   Double_t Graph_fy8[17] = {
   5.71290288 ,
   6.1989468  ,
   6.564121008,
   6.811437264,
   7.07382,
   7.22149,
   7.35981,
   7.48886,
   7.60738,
   7.71848,
   7.82013,
   7.91333,
   7.99997,
   8.07775,
   8.14919,
   8.21454,
   8.2732 };
   graph = new TGraph(17,Graph_fx8,Graph_fy8);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#3399ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph8 = new TH1F("Graph_Graph8","Graph",100,0.0325029,0.1468641);
   Graph_Graph8->SetMinimum(5.769314);
   Graph_Graph8->SetMaximum(8.500826);
   Graph_Graph8->SetDirectory(0);
   Graph_Graph8->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph8->SetLineColor(ci);
   Graph_Graph8->GetXaxis()->SetLabelFont(42);
   Graph_Graph8->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph8->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph8->GetXaxis()->SetTitleFont(42);
   Graph_Graph8->GetYaxis()->SetLabelFont(42);
   Graph_Graph8->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph8->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph8->GetYaxis()->SetTitleFont(42);
   Graph_Graph8->GetZaxis()->SetLabelFont(42);
   Graph_Graph8->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph8->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph8->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph8);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx9[17] = {
   0.12559,
   0.110389,
   0.0989672,
   0.0901562,
   0.0838739,
   0.0782209,
   0.0733033,
   0.0689971,
   0.0651932,
   0.0618132,
   0.0587914,
   0.0560743,
   0.0536186,
   0.0513883,
   0.049354,
   0.0474907,
   0.0457778};
   Double_t Graph_fy9[17] = {
   5.43341321 ,
   5.960599091,
   6.356718537,
   6.662292828,
   6.91299,
   7.06952,
   7.21686,
   7.35571,
   7.48571,
   7.60788,
   7.72205,
   7.82804,
   7.9255,
   8.01622,
   8.10026,
   8.17848,
   8.24809};
   graph = new TGraph(17,Graph_fx9,Graph_fy9);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#3399ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph9 = new TH1F("Graph_Graph9","Graph",100,0.03565828,0.1570925);
   Graph_Graph9->SetMinimum(5.579237);
   Graph_Graph9->SetMaximum(8.490713);
   Graph_Graph9->SetDirectory(0);
   Graph_Graph9->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph9->SetLineColor(ci);
   Graph_Graph9->GetXaxis()->SetLabelFont(42);
   Graph_Graph9->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetXaxis()->SetTitleFont(42);
   Graph_Graph9->GetYaxis()->SetLabelFont(42);
   Graph_Graph9->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetYaxis()->SetTitleFont(42);
   Graph_Graph9->GetZaxis()->SetLabelFont(42);
   Graph_Graph9->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph9);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx10[18] = {
   0.216595,
   0.187956,
   0.16691,
   0.152378,
   0.140163,
   0.129874,
   0.121036,
   0.113376,
   0.106685,
   0.100794,
   0.0955712,
   0.0909089,
   0.0867222,
   0.082942,
   0.0795118,
   0.076385,
   0.0735229,
   0.0708931};
   Double_t Graph_fy10[18] = {
   5.13823,
   5.51179,
   5.80367,
   6.07738,
   6.29378,
   6.49432,
   6.65571,
   6.82037,
   6.97348,
   7.11857,
   7.25636,
   7.38727,
   7.51104,
   7.62628,
   7.73633,
   7.83939,
   7.93643,
   8.0277};
   graph = new TGraph(18,Graph_fx10,Graph_fy10);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff00ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph10 = new TH1F("Graph_Graph10","Graph",100,0.05632291,0.2311652);
   Graph_Graph10->SetMinimum(4.849283);
   Graph_Graph10->SetMaximum(8.316647);
   Graph_Graph10->SetDirectory(0);
   Graph_Graph10->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph10->SetLineColor(ci);
   Graph_Graph10->GetXaxis()->SetLabelFont(42);
   Graph_Graph10->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph10->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph10->GetXaxis()->SetTitleFont(42);
   Graph_Graph10->GetYaxis()->SetLabelFont(42);
   Graph_Graph10->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph10->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph10->GetYaxis()->SetTitleFont(42);
   Graph_Graph10->GetZaxis()->SetLabelFont(42);
   Graph_Graph10->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph10->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph10->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph10);
   
   multigraph->Add(graph,"");
   
   Double_t Graph_fx11[18] = {
   0.242032,
   0.211421,
   0.188607,
   0.170894,
   0.15745,
   0.146887,
   0.137584,
   0.129363,
   0.122113,
   0.115667,
   0.109906,
   0.10473,
   0.100056,
   0.0958155,
   0.0919513,
   0.0884158,
   0.0851689,
   0.0821765};
   Double_t Graph_fy11[18] = {
   4.78428,
   5.15432,
   5.44487,
   5.68689,
   5.93258,
   6.11441,
   6.29704,
   6.4987,
   6.64424,
   6.80292,
   6.9551,
   7.1012,
   7.24144,
   7.37654,
   7.50453,
   7.62814,
   7.74473,
   7.85556};
   graph = new TGraph(18,Graph_fx11,Graph_fy11);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff00ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_Graph11 = new TH1F("Graph_Graph11","Graph",100,0.06619095,0.2580175);
   Graph_Graph11->SetMinimum(4.477152);
   Graph_Graph11->SetMaximum(8.162688);
   Graph_Graph11->SetDirectory(0);
   Graph_Graph11->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11->SetLineColor(ci);
   Graph_Graph11->GetXaxis()->SetLabelFont(42);
   Graph_Graph11->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11->GetXaxis()->SetTitleFont(42);
   Graph_Graph11->GetYaxis()->SetLabelFont(42);
   Graph_Graph11->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11->GetYaxis()->SetTitleFont(42);
   Graph_Graph11->GetZaxis()->SetLabelFont(42);
   Graph_Graph11->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph11);
   
   multigraph->Add(graph,"");
   multigraph->Draw("AL");
   multigraph->GetXaxis()->SetTitle("-dE/dx (MeV/#mum)");
   multigraph->GetXaxis()->CenterTitle(true);
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.05);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("dL/dE (a.u.)");
   multigraph->GetYaxis()->CenterTitle(true);
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.05);
   multigraph->GetYaxis()->SetTitleFont(42);
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
   
   TLatex * Label1 = new TLatex (0.0011,5.1,"^{1}H");
   TLatex * Label2 = new TLatex (0.0016,5.8,"^{2}H");
   TLatex * Label3 = new TLatex (0.0022,6.26,"^{3}H");
   TLatex * Label4 = new TLatex (0.0063,6.96,"^{3}He");
   TLatex * Label5 = new TLatex (0.010,7.61,"^{4}He");
   TLatex * Label6 = new TLatex (0.016,7.93,"^{6}He");
   TLatex * Label7 = new TLatex (0.05,8.1,"^{6,7,8}Li");
   TLatex * Label11 = new TLatex (0.094,7.5,"^{7,9}Be");
   
   Label1 ->SetTextColor(kRed);
   Label2 ->SetTextColor(kRed);
   Label3 ->SetTextColor(kRed);
   Label4 ->SetTextColor(kGreen+1);
   Label5 ->SetTextColor(kGreen+1);
   Label6 ->SetTextColor(kGreen+1);
   Label7 ->SetTextColor(kAzure+1);
   Label11->SetTextColor(kMagenta);
   
   Label1 ->Draw("SAME");
   Label2 ->Draw("SAME");
   Label3 ->Draw("SAME");
   Label4 ->Draw("SAME");
   Label5 ->Draw("SAME");
   Label6 ->Draw("SAME");
   Label7 ->Draw("SAME");
   Label11->Draw("SAME");
   
}
