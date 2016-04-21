//
// Created by 王鹏飞 on 16/4/7.
//

#ifndef FRAMENET_EN_LEXICAL_UNITS_H_H
#define FRAMENET_EN_LEXICAL_UNITS_H_H

#endif //FRAMENET_EN_LEXICAL_UNITS_H_H

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <queue>
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

struct StringCompare{
    static bool mycomp (char c1, char c2){
        return std::tolower(c1)<std::tolower(c2);
    }

    bool operator ()(const std::string& s1,const std::string& s2)const{
        return std::lexicographical_compare(s1.begin(),s1.end(),s2.begin(),s2.end(),StringCompare::mycomp);
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

    /**
     * 返回替换为FE后的句子,map键为替换后的句子,值vector
     * 为句子中包含的FE和LU,LU在vector的第一个元素,其余的为FE (一个句子中应该不会有重复的lu和fe吧???)
     */
    std::map<std::string,std::vector<std::string>>  get_sub_sentence(){
        std::set<std::string,StringCompare> prep_list{"about","after","among","as","at","because","before","between","by","despite","during","for","from","if","in",
        "of","on","over","since","than","that","through","under","while","with","without"};
        std::map<std::string,std::vector<std::string>> res;
        for(auto annotation:annotations){
            std::vector<Label>labels = annotation->get_labels();
            std::priority_queue<Label,std::vector<Label>,std::greater<Label>>q;
            for(auto label:labels){
                q.push(label);
            }

            std::string raw_sen = annotation->get_sentence();
            std::vector<std::string> fe_names;
            std::ostringstream strout;
            for(size_t i=0;i<raw_sen.size();i++){
                auto remain_label = q.top();
                //要判断是否为介词
                if(i==remain_label.start){
                    std::string s = remain_label.fe_name;
                    std::vector<std::string> v;
                    boost::algorithm::split(v, s, boost::algorithm::is_space());
                    if(prep_list.find(v[0])!=prep_list.end()){
                        strout<<v[0]<<" "; //如果开头是介词,保留这个介词到res中
                    }
                    strout<<remain_label.fe_name;
                    if(remain_label.fe_ID!=-1)//不是lu放到vector的后边,是的话放到开始
                    {
                        fe_names.push_back(remain_label.fe_name);
                    }
                    else{
                        fe_names.insert(fe_names.begin(),remain_label.fe_name);
                    }
                    i=remain_label.end;
                    q.pop();
                    continue;
                }
                else{
                    strout<<raw_sen[i];
                }
            }
            res[strout.str()]=fe_names;
        }
        return res;
    }

};


