//
// Created by 王鹏飞 on 16/4/13.
//

#include "builder.h"

int main(){
    std::string frame_path = "/Users/wangpf/git_repo/framenet/fndata-1.6/frame/";
    std::string relation_path = "/Users/wangpf/git_repo/framenet/fndata-1.6/frRelation.xml";
    std::string lu_path = "/Users/wangpf/git_repo/framenet/fndata-1.6/lu";

    FrameNetBuilder fnb = FrameNetBuilder(frame_path,relation_path,lu_path);
    FrameNet fn = fnb.read();
}
