//============================================================================
// Name        : sensors.cpp
// Author      : Zachary Berry
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>


#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <boost/shared_ptr.hpp>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "xbeep.h"
#include "xbee.h"


#include "xbeeConnection.h"
#include "XbeeSetting.h"


using namespace std;
using namespace sensorbone;

static log4cxx::LoggerPtr logger;

void setupLog4cxx (void)
{

	const char *logConfigFileName = "./config/sensorConfig.xml";
    log4cxx::xml::DOMConfigurator::configure(logConfigFileName);
    logger = log4cxx::Logger::getLogger("sensor.main");

    LOG4CXX_DEBUG(logger, "Lodaded logger xml\"" << logConfigFileName << "\"");
}

void initXbee(std::string &xbeeCommPort ,std::string &xbeeProtocolVersion, int baudRate)
{

	LOG4CXX_DEBUG(logger,
			"Initializing xbee on comm port \"" << xbeeCommPort << "\" baud rate " << baudRate << " xbee API mode \"" << xbeeProtocolVersion << "\"");

	boost::shared_ptr<libxbee::XBee> xbee(
			new libxbee::XBee(xbeeProtocolVersion, xbeeCommPort, baudRate));

	/* get available connection types */
	try {
		std::list<std::string> types = xbee->getConTypes();
		std::list<std::string>::iterator i;

		std::cout << "Available connection types:\n";
		for (i = types.begin(); i != types.end(); i++) {
			std::cout << "  \"" << *i << "\"";
		}
		std::cout << "\n";
	}
	catch (libxbee::xbee_etx &ret)

	{
		LOG4CXX_ERROR(logger ,"Error while retrieving connection types...\n"
				<< " reason: " << string (xbee_errorToStr(ret.ret)));
	}


	xbee->setLogLevel(1000000);

     XbeeSettings settings (*xbee, "Local AT");


	//boost::shared_ptr<xbeeConnection> con2 (new xbeeConnection (*xbee, "Local AT"));

    //con2->Tx("NI");


	boost::shared_ptr<xbeeConnection> con;
	xbee_conAddress address = {0};
	address.addr64_enabled = 1;
	// 00 13 A2 00 41 67 DF 44
	unsigned char a[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF };
	memcpy(address.addr64, a, sizeof(a));


	try
	{
		LOG4CXX_TRACE(logger, "Attempting to open xbee connection");
	    con = boost::shared_ptr<xbeeConnection> (new xbeeConnection(*xbee, "Data", &address));
		//con = boost::shared_ptr<xbeeConnection> (new xbeeConnection(*xbee, "Local AT"));
	}
	catch (xbee_errors &ret)
    {
		LOG4CXX_ERROR(logger ,"Error while settign up connection ...\n"
								<< " reason: "<< ret << " \"" << string (xbee_errorToStr(ret)));
    }




	/* Try to send something */
	try
	{

	con->Tx("Hello World");

	//con->Tx(string ("NI"));
	}
	catch (libxbee::xbee_etx &ret)
	{

		LOG4CXX_ERROR(logger ,"Error while transmitting ...\n"
						<< " reason: "<< ret.ret << " \"" << string (xbee_errorToStr(ret.ret))
					    << "\" retVal: \"" << (int) ret.retVal << "\"");
	}
	catch (xbee_errors &ret)
	    {
			LOG4CXX_ERROR(logger ,"Error while transmitting ...\n"
									<< " reason: "<< ret << " \"" << string (xbee_errorToStr(ret)));
	    }

	usleep(300000000);

	//con << "Hello World";


}

int main()
{
    setupLog4cxx();

    LOG4CXX_DEBUG(logger, "Reading config file");

    string xbeeCommPort ("/dev/ttyO2");
    string xbeeProtocolVersion ("xbee3");
    int baudRate = 57600;

    initXbee (xbeeCommPort, xbeeProtocolVersion, baudRate);





    return 0;
}
