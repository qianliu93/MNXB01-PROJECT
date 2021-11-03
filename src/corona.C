#include "corona.h"

Analyse_Corona::Analyse_Corona(std::string city, std::string filename): _city{city}, _filename{filename}{
	Plot_Corona();//plot the figure of the relation between the temperature and number of people infected with the COVID-19 when a new object is created.
}


void Analyse_Corona::Plot_Corona() const{
	std::string fname = "../datasets/Covid Data/Covid_" + _city + ".csv";

	std::ifstream file;
	file.open(fname);
	Int_t veck1[58];
	Int_t antal[58];
	Double_t veck2[58];

	Int_t i1 = 0;
	std::string yearstring, weekstring, numberstring;
	Int_t year = 0;
	Int_t week = 0;
	std::string city;
	Int_t number = 0;
	std::string fileline;
	std::getline(file, fileline); // the first line will be ignored

    std::regex re("(<|>)");
    while(std::getline(file, fileline)) {
        std::vector<std::string> rawsplit(string_split(std::regex_replace(fileline, re, ""), ","));
        int year = std::stoi(rawsplit[0]);
        int week = std::stoi(rawsplit[1]);
        int number = std::stoi(rawsplit[3]);
        if( (year == 2020 && week >= 9) || (year == 2021 && week <= 13) ){
            veck1[i1] = i1;
            veck2[i1] = i1;
            antal[i1] = number;
            i1++;
        }
    }


	WeatherDataVec Wdata {"../datasets/" + _filename};
    std::cout << "Loaded data (with " << Wdata.data.size() << " entries)." << std::endl;

	Double_t temp[58];
	// set the begining date and the due date we want to analyse
	int frYear = 2020;
	int frMonth = 2;
	int frDay = 24;
	int toYear = 2021;
	int toMonth = 4;
	int toDay = 4;
	int _i = 0; // counter

	// equivalent to old code: this has been checked. ("my kind request" - DF) - CF
    // load data between the begining date and end date
	WeatherDataVec Wbetween = Wdata.get_between(frYear,frMonth,frDay,toYear,toMonth,toDay);
    // average the temperature on each day
    Wbetween = Wbetween.avg_by_day();
	Gregorian counter_date {frYear,frMonth,frDay};
	std::vector<double> tempvec;
    // compute averages over the weeks
	while(counter_date < Gregorian(toYear,toMonth,toDay)){
        double avg_temp = Wbetween.get_between(counter_date.get_datestr(),(counter_date+6).get_datestr()).avgtemp();
		tempvec.push_back(avg_temp);
		counter_date = counter_date + 7;
	}
    // insert computed data into temp
	for(int i = 0 ; i < tempvec.size(); i++){
		temp[i] = tempvec[i];
	}

	TCanvas *c3 = new TCanvas("c3","Temperature & Corona",200,10,1200,600);
	TGraph* g1 = new TGraph(58, veck1, antal); // figure of the number of infected people
	TGraph* g2 = new TGraph(58, veck2, temp); // figure of the weekly average temperature
	TPad *pad1 = new TPad("pad1","",0,0,1,1);
	TPad *pad2 = new TPad("pad2","",0,0,1,1);
	pad2->SetFillStyle(4000); // the window is transparent
	pad2->SetFrameFillStyle(0); // hollow
	g1->SetFillColor(46); // red
	g1->SetTitle("Temperature & Corona");
	g1->GetYaxis()->SetLabelColor(46);
	g1->GetYaxis()->SetLabelSize(0.03); // default 0.04
	g1->GetYaxis()->SetTitle("Counts");
	g1->GetYaxis()->SetTitleColor(46);
	g1->GetYaxis()->SetTitleSize(0.03); // default 0.04
	g1->GetXaxis()->SetRangeUser(0, 62);
	g1->GetXaxis()->SetTitle("Weeks");
	g1->GetXaxis()->SetTitleSize(0.03); // default 0.04
	g1->GetXaxis()->SetLabelSize(0.03); // default 0.04
	g1->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"2020/9");	// change the original x-axis to the week we need
	g1->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"19");
	g1->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"29");
	g1->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"39");
	g1->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"49");
	g1->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"2021/6");
	g1->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"16");	
	g2->SetLineColor(9); // purple
	g2->SetLineWidth(3);
	g2->GetXaxis()->SetTickLength(0);
	g2->GetXaxis()->SetLabelOffset(999);
	g2->GetXaxis()->SetLabelSize(0);
	g2->GetYaxis()->SetLabelColor(9);
	g2->GetYaxis()->SetLabelSize(0.03); // default 0.04
	g2->GetYaxis()->SetTitle(" ^{o}C");
	g2->GetYaxis()->SetTitleColor(9);
	g2->GetYaxis()->SetTitleSize(0.03); // default 0.04
	pad1->Draw();
	pad1->cd();
	g1->Draw("AB, Y+"); //a bar chart(B) is drawn with axis(A) on the right side(Y+) of the plot
	pad2->Draw();
	pad2->cd();
	g2->Draw();

	TLegend *l1 = new TLegend(0.28, 0.273, 0.5, 0.436);
	l1->AddEntry(g1,"number of people infected","f");
	l1->AddEntry(g2,"average temp","l");
	l1->Draw();
}
