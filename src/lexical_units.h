//
// Created by 王鹏飞 on 16/4/7.
//

#ifndef FRAMENET_EN_LEXICAL_UNITS_H_H
#define FRAMENET_EN_LEXICAL_UNITS_H_H

#endif //FRAMENET_EN_LEXICAL_UNITS_H_H

#include <iostream>
#include "annotation.h"


class SemType{
private:
    std::string name;
    int ID;
public:
    SemType(std::string name,int ID){
        this->name = name;
        this->ID = ID;
    }
};


class FERealization{

public:
    std::string frame_name;
    int total;
    std::string lexeme;
    std::string fe_name;
    std::vector<int> annotationID;
    std::vector<Annotation*>annotations;


    FERealization(std::string frame_name,int total,std::string lexeme){
        this->frame_name = frame_name;
        this->total = total;
        this->lexeme = lexeme;
    }

    void set_fe(std::string fe_name){
        this->fe_name = fe_name;
    }

    void set_annotationID(int ID){
        annotationID.push_back(ID);
    }

};





/**
 * Just contains LU information from frame.xml without valence patterns
 */
class LexicalUnit{

private:
    std::string name;
    std::string pos;
    std::string frame_name;
    int ID;
    std::string status;
    SemType * semtype= nullptr;

    //information extract from the lu.xml
    std::string definition;
    std::vector<FERealization*>fe_realizations;
    std::vector<Annotation*>annotations;

public:
    LexicalUnit(std::string name,std::string pos,std::string frame_name,int ID,std::string status){
        this->name = name;
        this->pos = pos;
        this->frame_name = frame_name;
        this->ID = ID;
        this->status = status;
    }

    void set_definition(std::string definition){
        this->definition = definition;
    }

    void set_fe_realizations(const std::vector<FERealization*>&fe_realizations){
        this->fe_realizations = fe_realizations;
    }

    void set_annotations(const std::vector<Annotation*>&annotations){
        this->annotations = annotations;
    }


    void set_semtype(SemType *s){
            this->semtype = s;
    }

    std::string get_name(){
        return  this->name;
    }

    int get_ID(){
        return ID;
    }

    std::string get_frame_name(){
        return  this->frame_name;
    }

    std::string get_pos(){
        return  this->pos;
    }

    SemType* get_semtype(){
        return this->semtype;
    }

    std::string get_status(){
        return this->status;
    }

    std::vector<FERealization*>& get_fe_realizations(){
        return this->fe_realizations;
    }

    std::vector<Annotation*>& get_annotations(){
        return this->annotations;
    }

};


