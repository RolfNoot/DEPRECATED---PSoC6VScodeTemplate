#ifndef BUILDVERSION_H
#define BUILDVERSION_H

/* build info variables inserted at pre-build with buildversion tool */

#define	buildyear			/*%#y*/19				// Year 2 digit
#define	buildmonth          /*%#M*/ 6               // Month 2 digit
#define	buildday            /*%#D*/24               // Day 2 digit
#define	buildhour           /*%#H*/14               // Hour 2 digit
#define	buildminute         /*%#m*/19               // Minute 2 digit
#define	buildsecond         /*%#S*/11               // Second 2 digit
#define	buildnumber			/*%#N*/509           	// Incremental number, number of digits depending on total digits after identifier               

buildInfo_t buildInfo =
{
	.buildYear	            = buildyear,
	.buildMonth				= buildmonth,
	.buildDayOfMonth		= buildday,
	.buildHour				= buildhour,
	.buildMinute			= buildminute,
	.buildSecond			= buildsecond,
	.buildNumber			= buildnumber,
};

#endif /* BUILDVERSION_H */
