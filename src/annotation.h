//
// Created by 王鹏飞 on 16/4/12.
//

#ifndef FRAMENET_EN_ANNOTATIONS_H
#define FRAMENET_EN_ANNOTATIONS_H

#endif //FRAMENET_EN_ANNOTATIONS_H

#include <iostream>
#include <vector>

class Label{
public:
    int start;
    int end;
    std::string fe_name;
    int fe_ID;
};



class Annotation{
private:
    std::string sentence;
    int ID;
    std::string status;
    std::vector<Label>labels;
public:
    Annotation(const std::string &sentence,int ID,const std::string status,const std::vector<Label> &labels){
        this->sentence = sentence;
        this->ID = ID;
        this->status = status;
        this->labels = labels;
    }
    int get_ID(){
        return this->ID;
    }
};