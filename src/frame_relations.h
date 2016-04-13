//
// Created by 王鹏飞 on 16/4/7.
//

#ifndef FRAMENET_EN_FRAME_RELATIONS_H
#define FRAMENET_EN_FRAME_RELATIONS_H

#endif //FRAMENET_EN_FRAME_RELATIONS_H

#include <iostream>
#include <vector>

class FrameRelation{
private:
std::string relation_type;
std::vector<std::string> related_frames;
public:
FrameRelation(std::string relation,std::vector<std::string> &related){
     this->relation_type = relation;
     this->related_frames = related;
}
};