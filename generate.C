void generate()
{
    int n = 100; // liczba binów
    TH1F *hGaus = new TH1F("hgaus", "Rozklad gaussowski", n, -10, 10);
    TH1F *hUni = new TH1F("hUni", "Rozklad jednorodny", n, -10, 10);
    TH1F *hLand = new TH1F("hland", "Rozklad landaua", n, -10, 10);
    TH1F *hExp = new TH1F("hExp", "Rozklad eksponencjalny", n, -10, 10);
    THStack *hs = new THStack("hs", "rozklady");

    // #######################################################################
    // wypelnij histogramy
    for (int i = 0; i < 1e6; i++)
    {
        hGaus->Fill(gRandom->Gaus(0, 1));
        hUni->Fill(gRandom->Uniform(-10, 10));
        hLand->Fill(gRandom->Landau(0, 1));
        hExp->Fill(gRandom->Exp(-2));
    }

    // ################################################################
    // zbuduj legendę
    TLegend *leg = new TLegend(0.588825, 0.757991, 0.901146, 0.899543, "Rozklady");
    leg->AddEntry(hGaus, "Gauss ", "L");
    leg->AddEntry(hUni, "Jednorodny", "L");
    leg->AddEntry(hLand, "Landau", "L");
    leg->AddEntry(hExp, "Exponenta", "L");
    // ############################
    // ustaw ładne kolory i linie
    hGaus->SetLineColor(kBlack);
    hGaus->SetLineStyle(10);
    hGaus->SetLineWidth(2);
    hUni->SetLineColor(kBlue);
    hUni->SetLineStyle(8);
    hUni->SetLineWidth(2);
    hLand->SetLineColor(kGreen);
    hLand->SetLineStyle(5);
    hLand->SetLineWidth(2);
    hExp->SetLineColor(kRed);
    hExp->SetLineStyle(3);
    hExp->SetLineWidth(2);
    // ########################
    // dodaj do stacka
    hs->Add(hGaus);
    hs->Add(hUni);
    hs->Add(hLand);
    hs->Add(hExp);
    // #################
    // Narysuj
    auto cs = new TCanvas("cs", "cs", 10, 10, 700, 900);
    cs->cd();
    hs->Draw("nostack");
    leg->Draw();
}