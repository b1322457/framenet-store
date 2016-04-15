//
// Created by 王鹏飞 on 16/4/13.
//
#include "frames.h"


Frame* FrameBuilder::build_frame(std::string xml_path){

    std::vector<FrameElement*>elements;
    std::vector<LexicalUnit*>lexemes;
    std::vector<FrameRelation*>relations;
    std::vector<std::string>parents;
    std::vector<std::string>children;

    //read the frame.xml and analysis
    rapidxml::file<> fdoc(xml_path.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(fdoc.data());
    rapidxml::xml_node<>* root = doc.first_node();
    std::string name = root->first_attribute("name")->value();
    int ID = atoi(root->first_attribute("ID")->value());

    //build FE
    for(auto node = root->first_node("FE");node!= nullptr;node = node->next_sibling("FE")){
        elements.push_back(build_FE(node,name));
    }

    //build LU
    for(auto node = root->first_node("lexUnit");node!= nullptr;node = node->next_sibling("lexUnit")){
        lexemes.push_back(build_LU(node,name));
    }

    //build frameRelation
    for(auto node = root->first_node("frameRelation");node!= nullptr;node = node->next_sibling("frameRelation")){
        relations.push_back(build_FR(node,parents,children));
    }

    //build definition,use regex to filter the html tag
    rapidxml::xml_node<>* def_node = root->first_node("definition");
    std::string xml_text = def_node->value();
    boost::regex expr{"<[^>]*>"};
    std::string fmt{""};
    std::string def_text = boost::regex_replace(xml_text, expr, fmt);

    Frame *frame = new Frame(parents,children,name,elements,lexemes,relations,xml_text,def_text,ID);
    return frame;

}

FrameElement* FrameBuilder::build_FE(rapidxml::xml_node<>*node,std::string frame_name){
    std::string name = node->first_attribute("name")->value();
    std::string abbrev = node->first_attribute("abbrev")->value();
    std::string coreType = node->first_attribute("coreType")->value();
    int ID = atoi(node->first_attribute("ID")->value());
    std::string xml_definition = node->first_node("definition")->value();
    boost::regex expr{"<[^>]*>"};
    std::string fmt{""};
    std::string def_text = boost::regex_replace(xml_definition, expr, fmt);

    FrameElement *element = new FrameElement(name,abbrev,coreType,frame_name,ID,def_text);

    //set semType
    auto p=node->first_node("semType");
    if(p!= nullptr){
        std::string name = p->first_attribute("name")->value();
        int ID = atoi(p->first_attribute("ID")->value());
        SemType *s = new SemType(name,ID);
        element->set_semtype(s);
    }

    //set excludesFEs
    for(auto p=node->first_node("excludesFE");p!= nullptr;p = p->next_sibling("excludesFEs")){
        std::string name = p->first_attribute("name")->value();
        element->add_excludes(name);
    }

    //set requiresFEs
    for(auto p=node->first_node("requiresFE");p!= nullptr;p = p->next_sibling("requiresFEs")){
        std::string name = p->first_attribute("name")->value();
        element->add_requires(name);
    }


    return  element;
}

LexicalUnit* FrameBuilder::build_LU(rapidxml::xml_node<>*node,std::string frame_name){
    int ID = atoi(node->first_attribute("ID")->value());
    std::string name = node->first_attribute("name")->value();
    std::string POS = node->first_attribute("POS")->value();
    std::string status = node->first_attribute("status")->value();
    LexicalUnit *lu = new LexicalUnit(name,POS,frame_name,ID,status);
    auto p=node->first_node("semType");
    if(p!= nullptr){
        std::string name = p->first_attribute("name")->value();
        int ID = atoi(p->first_attribute("ID")->value());
        SemType *s = new SemType(name,ID);
        lu->set_semtype(s);
    }
    return lu;
}

FrameRelation* FrameBuilder::build_FR(rapidxml::xml_node<>*node,std::vector<std::string>&parents,std::vector<std::string>&children){
    std::string relation_type = node->first_attribute("type")->value();
    std::vector<std::string> related_frames;
    for(auto child = node->first_node("relatedFrame");child!= nullptr;child = child->next_sibling("relatedFrame")){
        std::string r_frame_name = child->value();
        related_frames.push_back(r_frame_name);
        if(relation_type=="Inherits from"){
            parents.push_back(r_frame_name);
        }
        if(relation_type=="Is Inherited by"){
            children.push_back(r_frame_name);
        }
    }
    return new FrameRelation(relation_type,related_frames);
}