#ifndef RESULTXML_H
#define RESULTXML_H

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "pstructs.h"

class ResultXML
{
    public:
        ResultXML();
        ResultXML(const char*);
        ~ResultXML();

        void addSpeedResult(SpeedInfo&);
        void addMemResult(MemInfo&);
        void addSection(const char*);
        void save();

    private:
        xercesc::DOMImplementation *imp;
        xercesc::DOMDocument *doc;
        xercesc::DOMElement *root;
        xercesc::DOMElement *spdResult;
        xercesc::DOMElement *memResult;
        xercesc::DOMElement *sectList;
        xercesc::XMLFormatTarget *ftarget;
        const char *filename;

        //forbid copying or assignment to keep things clean
        ResultXML(const ResultXML&){};
        ResultXML& operator= (const ResultXML&){
            return *this;
        }

};

#endif // RESULTXML_H
