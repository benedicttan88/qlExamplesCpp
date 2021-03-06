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


#pragma region Function Declaration
void Output(string output_path, std::vector<Date> CDS_Dates);
InterpolatedDiscountCurve<Linear> read_OIS_Curve(string input_path);
std::vector<pair<Period, Rate>> read_cds_spreads(string input_path);

#pragma endregion



void Output(string output_path , std::vector<Date> CDS_Dates) {

	ofstream outfile(output_path);

	outfile << "CDS Dates" << "\n";

	for (Date i : CDS_Dates) {
		outfile << i.serialNumber() << "\n";
	}

}

InterpolatedDiscountCurve<Linear> read_OIS_Curve(string input_path) {

	///read in data
	ifstream inFile(input_path);
	
	int serialNumber;
	double df;

	std::vector<Date> dateVector;
	std::vector<Rate> DiscountVector;

	while (inFile >> serialNumber >> df) {

		dateVector.push_back(Date(serialNumber));
		DiscountVector.push_back(df);

	}


	DayCounter dc = Actual360();
	Calendar cal = TARGET();

	InterpolatedDiscountCurve<Linear> curve(dateVector, DiscountVector, dc, cal);

	return curve;
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





int main()
{

	Date today = Date(1, Sep, 2017);
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
	//string input_path = "C:\\Users\\wb512563\\source\\repos\\qlExamplesCpp\\Input\\CDSspreads.csv";
	//vector<pair<Period, Rate>> inputSpreads = read_cds_spreads(input_path);

	//for (pair<Period, Rate> i : inputSpreads) {
	//	cout << i.first << endl;
	//}

	#pragma region OIS CURVE CONSTRUCTION
	//			OIS CURVE


	string input_OIS_path = "";
	InterpolatedDiscountCurve<Linear> oisCurve = read_OIS_Curve(input_OIS_path);



	#pragma endregion








	system("PAUSE");


    return 0;
}

