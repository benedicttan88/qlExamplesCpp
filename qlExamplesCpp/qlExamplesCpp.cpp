// qlExamplesCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>

#include <fstream>
#include <iomanip>

#include <ql/quantlib.hpp>

#include <boost/timer.hpp>
#include <boost/make_shared.hpp>


using namespace std;
using namespace QuantLib;


void survivalcurve();
void Output(string output_path, std::vector<Date> CDS_Dates);
std::vector<pair<Period, Rate>> read_cds_spreads(string input_path);





void Output(string output_path , std::vector<Date> CDS_Dates) {

	ofstream outfile(output_path);

	outfile << "CDS Dates" << "\n";

	for (Date i : CDS_Dates) {
		outfile << i.serialNumber() << "\n";
	}

}

std::vector<pair<Period,Rate>> read_cds_spreads(string input_path) {

	std::vector<pair<Period, Rate>> vec;

	ifstream infile(input_path);

	string temp1;
	double temp2;

	if (infile.good()) {

		string line;
		std::istringstream ss(line);
		
		while (getline(infile, line)) {

			istringstream ss(line);

			cout << line << endl;
		}


	}


	while (infile >> temp1 >> temp2) {

		cout << temp1 << endl;
		cout << temp2 << endl;

		if (temp1.back() == 'M') {
			Period period((int) 5, Months);
			vec.push_back(make_pair(period, temp2));
		}
		else if (temp1.back() == 'Y') {
			Period period((int)10, Months);
			vec.push_back(make_pair(period, temp2));
		}
	}



	return vec;
}



void survivalcurve() {

	//create instruments
	std::vector<boost::shared_ptr<DefaultProbabilityHelper> > instruments;


	//Bootstrap hazard rates




}


int main()
{

	Date today = Date(15, June, 2017);
	Calendar cal = TARGET();

	Settings::instance().evaluationDate() = today;

	Date maturity = cal.adjust(today + Period(10, Years), Following);

	Schedule cdsSchedule_new = MakeSchedule()
		.from(today)
		.to(maturity)
		.withFrequency(Quarterly)
		.withCalendar(cal)
		.withConvention(Following)
		.backwards()
		.withTerminationDateConvention(Following)
		.withRule(DateGeneration::CDS2015);


	//Schedule cdsSch = Schedule(today, maturity, new Period(3, Months), cal, Following, Following, DateGeneration::CDS2015);


	std::vector<Date> cdsDates_new = cdsSchedule_new.dates();

	for (Date i : cdsDates_new) {
		cout << i << std::endl;
	};

	std::cout << "\n\n\n" << std::endl;

	Schedule cdsSchedule_old = MakeSchedule()
		.from(today)
		.to(maturity)
		.withFrequency(Quarterly)
		.withCalendar(cal)
		.withConvention(Following)
		.withTerminationDateConvention(Following)
		.withRule(DateGeneration::CDS);



	std::vector<Date> cdsDates_old = cdsSchedule_old.dates();

	for (Date i : cdsDates_old) {
		cout << i << std::endl;
	};


	string output_location = "C:\\Users\\wb512563\\source\\repos\\qlExamplesCpp\\Output\\cds_new.csv";
	Output(output_location, cdsDates_new);

	//string input_path = R"("C:\Users\wb512563\source\repos\qlExamplesCpp\Input\CDSspreads.csv")";
	string input_path = "C:\\Users\\wb512563\\source\\repos\\qlExamplesCpp\\Input\\CDSspreads.csv";
	vector<pair<Period, Rate>> inputSpreads = read_cds_spreads(input_path);

	for (pair<Period, Rate> i : inputSpreads) {
		cout << i.first << endl;
	}

	system("PAUSE");


    return 0;
}

