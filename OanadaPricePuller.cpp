/* 
 * File:   OanadaPricePuller.cpp
 * Author: matt
 * 
 * Created on 03 June 2015, 18:25
 */

#include "OanadaPricePuller.h"
#include "GraphLines.h"

OanadaPricePuller::OanadaPricePuller(GraphLines *inG,std::string inAccessId,std::string inAccessToken)
: gLines(inG)
,accessId(inAccessId)
,accessToken(inAccessToken)
{
}

OanadaPricePuller::OanadaPricePuller(const OanadaPricePuller& orig)
{
}

OanadaPricePuller::~OanadaPricePuller()
{
}

void OanadaPricePuller::handleStream(std::streambuf* stream_buffer)
{
    std::istreambuf_iterator<char> eos; // end-of-range iterator
    std::istreambuf_iterator<char> iit(stream_buffer); // stream iterator
    std::string str;

    while (iit != eos)
    {
        std::ostringstream oss;
        while (*iit != '\n')
        {
            oss << *iit++;
        }
        rapidjson::Document d;
        d.Parse(oss.str().c_str());
        if (d.HasMember("tick"))
        {
            rapidjson::Value& val = d["tick"]["ask"];
            gLines->setPoint(val.GetDouble());
        }
        else if (d.HasMember("heartbeat"))
        {

        }
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);
        *iit++;
    }
}

void OanadaPricePuller::getTick()
{
    std::string instruments = "EUR_USD,USD_CAD,EUR_JPY";
//    std::string instruments = "EUR_JPY";
    try
    {
        const Poco::Net::Context::Ptr context =
                new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

        // prepare session
        Poco::URI uri(OANDA_DOMAIN + std::string("/v1/prices?accountId=") + accessId + std::string("&instruments=") + instruments);

        Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
        session.setKeepAlive(true);

        // prepare path
        std::string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        // send request
        Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);
        req.set("Authorization", std::string("Bearer ") + accessToken);
        session.sendRequest(req);

        // get response
        Poco::Net::HTTPResponse res;
        std::istream& rs = session.receiveResponse(res);

        // handle response
        std::ostringstream out_string_stream;
        handleStream(rs.rdbuf());
    }
    catch (const Poco::Exception &e)
    {
        std::cerr << e.displayText() << std::endl;
    }
}

