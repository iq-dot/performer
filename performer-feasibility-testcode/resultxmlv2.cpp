#include "performer/resultxml.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <sstream>
#include <iostream>
#include <ctime>

using namespace xercesc;
using namespace std;

XMLCh* ResultXML::rootName = 0;
XMLCh* ResultXML::spdName = 0;
XMLCh* ResultXML::memName = 0;
XMLCh* ResultXML::sectName = 0;
XMLCh* ResultXML::ridAtrb = 0;
XMLCh* ResultXML::tsourceAtrb = 0;

void ResultXML::init()
{
    //sets-up for XML processing and handle any errors if unsuccessful
    try{
        XMLPlatformUtils::Initialize();
    }
    catch (XMLException &e){
        char *msg = XMLString::transcode(e.getMessage());
        XERCES_STD_QUALIFIER cerr << "Error During Initialization: " << endl << msg;
        XMLString::release(&msg);
    }
    catch (...){
        cerr << "Error Unknown Exception Encountered!" << endl;
    }

    rootName = XMLString::transcode("result");
    spdName = XMLString::transcode("speed_result");
    memName = XMLString::transcode("memory_result");
    sectName = XMLString::transcode("section_list");
    ridAtrb = XMLString::transcode("rid");
    tsourceAtrb = XMLString::transcode("tsource");
}

//create a new blank XML document to hold results
ResultXML::ResultXML(const char *fname, const char *source):parser(NULL)
{
    init();

    //get the XML implementation using the core feature set
    XMLCh *feature = XMLString::transcode("Core");
    imp = DOMImplementationRegistry::getDOMImplementation(feature);

    if(imp != NULL){
        try{

            //Set-up attribute values, the rid value will be based on a unix timestamp
            stringstream ss;
            ss << time(NULL);
            XMLCh *ridValue = XMLString::transcode(ss.str().c_str());
            XMLCh *tsourceVal = XMLString::transcode(source);

            //use the cstring version of the string to create the save location and filename as unicode format
            filename = XMLString::transcode(fname);

            //create the document and the main elements for the document and set-up save location for serializing
            doc = imp->createDocument(0, rootName, 0);
            root = doc->getDocumentElement();
            spdResult = doc->createElement(spdName);
            memResult = doc->createElement(memName);
            sectList = doc->createElement(sectName);

            //sets the attribute of the root node
            root->setAttribute(ridAtrb, ridValue);
            root->setAttribute(tsourceAtrb, tsourceVal);

            //append the nodes and set the template for the document
            root->appendChild(spdResult);
            root->appendChild(memResult);
            root->appendChild(sectList);

//            //release the memory occupied by the encoded strings
//            XMLString::release(&feature);
//            XMLString::release(&rootName);
//            XMLString::release(&spdName);
//            XMLString::release(&memName);
//            XMLString::release(&sectName);
//            XMLString::release(&ridAtrb);
//            XMLString::release(&ridValue);
//            XMLString::release(&tsourceAtrb);
//            XMLString::release(&tsourceVal);
        }
        catch (const OutOfMemoryException&){

            XERCES_STD_QUALIFIER cerr << "Error Out of Memory Exception: " << XERCES_STD_QUALIFIER endl;
        }
        catch (const DOMException& e){

            XERCES_STD_QUALIFIER cerr << "Error DOMException Encountered Code:  " << e.code << XERCES_STD_QUALIFIER endl;
        }
        catch (...){

            XERCES_STD_QUALIFIER cerr << "Unknown Error Encountered, Could Not Create Document" << XERCES_STD_QUALIFIER endl;
        }
    }
    else{
         XERCES_STD_QUALIFIER cerr << "Error: Could Not Create Requested Implementation" << XERCES_STD_QUALIFIER endl;
    }
}

