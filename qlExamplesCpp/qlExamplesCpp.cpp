// qlExamplesCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <ql/qldefines.hpp>
#include <ql/quantlib.hpp>

#include <boost/timer.hpp>
#include <boost/make_shared.hpp>


using namespace std;
using namespace QuantLib;


void survivalcurve();

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

	Date maturity = cal.adjust(today + Period(5, Years), Following);

	Schedule cdsSchedule_new = MakeSchedule()
		.from(today)
		.to(maturity)
		.withFrequency(Quarterly)
		.withCalendar(cal)
		.withTerminationDateConvention(Unadjusted)
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
		.withTerminationDateConvention(Unadjusted)
		.withRule(DateGeneration::CDS);



	std::vector<Date> cdsDates_old = cdsSchedule_old.dates();

	for (Date i : cdsDates_old) {
		cout << i << std::endl;
	};

	system("PAUSE");


    return 0;
}

