/*
 * xbeeConnection.cpp
 *
 *  Created on: May 18, 2017
 *      Author: zberry
 */

#include "xbeeConnection.h"
#include <iostream>

using namespace std;


xbeeConnection::~xbeeConnection() {
	// TODO Auto-generated destructor stub
}

xbeeConnection::xbeeConnection(libxbee::XBee& parent, std::string type,
		struct xbee_conAddress* address) : libxbee::ConCallback(parent, type, address)
{
}

void xbeeConnection::xbee_conCallback(libxbee::Pkt** pkt) {

	cout << "Connection callback called" << endl;
	cout << "Packet " << (*pkt)->getData();
}
