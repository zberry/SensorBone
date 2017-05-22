/*
 * xbeeConnection.h
 *
 *  Created on: May 18, 2017
 *      Author: zberry
 */

#ifndef XBEECONNECTION_H_
#define XBEECONNECTION_H_

#include <xbeep.h>

class xbeeConnection: public libxbee::ConCallback {
public:
	xbeeConnection();
	explicit xbeeConnection(libxbee::XBee &parent, std::string type, struct xbee_conAddress *address = NULL);
	virtual ~xbeeConnection();

	void xbee_conCallback(libxbee::Pkt **pkt);

private:
};

#endif /* XBEECONNECTION_H_ */
