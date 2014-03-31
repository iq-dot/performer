#include "performer/data_collection/resultxml.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <sstream>
#include <iostream>
#include <ctime>

using namespace xercesc;
using namespace std;

int ResultXML::refCount = 0;

XMLCh* ResultXML::feature = 0;
XMLCh* ResultXML::rootName = 0;
XMLCh* ResultXML::spdName = 0;
XMLCh* ResultXML::memName = 0;
XMLCh* ResultXML::sectName = 0;
XMLCh* ResultXML::ridAtrb = 0;
XMLCh* ResultXML::tsourceAtrb = 0;
XMLCh* ResultXML::updateAtrb = 0;
XMLCh* ResultXML::sectElmName = 0;

XMLCh* ResultXML::stestName = 0;
XMLCh* ResultXML::wTimeName = 0;
XMLCh* ResultXML::cpuTimeName = 0;
XMLCh* ResultXML::totalTimeName = 0;
XMLCh* ResultXML::uTimeName = 0;
XMLCh* ResultXML::sTimeName = 0;
XMLCh* ResultXML::tsectionAtb = 0;

void ResultXML::SetUp()
{
    if(refCount < 1){
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

        //set-up the feature-set
        XMLCh *feature = XMLString::transcode("Core Traversal");

        //set-up XML unicode encoded strings to use
        XMLCh *rootName = XMLString::transcode("result");
        XMLCh *spdName = XMLString::transcode("speed_result");
        XMLCh *memName = XMLString::transcode("memory_result");
        XMLCh *sectName = XMLString::transcode("section_list");
        XMLCh *ridAtrb = XMLString::transcode("rid");
        XMLCh *tsourceAtrb = XMLString::transcode("tsource");
        XMLCh *updateAtrb = XMLString::transcode("updated");
        XMLCh *sectElmName = XMLString::transcode("section");
        XMLCh *tsectionAtb = XMLString::transcode("tsection");

        //set-up xml tag names and attributes
        XMLCh *stestName = XMLString::transcode("stest");
        XMLCh *wTimeName = XMLString::transcode("walltime");
        XMLCh *cpuTimeName = XMLString::transcode("cputime");
        XMLCh *totalTimeName = XMLString::transcode("totaltime");
        XMLCh *uTimeName = XMLString::transcode("usrtime");
        XMLCh *sTimeName = XMLString::transcode("systime");
    }

    refCount++;
}


void ResultXML::CleanUp()
{
    refCount--;

    if(refCount == 0){

        //release the memory occupied by the encoded strings
        XMLString::release(&feature);
        XMLString::release(&rootName);
        XMLString::release(&spdName);
        XMLString::release(&memName);
        XMLString::release(&sectName);
        XMLString::release(&ridAtrb);
        XMLString::release(&tsourceAtrb);
        XMLString::release(&updateAtrb);
        XMLString::release(&tsectionAtb);

        //release occupied memory from the unicode strings in the speed results section
        XMLString::release(&stestName);
        XMLString::release(&wTimeName);
        XMLString::release(&cpuTimeName);
        XMLString::release(&totalTimeName);
        XMLString::release(&uTimeName);
        XMLString::release(&sTimeName);

        //safely terminates the XML parser
        XMLPlatformUtils::Terminate();
    }
}

