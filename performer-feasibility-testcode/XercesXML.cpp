#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <ctime>
#include <sstream>

#include <iostream>

using namespace xercesc;
using namespace std;

int main()
{
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    // Do your failure processing here
    return 1;
  }
  // Do your actual work with Xerces-C++ here.
  int errorCode = 0;
	
  XMLCh *ft = XMLString::transcode("Core");
  DOMImplementation *pImp = DOMImplementationRegistry::getDOMImplementation(ft);
  if(pImp != NULL){
	  try{
		  DOMDocument *pDoc = pImp->createDocument(0, XMLString::transcode("testdoc"), 0);
		  DOMElement *root = pDoc->getDocumentElement();
		  
		  DOMElement *elem = pDoc->createElement(XMLString::transcode("smsg"));
		  DOMText *txtElm = pDoc->createTextNode(XMLString::transcode("hello msg"));
		  
		  root->appendChild(elem);
		  elem->appendChild(txtElm);
		  elem->setAttribute(XMLString::transcode("watt"), XMLString::transcode("super"));
		  
		  DOMLSSerializer *serializer = ((DOMImplementationLS*)pImp)->createLSSerializer();
		
		if(serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
			serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
		
			const char* s= "hello";
			const char* s2 = ".xml";
			char sar[25];
			strcat(sar, s);
			strcat(sar, s2);
		  
		  XMLFormatTarget *target = new LocalFileFormatTarget(XMLString::transcode(&sar));
		  DOMLSOutput *output = ((DOMImplementationLS*)pImp)->createLSOutput();
		  output->setByteStream(target);
		  
		  try{
			  serializer->write(root, output);
		  }
		  catch (...){
			  cout << "Unexpected Exception \n";
			  return -1;
		  }
		  
		  delete target;
	  }
	  catch (const OutOfMemoryException&){
		  XERCES_STD_QUALIFIER cerr << "Out of memory exception: " << XERCES_STD_QUALIFIER endl;
		  errorCode=5;
	  }
	  catch (const DOMException& e){
		  
               XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
               errorCode = 2;
           }
      catch (...){
		  
               XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
               errorCode = 3;
		}
	}
	 else
     {
           XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
           errorCode = 4;
     }

  

  XMLPlatformUtils::Terminate();

  // Other terminations and cleanup.

	return 0;
}
