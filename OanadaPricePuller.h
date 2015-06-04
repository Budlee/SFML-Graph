/* 
 * File:   OanadaPricePuller.h
 * Author: matt
 *
 * Created on 03 June 2015, 18:25
 */

#ifndef OANADAPRICEPULLER_H
#define	OANADAPRICEPULLER_H

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "GraphLines.h"

#define OANDA_DOMAIN "https://stream-fxpractice.oanda.com"

class OanadaPricePuller {
public:
    OanadaPricePuller(GraphLines *inG, std::string inAccessId,std::string inAccessToken);
    OanadaPricePuller(const OanadaPricePuller& orig);
    virtual ~OanadaPricePuller();

    void getTick();

private:
    void handleStream(std::streambuf* stream_buffer);
    
    GraphLines *gLines;
    std::string accessId,accessToken;
    
};

#endif	/* OANADAPRICEPULLER_H */

