// qlExamplesCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <ql/qldefines.hpp>
#include <ql/quantlib.hpp>


using namespace std;
using namespace QuantLib;


int main()
{

	Date today = Date(31, March, 2017);
	Calendar cal = TARGET();

	Settings::instance().evaluationDate() = today;

	Date maturity = cal.adjust(today + Period(5, Years), Following);

	Schedule cdsSchedule = MakeSchedule()
		.from(today)
		.to(maturity)
		.withFrequency(Quarterly)
		.withCalendar(cal)
		.withTerminationDateConvention(Unadjusted)
		.withRule(DateGeneration::CDS2015);




    return 0;
}

