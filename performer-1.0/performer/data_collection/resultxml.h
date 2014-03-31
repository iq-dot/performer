#ifndef RESULTXML_H
#define RESULTXML_H

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLString.hpp>
#include "performer/data_collection/pstructs.h"

class ResultXML
{
    public:
        ResultXML(const char *file, const char *source); //create file
        ResultXML(const char* file); //load file
        ~ResultXML();

        void addSpeedResult(const SpeedInfo&, const char *sect);
        void addMemResult(const MemInfo&, const char *sect);
        void save();
        const char* getSourceName();

        void getSpeedResult(speed_map *sm);
        void getMemResult(mem_map *mm);

    private:
        xercesc::DOMImplementation *imp;
        xercesc::DOMDocument *doc;
        xercesc::DOMElement *root;
        xercesc::DOMElement *spdResult;
        xercesc::DOMElement *memResult;
        xercesc::DOMElement *sectList;
        xercesc::XercesDOMParser *parser;
        XMLCh *filename;

        bool findSection(XMLCh *sect);
        void addSection(XMLCh *sect);
        void extractSpeedInfo(xercesc::DOMElement*, SpeedInfo&);
        void extractMemInfo(xercesc::DOMElement*, MemInfo&);

        //forbid copying or assignment to keep things clean
        ResultXML(const ResultXML&){};
        ResultXML& operator= (const ResultXML&){
            return *this;
        }
};

#endif // RESULTXML_H
