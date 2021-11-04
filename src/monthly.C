#include "monthly.h"

Analyse_Monthly::Analyse_Monthly(Int_t month, std::string filename): _month{month},  _Wdata{filename} {}

void Analyse_Monthly::Temp_PerMonth(){	

	WeatherDataVec Monthly = _Wdata.get_by_month(_month); // all data of _month from the file with all of the years

	std::vector<int> year = Monthly.list_years(); // list of the years
	
	TH1D* h1 = new TH1D("h1", "Monthly temperatures distribution; Celsius; Counts", 150, -20, 30);// histogram that will store the monthly average temperatures data

	// fill the histogram with average monthly temperatures
	for (unsigned i = 0; i < year.size(); i++ ){
		WeatherDataVec A = Monthly.get_by_year(year[i]); 
		h1->Fill(A.avgtemp());
	}

	TCanvas *c1 = new TCanvas("c1","Monthly temperatures distribution",250,10,1200,600);

	TF1* fitfcn = new TF1("fitfcn", "gaus", -20, 30); // fitting function
	h1->Fit("fitfcn"); 
	h1->SetLineWidth(2);
	h1->GetXaxis()->SetTitleSize(0.03);
	h1->GetXaxis()->SetLabelSize(0.03);
	h1->GetYaxis()->SetTitleSize(0.03);
	h1->GetYaxis()->SetLabelSize(0.03);
	h1->Draw();

	// plot histogram
	TH1D *h2 = new TH1D("h2", "Monthly temperatures distribution; Temperature ^{o}C; Year Counts", 150, -20, 30);
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(h2);
	h2->SetFillColor(41); // yellow
	h2->GetXaxis()->SetTitleSize(0.03);
	h2->GetXaxis()->SetLabelSize(0.03);
	h2->GetYaxis()->SetTitleSize(0.03);
	h2->GetYaxis()->SetLabelSize(0.03);
	h2->Draw("e3");
	h1->Draw("same");

	// set legend
	TLegend *l1 = new TLegend(0.73, 0.847, 0.946, 0.945);
	l1->AddEntry(h1,"temp distribution","l");
	l1->AddEntry(fitfcn,"fit","l");
	l1->AddEntry(h2,"95% CI of fitting function","f");
	l1->Draw();
	c1->SaveAs("monthly1.pdf");
}


void Analyse_Monthly::Month_Extreme(){

	WeatherDataVec Monthly = _Wdata.get_by_month(_month); // all data of _month from the file all of the years
	Double_t highest = Monthly.maxtemp(); // the highest temp of _month over all of the year
	Double_t lowest = Monthly.mintemp(); // the lowest temp of _month over all of the year
	
	Int_t year_highest = 0;
	Int_t year_lowest = 0;
	Int_t counter1 = 1; 
	Int_t counter2 = 1; 
	// find the corresponding year of the highest/lowest temperature
	for (unsigned i = 0; i < Monthly.data.size(); i++ ){
		if ( (highest == Monthly.data[i].get_temp()) && (counter1 == 1) ){
			year_highest = Monthly.data[i].get_year();
			counter1--;
		}
		if ( (lowest == Monthly.data[i].get_temp()) && (counter2 == 1) ){
			year_lowest = Monthly.data[i].get_year();
			counter2--;
		}
		if ( (counter1 == 0) && (counter2 == 0))
			break; // stop loop if two years have been found
	}
	std::vector<int> year = Monthly.list_years(); // list of the years
	Int_t nYears = year.size(); // number of the years
	Double_t x[nYears], yH[nYears], yL[nYears], yA[nYears]; // x storing the years, yH storing the highest, yL storing the lowest, yA storing the average
	
	// store the temperatures in the arrays
	for (unsigned i = 0; i < year.size(); i++ ){
		WeatherDataVec A = Monthly.get_by_year(year[i]); 
		yA[i] = A.avgtemp();
		yH[i] = A.maxtemp();
		yL[i] = A.mintemp();
		x[i] = year[i];
	}

	std::cout << "\nThe highest temperature of this month is " << highest << " occuring in " << year_highest << std::endl;
	std::cout << "The lowest temperature of this month is " << lowest << " occuring in " << year_lowest << std::endl;
	
	TCanvas *c2 = new TCanvas("c2","Month Extreme Temperature",200,10,1000,600);
	TGraph* g1 = new TGraph(nYears, x, yH); // figure of the month highest temperature 
	TGraph* g2 = new TGraph(nYears, x, yL); // figure of the month lowest temperature 
	TGraph* g3 = new TGraph(nYears, x, yA); // figure of the month average temperature 
	TMultiGraph *mg = new TMultiGraph();
	TF1* fitfcn = new TF1("fitfcn", "pol1", x[0], x[nYears]); // fitting function for average temp
	mg->SetTitle("Month Extreme Temperature; Year; Temperature ^{o}C");
	g1->SetFillColor(46); // red
	g2->SetFillColor(38); // azure blue
	g3->SetLineWidth(3);
	g3->SetLineColor(12);
	g3->Fit("fitfcn");
	mg->Add(g1);
	mg->Add(g2);
	mg->Draw("AB");
	mg->GetXaxis()->SetTitleSize(0.03);
	mg->GetXaxis()->SetLabelSize(0.03);
	mg->GetYaxis()->SetTitleSize(0.03);
	mg->GetYaxis()->SetLabelSize(0.03);
	g3->Draw("same");

	// set legend
	TLegend *l1 = new TLegend(0.0051, 0.5178, 0.144, 0.652);
	l1->AddEntry(g1,"highest temp","f");
	l1->AddEntry(g2,"lowest temp","f");
	l1->AddEntry(g3,"average temp","l");
	l1->AddEntry(fitfcn,"linear fit","l");
	l1->Draw();

	c2->SaveAs("monthly2.pdf");
}
