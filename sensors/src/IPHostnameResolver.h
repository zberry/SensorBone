/*
 * IPHostnameResolver.h
 *
 *  Created on: May 14, 2017
 *      Author: zberry
 */

#ifndef IPHOSTNAMERESOLVER_H_
#define IPHOSTNAMERESOLVER_H_

#include <cstdint>
#include <boost/shared_array.hpp>

namespace sensorbone
    {

    class IPHostnameResolver
        {
        public:
            IPHostnameResolver();

            virtual ~IPHostnameResolver();

            boost::shared_array<uint8_t> getIPAddress(void);
            std::string getHostname(void);

        private:
            boost::shared_array<uint8_t> ipAddress;
            std::string hostname;

        };

    } /* namespace sensorbone */

#endif /* IPHOSTNAMERESOLVER_H_ */
