/*
 * IPHostnameResolver.cpp
 *
 *  Created on: May 14, 2017
 *      Author: zberry
 */
#include <boost/regex.h>

#include "IPHostnameResolver.h"


namespace sensorbone
    {

    IPHostnameResolver::IPHostnameResolver()
    {
        FILE * fp = popen("hostname", "r");
        if (!fp)
        {

        }
        char *p = NULL;
        size_t n;
        if (getline(&p, &n, fp) > 0)
        {
        hostname = p;

        }
        else
        {
        /* Error hostname didnt return anything */
        }

    }

    IPHostnameResolver::~IPHostnameResolver()
    {
        // TODO Auto-generated destructor stub
    }

    boost::shared_array<uint8_t> IPHostnameResolver::getIPAddress(void)
    {
    }

    std::string IPHostnameResolver::getHostname(void)
    {
    }

    } /* namespace sensorbone */
