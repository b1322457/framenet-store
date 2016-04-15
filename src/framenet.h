//
// Created by 王鹏飞 on 16/4/6.
//

#ifndef FRAMENET_EN_FRAMENET_H
#define FRAMENET_EN_FRAMENET_H

#endif //FRAMENET_EN_FRAMENET_H

#include <map>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "frames.h"
using namespace boost::algorithm;

class FrameNet{
public:
    FrameNet(){

    }

    void add_frame(Frame* frame){
        this->name_to_frames[frame->get_name()]=frame;
        this->frames.push_back(frame);
        for(auto p:frame->get_lexicalUnits()){
            std::string lex = p->get_name();
            std::vector<std::string> v;
            split(v, lex, is_any_of("."));
            std::string untag =v[0];

            this->lexemes_to_frames[lex].push_back(frame);
            this->untagged_lus[untag].push_back(frame);
            this->definitions_to_frames[frame->get_definition()]=frame;
            this->xml_definitions_to_frames[frame->get_xml_definition()]=frame;
            this->ID_to_frames[frame->get_ID()]=frame;
        }
    }

    /**
     * Returns frame from name
     */
    Frame* get_frame(std::string name){
        if(name_to_frames[name]!= nullptr){
            return  name_to_frames[name];
        }
        else
        {
            return nullptr;
        }
    }

    std::vector<Frame*> get_frames_from_lu(std::string lu_name){
        if(lexemes_to_frames.find(lu_name)!=lexemes_to_frames.end()){
            return lexemes_to_frames[lu_name];
        }
    }


private:
    std::map<std::string,Frame*> name_to_frames;
    std::map<std::string,std::string> hierarchy;
    std::vector<Frame*> frames;

    //frame index
    std::map<std::string,std::vector<Frame*>> untagged_lus;
    std::map<std::string,std::vector<Frame*>> lexemes_to_frames;
    std::map<std::string,Frame*> definitions_to_frames;
    std::map<std::string,Frame*> xml_definitions_to_frames;
    std::map<int,Frame*> ID_to_frames;

};