//initialize a ResultXML object using an existing xml file
ResultXML::ResultXML(const char *file)
{
    //sets-up for XML processing and handle any errors if unsuccessful
    try{
        XMLPlatformUtils::Initialize();
    }
    catch (XMLException &e){
        char *msg = XMLString::transcode(e.getMessage());
        XERCES_STD_QUALIFIER cerr << "Error During Initialization: " << endl << msg;
        XMLString::release(&msg);
    }
    catch (...){
        cerr << "Error Unknown Exception Encountered!" << endl;
    }

    //create a parser and set it to validate document but not load a DTD or use a schema
    parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoSchema(false);
    parser->setLoadExternalDTD(false);

    //get the XML implementation using the core feature set
    XMLCh *feature = XMLString::transcode("Core");
    imp = DOMImplementationRegistry::getDOMImplementation(feature);

    try{
        //create unicode strings to for later use
        XMLCh *updateAtrb = XMLString::transcode("updated");
        filename = XMLString::transcode(file);

        //parse the file and retrieve the required nodes
        parser->parse(file);
        doc = parser->getDocument();
        root = doc->getDocumentElement();

        //Set-up attribute values, the updated value will be based on the current local date and time
        stringstream ss;
        time_t curTime;
        struct tm *localt;

        //retrieve the raw unix timestamp and convert to local time
        time(&curTime);
        localt = localtime(&curTime);

        //format the value for the updated attribute to be in the form: day-month-year-hour-min
        ss << localt->tm_mday << "-" << (localt->tm_mon + 1) << "-" << (localt->tm_year + 1900)<< "-" << localt->tm_hour << "-" << localt->tm_min;

        XMLCh *updateVal = XMLString::transcode(ss.str().c_str());

        //set the updated value
        root->setAttribute(updateAtrb, updateVal);

        DOMNodeList *nlist = root->getChildNodes();

        //go through the nodelist finding the top level child nodes and assign them to the right member variables
        for(XMLSize_t i=0; i<nlist->getLength(); i++){

            DOMNode *curNode = nlist->item(i);
            DOMElement *curElm;

            //safely check for element node before casting
            if(curNode->getNodeType() == DOMNode::ELEMENT_NODE){
                curElm = dynamic_cast<DOMElement*>(curNode);

                //check the tag name and assign accordingly
                if(XMLString::equals(spdName, curElm->getTagName())){
                    spdResult = curElm;
                }
                else if(XMLString::equals(memName, curElm->getTagName())){
                    memResult = curElm;
                }
                else if(XMLString::equals(sectName, curElm->getTagName())){
                    sectList = curElm;
                }
            }

        }

        //release the memory occupied by the encoded strings
//        XMLString::release(&spdName);
//        XMLString::release(&memName);
//        XMLString::release(&sectName);
//        XMLString::release(&feature);
//        XMLString::release(&updateAtrb);
//        XMLString::release(&updateVal);
    }
    catch (const OutOfMemoryException&){

        XERCES_STD_QUALIFIER cerr << "Error Out of Memory Exception: " << XERCES_STD_QUALIFIER endl;
    }
    catch (const DOMException& e){

        XERCES_STD_QUALIFIER cerr << "Error DOMException Encountered Code:  " << e.code << XERCES_STD_QUALIFIER endl;
    }
    catch (...){

        XERCES_STD_QUALIFIER cerr << "Unknown Error Encountered, Could Not Create Document" << XERCES_STD_QUALIFIER endl;
    }

}

//destructor
ResultXML::~ResultXML()
{
    //save the document before cleaning up
    save();

    XMLString::release(&filename);

    //before destroying the parser, double check it exists
    if(parser!=NULL){
        delete parser;
    }

    //safely terminates the XML parser
    XMLPlatformUtils::Terminate();
}

//Adds the memory results to the XML doc
void ResultXML::addMemResult(MemInfo &mem, const char *sect)
{


}

void ResultXML::addSpeedResult(SpeedInfo &spd, const char *sect)
{
    //NOTE TODO: look at reference counting
    XMLCh *stestElm = XMLString::transcode("stest");
    XMLCh *wTimeElm = XMLString::transcode("walltime");
    XMLCh *cpuTimeElm = XMLString::transcode("cputime");
    XMLCh *uTimeElm = XMLString::transcode("usrtime");
    XMLCh *sTimeElm = XMLString::transcode("systime");
    XMLCh *tsectionAtb = XMLString::transcode("tsection");
    XMLCh *tsectVal = XMLString::transcode(sect);

}

void ResultXML::addSection(const char* name)
{

}

//save the document to an external file
void ResultXML::save()
{
    //create the serializer for saving the document
    DOMLSSerializer *serializer = (DOMLSSerializer*)imp->createLSSerializer();

    //use the cstring version of the string to create the save location and filename as unicode format
    xercesc::XMLFormatTarget *ftarget = new LocalFileFormatTarget(filename);

    //configure for saving it in a well presented human readable format
    if(serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true)){
       serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
    }

    //set the output for serializing as a stream
    DOMLSOutput *output = ((DOMImplementationLS*)imp)->createLSOutput();
    output->setByteStream(ftarget);

    //use the serializer to save the document and catch any errors encountered
    try{
        serializer->write(root, output);
    }
    catch (const XMLException& e) {
        char* msg = XMLString::transcode(e.getMessage());
        cout << "Error Exception Encountered: " << endl << msg << endl;
        XMLString::release(&msg);
    }
    catch (const DOMException& e) {
        char* msg = XMLString::transcode(e.getMessage());
        cout << "Error Exception Encountered: " << endl << msg << endl;
        XMLString::release(&msg);
    }
    catch (...) {
        cout << "Error Unknown Exception" << endl;
    }

    //force the release of resources held by the serializer and output manager
    output->release();
    serializer->release();
    delete ftarget;
}
