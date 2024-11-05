//Zofia Juda, 05.11.2024
#include <iostream>
using namespace std;

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
void WidmoCs(string name = "Cs-137.dat")
{
    // ###############################################3
    // Czytanie plików i wpisywanie ich w tablice
    ifstream file; //= ifstream("1.lst", ios_base::in);

    int nbins = 1024;

    TH1F *hCes = new TH1F("hces", "Cs spektrum energetyczne;kanal [au];liczba zliczen", nbins, 0, 1024);

    int j = 0;
    float dane[nbins];
    // otwieranie i czytanie z pliku
    file.open(name, ios_base::in);
    if (file.is_open())
    {
        string line;
        while (!file.eof())
        {
            getline(file, line);
            // cout << line << endl;
            stringstream ss(line);
            ss >> dane[j];
            // wypelnianie histogramu
            hCes->SetBinContent(j, dane[j]);
            hCes->SetBinError(j, sqrt(dane[j]));
            j++;
        }
        file.close();

        // rysowanie na kanwie
        TCanvas *c1 = new TCanvas("k1", "k1", 0, 0, 1028, 1028);
        c1->cd();
        hCes->SetLineWidth(3);
        hCes->SetLineColor(kBlack);
        hCes->GetXaxis()->SetRangeUser(0, 400);
        // ################################################
        // Dodatki i ulepszenia znajdź piki samodzielnie
        double nmax[4] = {0, 0, 0, 0};
        double xmax[4];
        for (int i = 10; i < nbins; i++)
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
            xmax[j + 1] = LowPeak(dane, j, nmax, nbins);
        }

        cout << "oto największa liczba zliczeń: " << nmax[0] << " oto jego środek: " << xmax[0] << endl;

        cout << "oto największa liczba zliczeń: " << nmax[1] << " oto jego środek: " << xmax[1] << endl;

        cout << "oto największa liczba zliczeń: " << nmax[2] << " oto jego środek: " << xmax[2] << endl;
        cout << "oto największa liczba zliczeń: " << nmax[3] << " oto jego środek: " << xmax[3] << endl;
        // ####################
        // ustawienia dla linii
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
        // ###############
        // narysuj wszystko
        hCes->GetYaxis()->SetTitle("liczba zliczen");
        gPad->SetMargin(0.125, 0.125, 0.125, 0.125);
        hCes->GetYaxis()->SetMaxDigits(2);
        hCes->Draw();
        c1->SetGrid();
        c1->Update();
        t->Draw();
        t1->Draw();
        fotopik->Draw();
        Compton->Draw();
        pik->Draw();
        jakispik->Draw();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}