//create a new blank XML document to hold results
ResultXML::ResultXML(const char *fname, const char *source):parser(NULL)
{
    //setup for all ResultXML objects
    ResultXML::SetUp();

    //get the XML implementation using the feature set
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

            //release resources from xml strings
            XMLString::release(&tsourceVal);
            XMLString::release(&ridValue);
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
    //setup for all ResultXML objects
    ResultXML::SetUp();

    //create a parser and set it to validate document but not load a DTD or use a schema
    parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoSchema(false);
    parser->setLoadExternalDTD(false);

    //get the XML implementation using the feature set
    imp = DOMImplementationRegistry::getDOMImplementation(feature);

    try{
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
        //release any xml string resources
        XMLString::release(&updateVal);
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

    //cleanup resources from ResultXML objects
    ResultXML::CleanUp();
}

//Adds the memory results to the XML doc
void ResultXML::addMemResult(const MemInfo &mem, const char *sect)
{
    //setup xml unicode names for tags, attributes and values

    XMLCh *mtestName = XMLString::transcode("mtest");
    XMLCh *tsectAtrb = XMLString::transcode("tsection");
    XMLCh *tsecVal = XMLString::transcode(sect);
    XMLCh *vsizeName = XMLString::transcode("virtual");
    XMLCh *resName = XMLString::transcode("resident");
    XMLCh *refName = XMLString::transcode("referenced");
    XMLCh *swapName = XMLString::transcode("swap");
    XMLCh *dirMemName = XMLString::transcode("dirty");
    XMLCh *clnMemName = XMLString::transcode("clean");

    XMLCh *sharedName = XMLString::transcode("shared");
    XMLCh *sharedTot = XMLString::transcode("total_shared");
    XMLCh *sharedDir = XMLString::transcode("shared_dirty");
    XMLCh *sharedCln = XMLString::transcode("shared_clean");

    XMLCh *privName = XMLString::transcode("private");
    XMLCh *privTot = XMLString::transcode("private_total");
    XMLCh *privClean = XMLString::transcode("private_clean");
    XMLCh *privDirty = XMLString::transcode("private_dirty");

    XMLCh *stackName = XMLString::transcode("stack");
    XMLCh *stackVss = XMLString::transcode("stack_vss");
    XMLCh *stackRss = XMLString::transcode("stack_rss");
    XMLCh *stackRef = XMLString::transcode("stack_ref");
    XMLCh *stackDirty = XMLString::transcode("stack_dirty");
    XMLCh *stackCln = XMLString::transcode("stack_clean");

    XMLCh *heapName = XMLString::transcode("heap");
    XMLCh *heapVss = XMLString::transcode("heap_vss");
    XMLCh *heapRss = XMLString::transcode("heap_rss");
    XMLCh *heapRef = XMLString::transcode("heap_ref");
    XMLCh *heapDirty = XMLString::transcode("heap_dirty");
    XMLCh *heapCln = XMLString::transcode("heap_clean");

    XMLCh *vmDataName = XMLString::transcode("vm_data");
    XMLCh *vmExeName = XMLString::transcode("vm_exe");
    XMLCh *vmLibName = XMLString::transcode("vm_lib");
    XMLCh *vmPteName = XMLString::transcode("vm_pte");
    XMLCh *pageFaultName = XMLString::transcode("page_faults");

    //prepare the values from the MemInfo structure

    stringstream sharedS, privS, dirtyS, cleanS, swapS, refS, shrDirS, shrClnS, privDirS, privClnS, resS, virS;
    stringstream stkVirS, stkResS, stkRefS, stkClnS, stkDirS, heapVirS, heapResS, heapRefS, heapClnS, heapDirS;
    stringstream vmDataS, vmExeS, vmLibS, vmPteS, pageS;

    sharedS << mem.sharedMem;
    privS << mem.privateMem;
    dirtyS << mem.dirtyMem;
    cleanS << mem.cleanMem;
    swapS << mem.swapMem;
    refS << mem.refMem;
    shrDirS << mem.sharedDirtyMem;
    shrClnS << mem.sharedCleanMem;
    privDirS << mem.privateDirtyMem;
    privClnS << mem.privateCleanMem;
    resS << mem.rsSize;
    virS << mem.vsSize;
    stkVirS << mem.stackSize;
    stkResS << mem.stackRss;
    stkRefS << mem.stackRef;
    stkClnS << mem.stackClean;
    stkDirS << mem.stackDirty;
    heapVirS << mem.heapSize;
    heapResS << mem.heapRss;
    heapRefS << mem.heapRef;
    heapClnS << mem.heapClean;
    heapDirS << mem.heapDirty;
    vmDataS << mem.vmData;
    vmExeS << mem.vmExe;
    vmLibS << mem.vmLib;
    vmPteS << mem.vmPTE;
    pageS << mem.pagefaults;

    //extract values and create unicode versions from the MemInfo structure

    XMLCh *sharedVal = XMLString::transcode(sharedS.str().c_str());
    XMLCh *privVal = XMLString::transcode(privS.str().c_str());
    XMLCh *dirtyVal = XMLString::transcode(dirtyS.str().c_str());
    XMLCh *cleanVal = XMLString::transcode(cleanS.str().c_str());
    XMLCh *swapVal = XMLString::transcode(swapS.str().c_str());
    XMLCh *refVal = XMLString::transcode(refS.str().c_str());
    XMLCh *shrDirVal = XMLString::transcode(shrDirS.str().c_str());
    XMLCh *shrClnVal = XMLString::transcode(shrClnS.str().c_str());
    XMLCh *privDirVal = XMLString::transcode(privDirS.str().c_str());
    XMLCh *privClnVal = XMLString::transcode(privClnS.str().c_str());
    XMLCh *resVal = XMLString::transcode(resS.str().c_str());
    XMLCh *virVal = XMLString::transcode(virS.str().c_str());
    XMLCh *stkVirVal = XMLString::transcode(stkVirS.str().c_str());
    XMLCh *stkResVal = XMLString::transcode(stkResS.str().c_str());
    XMLCh *stkRefVal = XMLString::transcode(stkRefS.str().c_str());
    XMLCh *stkClnVal = XMLString::transcode(stkClnS.str().c_str());
    XMLCh *stkDirVal = XMLString::transcode(stkDirS.str().c_str());
    XMLCh *heapVirVal = XMLString::transcode(heapVirS.str().c_str());
    XMLCh *heapResVal = XMLString::transcode(heapResS.str().c_str());
    XMLCh *heapRefVal = XMLString::transcode(heapRefS.str().c_str());
    XMLCh *heapClnVal = XMLString::transcode(heapClnS.str().c_str());
    XMLCh *heapDirVal = XMLString::transcode(heapDirS.str().c_str());
    XMLCh *vmDataVal = XMLString::transcode(vmDataS.str().c_str());
    XMLCh *vmExeVal = XMLString::transcode(vmExeS.str().c_str());
    XMLCh *vmLibVal = XMLString::transcode(vmLibS.str().c_str());
    XMLCh *vmPteVal = XMLString::transcode(vmPteS.str().c_str());
    XMLCh *pageVal = XMLString::transcode(pageS.str().c_str());


    //check if the section is already added, if not then add the section in the section list
    if(!findSection(tsecVal)){
        addSection(tsecVal);
    }

    //create the document elements and attributes

    DOMElement *mtestElm = doc->createElement(mtestName);
    DOMElement *vsizeElm = doc->createElement(vsizeName);
    DOMElement *resElm = doc->createElement(resName);
    DOMElement *refElm = doc->createElement(refName);
    DOMElement *swapElm = doc->createElement(swapName);
    DOMElement *dirMemElm = doc->createElement(dirMemName);
    DOMElement *clnMemElm = doc->createElement(clnMemName);

    DOMElement *sharedElm = doc->createElement(sharedName);
    DOMElement *sharedClnElm = doc->createElement(sharedCln);
    DOMElement *sharedDirElm = doc->createElement(sharedDir);
    DOMElement *sharedTotElm = doc->createElement(sharedTot);

    DOMElement *privElm = doc->createElement(privName);
    DOMElement *privDirtyElm = doc->createElement(privDirty);
    DOMElement *privCleanElm = doc->createElement(privClean);
    DOMElement *privTotElm = doc->createElement(privTot);

    DOMElement *stackElm = doc->createElement(stackName);
    DOMElement *stackVssElm = doc->createElement(stackVss);
    DOMElement *stackRssElm = doc->createElement(stackRss);
    DOMElement *stackRefElm = doc->createElement(stackRef);
    DOMElement *stackClnElm = doc->createElement(stackCln);
    DOMElement *stackDirElm = doc->createElement(stackDirty);

    DOMElement *heapElm = doc->createElement(heapName);
    DOMElement *heapVssElm = doc->createElement(heapVss);
    DOMElement *heapRssElm = doc->createElement(heapRss);
    DOMElement *heapRefElm = doc->createElement(heapRef);
    DOMElement *heapClnElm = doc->createElement(heapCln);
    DOMElement *heapDirElm = doc->createElement(heapDirty);

    DOMElement *vmDataElm = doc->createElement(vmDataName);
    DOMElement *vmExeElm = doc->createElement(vmExeName);
    DOMElement *vmLibElm = doc->createElement(vmLibName);
    DOMElement *vmPteElm = doc->createElement(vmPteName);
    DOMElement *pageFaultElm = doc->createElement(pageFaultName);

    //create the text nodes from the values extracted from the MemInfo structure earlier

    DOMText *sharedTxt = doc->createTextNode(sharedVal);
    DOMText *privTxt = doc->createTextNode(privVal);
    DOMText *dirTxt = doc->createTextNode(dirtyVal);
    DOMText *cleanTxt = doc->createTextNode(cleanVal);
    DOMText *swapTxt = doc->createTextNode(swapVal);
    DOMText *refTxt = doc->createTextNode(refVal);
    DOMText *shrDirTxt = doc->createTextNode(shrDirVal);
    DOMText *shrClnTxt = doc->createTextNode(shrClnVal);
    DOMText *privDirTxt = doc->createTextNode(privDirVal);
    DOMText *privClnTxt = doc->createTextNode(privClnVal);
    DOMText *resTxt = doc->createTextNode(resVal);
    DOMText *virTxt = doc->createTextNode(virVal);
    DOMText *stkVirTxt = doc->createTextNode(stkVirVal);
    DOMText *stkResTxt = doc->createTextNode(stkResVal);
    DOMText *stkRefTxt = doc->createTextNode(stkRefVal);
    DOMText *stkClnTxt = doc->createTextNode(stkClnVal);
    DOMText *stkDirTxt = doc->createTextNode(stkDirVal);
    DOMText *heapVirTxt = doc->createTextNode(heapVirVal);
    DOMText *heapResTxt = doc->createTextNode(heapResVal);
    DOMText *heapRefTxt = doc->createTextNode(heapRefVal);
    DOMText *heapClnTxt = doc->createTextNode(heapClnVal);
    DOMText *heapDirTxt = doc->createTextNode(heapDirVal);
    DOMText *vmDataTxt = doc->createTextNode(vmDataVal);
    DOMText *vmExeTxt = doc->createTextNode(vmExeVal);
    DOMText *vmLibTxt = doc->createTextNode(vmLibVal);
    DOMText *vmPteTxt = doc->createTextNode(vmPteVal);
    DOMText *pageFaultTxt = doc->createTextNode(pageVal);

    //append the elements together and append it to the document

    memResult->appendChild(mtestElm);

    mtestElm->setAttribute(tsectAtrb, tsecVal);
    mtestElm->appendChild(vsizeElm);
    mtestElm->appendChild(resElm);
    mtestElm->appendChild(refElm);
    mtestElm->appendChild(swapElm);
    mtestElm->appendChild(dirMemElm);
    mtestElm->appendChild(clnMemElm);
    mtestElm->appendChild(privElm);
    mtestElm->appendChild(sharedElm);
    mtestElm->appendChild(vmDataElm);
    mtestElm->appendChild(vmExeElm);
    mtestElm->appendChild(vmLibElm);
    mtestElm->appendChild(vmPteElm);
    mtestElm->appendChild(pageFaultElm);

    vsizeElm->appendChild(virTxt);
    resElm->appendChild(resTxt);
    refElm->appendChild(refTxt);
    swapElm->appendChild(swapTxt);
    dirMemElm->appendChild(dirTxt);
    clnMemElm->appendChild(cleanTxt);
    vmDataElm->appendChild(vmDataTxt);
    vmExeElm->appendChild(vmExeTxt);
    vmLibElm->appendChild(vmLibTxt);
    vmPteElm->appendChild(vmPteTxt);
    pageFaultElm->appendChild(pageFaultTxt);

    privElm->appendChild(privTotElm);
    privElm->appendChild(privDirtyElm);
    privElm->appendChild(privCleanElm);
    privTotElm->appendChild(privTxt);
    privDirtyElm->appendChild(privDirTxt);
    privCleanElm->appendChild(privClnTxt);

    sharedElm->appendChild(sharedTotElm);
    sharedElm->appendChild(sharedDirElm);
    sharedElm->appendChild(sharedClnElm);
    sharedTotElm->appendChild(sharedTxt);
    sharedDirElm->appendChild(shrDirTxt);
    sharedClnElm->appendChild(shrClnTxt);

    stackElm->appendChild(stackVssElm);
    stackElm->appendChild(stackRssElm);
    stackElm->appendChild(stackRefElm);
    stackElm->appendChild(stackDirElm);
    stackElm->appendChild(stackClnElm);
    stackVssElm->appendChild(stkVirTxt);
    stackRssElm->appendChild(stkResTxt);
    stackRefElm->appendChild(stkRefTxt);
    stackDirElm->appendChild(stkDirTxt);
    stackClnElm->appendChild(stkClnTxt);

    heapElm->appendChild(heapVssElm);
    heapElm->appendChild(heapRssElm);
    heapElm->appendChild(heapRefElm);
    heapElm->appendChild(heapDirElm);
    heapElm->appendChild(heapClnElm);
    heapVssElm->appendChild(heapVirTxt);
    heapRssElm->appendChild(heapResTxt);
    heapRefElm->appendChild(heapRefTxt);
    heapDirElm->appendChild(heapDirTxt);
    heapClnElm->appendChild(heapClnTxt);

    //clean up by releasing occupied memory from the names encoded in unicode

    XMLString::release(&mtestName);
    XMLString::release(&tsectAtrb);
    XMLString::release(&tsecVal);
    XMLString::release(&vsizeName);
    XMLString::release(&resName);
    XMLString::release(&refName);
    XMLString::release(&swapName);
    XMLString::release(&dirMemName);
    XMLString::release(&clnMemName);

    XMLString::release(&sharedName);
    XMLString::release(&sharedCln);
    XMLString::release(&sharedDir);
    XMLString::release(&sharedTot);

    XMLString::release(&privName);
    XMLString::release(&privDirty);
    XMLString::release(&privClean);
    XMLString::release(&privTot);

    XMLString::release(&stackName);
    XMLString::release(&stackVss);
    XMLString::release(&stackRss);
    XMLString::release(&stackRef);
    XMLString::release(&stackDirty);
    XMLString::release(&stackCln);

    XMLString::release(&heapName);
    XMLString::release(&heapVss);
    XMLString::release(&heapRss);
    XMLString::release(&heapRef);
    XMLString::release(&heapDirty);
    XMLString::release(&heapCln);

    XMLString::release(&vmDataName);
    XMLString::release(&vmExeName);
    XMLString::release(&vmLibName);
    XMLString::release(&vmPteName);
    XMLString::release(&pageFaultName);

    XMLString::release(&sharedVal);
    XMLString::release(&privVal);
    XMLString::release(&dirtyVal);
    XMLString::release(&cleanVal);
    XMLString::release(&swapVal);
    XMLString::release(&refVal);
    XMLString::release(&shrDirVal);
    XMLString::release(&shrClnVal);
    XMLString::release(&privDirVal);
    XMLString::release(&privClnVal);
    XMLString::release(&resVal);
    XMLString::release(&virVal);
    XMLString::release(&stkVirVal);
    XMLString::release(&stkRefVal);
    XMLString::release(&stkResVal);
    XMLString::release(&stkClnVal);
    XMLString::release(&stkDirVal);
    XMLString::release(&heapVirVal);
    XMLString::release(&heapResVal);
    XMLString::release(&heapRefVal);
    XMLString::release(&heapClnVal);
    XMLString::release(&heapDirVal);
    XMLString::release(&vmDataVal);
    XMLString::release(&vmExeVal);
    XMLString::release(&vmLibVal);
    XMLString::release(&vmPteVal);
    XMLString::release(&pageVal);
}

void ResultXML::addSpeedResult(const SpeedInfo &spd, const char *sect)
{
    XMLCh *tsectVal = XMLString::transcode(sect);

    //check if the section is already added, if not then add the section in the section list
    if(!findSection(tsectVal)){
        addSection(tsectVal);
    }

    //create unicode strings from the SpeedInfo structure
    stringstream wallS, cpuS, sysS, usrS;
    wallS << spd.wallTime;
    cpuS << spd.cpuTime;
    sysS << spd.sysTime;
    usrS << spd.usrTime;

    XMLCh *wallVal = XMLString::transcode(wallS.str().c_str());
    XMLCh *cpuVal = XMLString::transcode(cpuS.str().c_str());
    XMLCh *sysVal = XMLString::transcode(sysS.str().c_str());
    XMLCh *usrVal = XMLString::transcode(usrS.str().c_str());

    //create the dom elements using the above names
    DOMElement *stestElm = doc->createElement(stestName);
    DOMElement *wTimeElm = doc->createElement(wTimeName);
    DOMElement *cpuTimeElm = doc->createElement(cpuTimeName);
    DOMElement *totalTimeElm = doc->createElement(totalTimeName);
    DOMElement *uTimeElm = doc->createElement(uTimeName);
    DOMElement *sTimeElm = doc->createElement(sTimeName);

    DOMText *wallTxt = doc->createTextNode(wallVal);
    DOMText *cpuTxt = doc->createTextNode(cpuVal);
    DOMText *sysTxt = doc->createTextNode(sysVal);
    DOMText *usrTxt = doc->createTextNode(usrVal);

    //append the elements to the documents speed result section
    spdResult->setAttribute(tsectionAtb, tsectVal);
    spdResult->appendChild(stestElm);
    stestElm->appendChild(wTimeElm);
    stestElm->appendChild(cpuTimeElm);

    wTimeElm->appendChild(wallTxt);

    cpuTimeElm->appendChild(totalTimeElm);
    cpuTimeElm->appendChild(uTimeElm);
    cpuTimeElm->appendChild(sTimeElm);
    totalTimeElm->appendChild(cpuTxt);
    uTimeElm->appendChild(usrTxt);
    sTimeElm->appendChild(sysTxt);

    XMLString::release(&tsectVal);
    XMLString::release(&wallVal);
    XMLString::release(&cpuVal);
    XMLString::release(&sysVal);
    XMLString::release(&usrVal);
}

//check if a section already exists
bool ResultXML::findSection(XMLCh *sect)
{
    //create the iterator to look for only text nodes
    DOMNodeIterator *iter = doc->createNodeIterator(sectList, DOMNodeFilter::SHOW_TEXT, 0, false);
    DOMNode *node;

    //loop through the section list part of the document comparing the text nodes to see if it exists
    while((node = iter->nextNode()) != NULL)
    {
        DOMText *txtNode = dynamic_cast<DOMText*>(node);

        if(XMLString::equals(sect, txtNode->getData())){

            return true;
        }
    }

    return false;
}

//add the name of a section to the section list
void ResultXML::addSection(XMLCh* sectName)
{

    DOMText *txtNode = doc->createTextNode(sectName);
    DOMElement *sectElm = doc->createElement(sectElmName);

    sectList->appendChild(sectElm);
    sectElm->appendChild(txtNode);
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

speed_map ResultXML::getSpeedResult()
{
    //get all the child nodes that contain the resulte
    DOMNodeList *spdList = spdResult->getChildNodes();

    speed_map spdMap; //hold the extracted values

    //set-up xml names
    XMLCh *stestName = XMLString::transcode("stest");

    for(XMLSize_t x=0; x<spdList->getLength(); x++){

        DOMNode *curNode = spdList->item(x);
        DOMElement *curElm;

        if(curNode->getNodeType() == DOMNode::ELEMENT_NODE){
            curElm = dynamic_cast<DOMElement*>(curNode);

            if(XMLString::equals(stestName, curElm->getTagName())){
              //  struct SpeedInfo si;
                //extractSpeedInfo(curElm, si);
                //char *section = XMLString::transcode(curElm->getAttribute())
               // if(spdMap)
            }
        }

    }
}
