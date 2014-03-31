#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>

#include <iostream>

using namespace xercesc;
using namespace std;

int main()
{
	try{
		XMLPlatformUtils::Initialize();
	}
	catch(const XMLException &e){
		char *msg = XMLString::transcode(e.getMessage());
		cout << "XMLException Error: " << msg << endl;
		XMLString::release(&msg);
	}
	
	XercesDOMParser *parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);
	
	ErrorHandler *errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);
	
	char *xmlFile = "test.xml";
	
	try{
		parser->parse(xmlFile);
		
		DOMDocument *doc = parser->getDocument();
		DOMElement *root = doc->getDocumentElement();
		
		DOMImplementation *imp = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
		DOMLSSerializer *serializer = ((DOMImplementationLS*)imp)->createLSSerializer();
		
		if(serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
			serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
		
		  
		  XMLFormatTarget *target = new StdOutFormatTarget();
		  DOMLSOutput *output = ((DOMImplementationLS*)imp)->createLSOutput();
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
	catch (const XMLException &e) {
		char *msg = XMLString::transcode(e.getMessage());
		cout << "Error Exception: " << msg << endl;
		XMLString::release(&msg);
		return -1;
	}
	catch (...) {
		cout << "Unexpected Error" << endl;
		return -1;
	}
	
	delete parser;
	delete errHandler;
	
	XMLPlatformUtils::Terminate();
	return 0;
}
