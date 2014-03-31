#include "resultxml.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <iostream>

using namespace xercesc;
using namespace std;

//create a new blank XML document to hold results
ResultXML::ResultXML()
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

    //get the XML implementation using the core feature set
    XMLCh *feature = XMLString::transcode("Core");
    imp = DOMImplementationRegistry::getDOMImplementation(feature);

    if(imp != NULL){
        try{
            //set-up XML unicode encoded strings to use
            XMLCh *rootName = XMLString::transcode("result");
            XMLCh *spdName = XMLString::transcode("speed_result");
            XMLCh *memName = XMLString::transcode("memory_result");
            XMLCh *sectName = XMLString::transcode("section_list");
            XMLCh *fname = XMLString::transcode(filename);

            //create the document and the main elements for the document and set-up save location for serializing
            doc = imp->createDocument(0, rootName, 0);
            root = doc->getDocumentElement();
            spdResult = doc->createElement(spdName);
            memResult = doc->createElement(memName);
            sectList = doc->createElement(sectName);
            ftarget = new LocalFileFormatTarget(fname);

            //append the nodes and set the template for the document
            root->appendChild(spdResult);
            root->appendChild(memResult);
            root->appendChild(sectList);

            //release the memory occupied by the encoded strings
            XMLString::release(&feature);
            XMLString::release(&rootName);
            XMLString::release(&spdName);
            XMLString::release(&memName);
            XMLString::release(&sectName);
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
    XercesDOMParser *parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoSchema(false);
    parser->setLoadExternalDTD(false);

    try{
        //create unicode strings to for later use
        XMLCh *spdName = XMLString::transcode("speed_result");
        XMLCh *memName = XMLString::transcode("memory_result");
        XMLCh *sectName = XMLString::transcode("section_list");
        XMLCh *fname = XMLString::transcode(file);

        //set the save location, parse the file and retrieve the required nodes
        ftarget = new LocalFileFormatTarget(fname);
        parser->parse(file);
        doc = parser->getDocument();
        root = doc->getDocumentElement();

        DOMNodeList *nlist = root->getChildNodes();

        //go through the nodelist finding the top level child nodes and assign them to the right member variables
        for(XMLSize_t i=0; i<nlist->getLength(); i++){

            DOMNode *curNode = nlist->item(i);
            DOMElement *curElm;

            //safely check for element node before casting
            if(curNode->getNodeType() == DOMNode::ELEMENT_NODE){
                curElm = dynamic_cast<DOMElement*>(curNode);
            }

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

        //release the memory occupied by the encoded strings
        XMLString::release(&spdName);
        XMLString::release(&memName);
        XMLString::release(&sectName);
        XMLString::release(&fname);
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

    delete parser;
}

//destructor
ResultXML::~ResultXML()
{
    //save the document before cleaning up
    save();

    //safely terminates the XML parser
    XMLPlatformUtils::Terminate();
    delete ftarget;
}

//Adds the memory results to the XML doc
void ResultXML::addMemResult(MemInfo &mem)
{
    XMLCh *memElm;
    XMLCh *wTimeElm;
    XMLCh *uTimeElm;
    XMLCh *sTimeElm;

}

void ResultXML::addSpeedResult(SpeedInfo &spd)
{

}

void ResultXML::addSection(const char* name)
{

}

//save the document to an external file
void ResultXML::save()
{
    //create the serializer for saving the document
    DOMLSSerializer *serializer = (DOMLSSerializer*)imp->createLSSerializer();

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
}

int main()
{
	ResultXML xp;
	
	return 0;
}
