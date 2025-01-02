
#include <iostream>
#include "binary_read.C"
#include "RewriteFile.C"

bool Is_Peak(double pik, float *dane, int i)
{
    bool is_peak = false;
    for (int j = 1; j < 10; j++)
    {
        if (pik > dane[i + j] && pik > dane[i - j])
        {
            is_peak = true;
        }
        else
        {

            is_peak = false;
            break;
        }
    }
    return is_peak;
}
int LowPeak(float *dane, int j, double *nmax, int n)
{
    int lowpeak;

    for (int i = 10; i < n; i++)
    {
        double pik = dane[i];
        if ((nmax[j] > dane[i]) && (dane[i] > nmax[j + 1]))
        {

            double pik = dane[i];
            if (Is_Peak(pik, dane, i))
            {
                nmax[j + 1] = pik;
                lowpeak = i;
            }
        }
    }
    return lowpeak;
}

void WidmoCsBin(string inputfile = "Cs-137.dat", string outputfile = "Cs137.bin")
{
    // READ FILE
    float dane[10000];
    fstream myfile;
    RewriteFile(inputfile, outputfile);
    myfile.open(outputfile, ios::binary | ios::in);
    int k = 0;

    binary_read(dane, "Cs137.bin");
    //  Histogram
    int n = 1024;
    double nmax[4] = {0, 0, 0, 0};
    double xmax[4];
    TH1F *hCes = new TH1F("hces", "Cs energy spectrum;kanal;liczba zliczen [au]", n, 0, 1024);
    TFile *rootfile = new TFile("CsWidmoBin.root", "RECREATE");
    TTree *tree = new TTree("piki", "wartosci pików");
    tree->Branch("nmax", &nmax, "nmax/D");
    tree->Branch("xmax", &xmax, "xmax/D");

    // ####################
    // HISTOGRAM FILLING
    for (int i = 0; i < n; i++)
    {
        hCes->SetBinContent(i+1, dane[i]);     // Fill histogram
        hCes->SetBinError(i+1, sqrt(dane[i])); // set bin error
    }

    for (int i = 10; i < n; i++)
    {
        if (nmax[0] < dane[i])
        {
            double pik = dane[i];
            if (Is_Peak(pik, dane, i))
            {
                nmax[0] = dane[i];
                xmax[0] = i;
            }
        }
    }
    for (int j = 0; j < 3; j++)
    {
        xmax[j + 1] = LowPeak(dane, j, nmax, n);
    }

    cout << "Pik: " << nmax[0] << " oto jego środek: " << xmax[0] << endl;

    cout << "Pik: " << nmax[1] << " oto jego środek: " << xmax[1] << endl;

    cout << "Pik: " << nmax[2] << " oto jego środek: " << xmax[2] << endl;
    cout << "Pik: " << nmax[3] << " oto jego środek: " << xmax[3] << endl;

    // ###################
    // HISTOGRAM DRAWING
    TCanvas *c1 = new TCanvas("k1", "k1", 0, 0, 1028, 1028);
    c1->cd();
    // gPad->SetLogy();
    hCes->SetLineWidth(2);
    hCes->SetLineColor(kBlack);
    hCes->GetXaxis()->SetRangeUser(0, 400);
    TLine *jakispik = new TLine(xmax[0], 200, xmax[0], 1400);
    TLine *fotopik = new TLine(xmax[1], 200, xmax[1], 1300);
    TLine *Compton = new TLine(170, 200, 170, 1400);
    TLine *pik = new TLine(xmax[2], 200, xmax[2], 1300);
    TText *t = new TText(xmax[1] + 10, 1300, "Fotopik");
    TText *t1 = new TText(170 + 10, 1400, "Zbocze komptonowskie");
    fotopik->SetLineWidth(3);
    fotopik->SetLineColor(kRed);
    Compton->SetLineWidth(3);
    pik->SetLineWidth(3);
    Compton->SetLineColor(kBlue);
    pik->SetLineColor(kGreen);
    jakispik->SetLineColor(kViolet);
    jakispik->SetLineWidth(3);
    gStyle->SetOptStat(0);
    t->SetTextColor(kRed);
    t->SetTextFont(43);
    t->SetTextSize(40);
    t1->SetTextColor(kBlue);
    t1->SetTextFont(43);
    t1->SetTextSize(40);

    // hCes->SetLineStyle(2);
    gPad->SetMargin(0.125, 0.125, 0.125, 0.125);
    hCes->Draw();
    c1->Update();
    t->Draw();
    t1->Draw();
    fotopik->Draw();
    Compton->Draw();
    pik->Draw();
    jakispik->Draw();
    hCes->Write();
    tree->Fill();
    rootfile->Write();
    c1->Write();
}
