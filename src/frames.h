//
// Created by 王鹏飞 on 16/4/6.
//

#ifndef FRAMENET_EN_FRAMES_H
#define FRAMENET_EN_FRAMES_H

#endif //FRAMENET_EN_FRAMES_H

#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "lexical_units.h"
#include "frame_relations.h"



class FrameElement{

private:
    std::string name;
    std::string abbrev;
    std::string coreType;
    std::string frame_name;
    int ID;
    std::string definition;
    SemType *semtype;// type  should be object
    std::vector<std::string> excludes;// type should be vector
    std::vector<std::string> requires;// type should be vector
public:
    FrameElement(std::string name,std::string abbrev,std::string coreType,std::string frame_name,int ID,
                 std::string definition,SemType *semType= nullptr){
        this->name = name;
        this->abbrev = abbrev;
        this->coreType = coreType;
        this->frame_name = frame_name;
        this->ID = ID;
        this->semtype = semType;
    };

    void set_semtype(SemType *s){
        this->semtype = s;
    }

    void add_excludes(std::string fe_name){
        this->excludes.push_back(fe_name);
    }

    void add_requires(std::string fe_name){
        this->requires.push_back(fe_name);
    }


};

class FrameElementRelation{
private:
    std::string fe1;
    std::string fe2;
    std::string name;
    std::string superFrame;
    std::string subFrame;
public:
    FrameElementRelation(std::string fe1,std::string fe2,std::string name="",std::string superFrame="",std::string subFrame=""){
        this->fe1 = fe1;
        this->fe2 = fe2;
        this->name = name;
        this->superFrame = superFrame;
        this->subFrame = subFrame;
    }
};




class Node{
private:
    std::vector<std::string> parents;
    std::vector<std::string> children;
public:
    Node(const std::vector<std::string> &parents,const std::vector<std::string> &children){
        this->parents = parents;
        this->children = children;
    }
};
class Frame:public Node{
private:
    std::string name;
    std::vector<FrameElement*> elements;
    std::vector<LexicalUnit*> lexicalUnits; //ShallowLU don't have the full LU infomation
    std::vector<FrameRelation*>relations;
    std::vector<FrameElementRelation*> fe_relations;// data type need change
    std::string xml_definition;
    std::string definition;
    int ID;
    std::vector<FERealization*>fe_realizations;
public:
     Frame(const std::vector<std::string>&parents,const std::vector<std::string>&children,std::string name,const std::vector<FrameElement*> &elements,
          const std::vector<LexicalUnit*>&lexicalUnits,const std::vector<FrameRelation*>&relations,std::string xml_definition,std::string definition,int ID):Node(parents,children){
        this->name = name;
        this->elements = elements;
        this->lexicalUnits = lexicalUnits;
        this->relations = relations;
        this->xml_definition = xml_definition;
        this->definition = definition;
        this->ID = ID;
    }

     std::string get_name() const{
        return  name;
    }

     std::vector<LexicalUnit*> get_lexicalUnits() const{
        return lexicalUnits;
    }

     std::string get_definition() const{
        return  definition;
    }

     std::string get_xml_definition() const{
        return  xml_definition;
    }

     int get_ID() const{
        return  ID;
    }

     void add_fe_realizations(std::vector<FERealization*> fer_vec){
        this->fe_realizations.insert(fe_realizations.end(),fer_vec.begin(),fer_vec.end());
    }

     void add_fe_relation(FrameElementRelation* fr){
        this->fe_relations.push_back(fr);
    }

};

class FrameBuilder{
public:
    /**
     * build frame object from the frame.xml
     */
    Frame* build_frame(std::string xml_path);

    /**
     * build frameelement from the info in frame.xml
     */
    FrameElement* build_FE(rapidxml::xml_node<>*node,std::string frame_name);

    /**
     * build lu from the shallow info in frame.xml
     */
    LexicalUnit* build_LU(rapidxml::xml_node<>*node,std::string frame_name);

    /**
     * build fr obj from the frame.xml
     */
    FrameRelation* build_FR(rapidxml::xml_node<>*node,std::vector<std::string>&parents,std::vector<std::string>&children);

};


