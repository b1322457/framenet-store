//
// Created by 王鹏飞 on 16/4/13.
//

#include "builder.h"

int main(){
    std::string frame_path = "/Users/wangpf/git_repo/framenet/fndata-1.6/frame/";
    std::string relation_path = "/Users/wangpf/git_repo/framenet/fndata-1.6/frRelation.xml";
    std::string lu_path = "/Users/wangpf/git_repo/framenet/fndata-1.6/lu/";

    FrameNetBuilder fnb = FrameNetBuilder(frame_path,relation_path,lu_path);
    FrameNet fn = fnb.read();
    fnb.build_lus_for_frame("Motion", fn);
    auto frame = fn.get_frame("Motion");

    auto relations = frame->get_relations();

    for(auto relation:relations){
        std::cout<<relation->relation_type<<std::endl;
        std::cout<<relation->related_frames.size()<<std::endl;
    }
    auto lu = frame->get_lu("coast.v");


}
